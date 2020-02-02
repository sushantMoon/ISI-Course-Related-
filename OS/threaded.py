""" Utility to download files over the internet
    multithreaded, and uses signal to handle quitting
    using KeyBoardInterrupt, prints the status in shell.
"""


import argparse
import logging
import Queue
import urllib2
import os
import signal
import sys
import time
import threading
from socket import error  as _SocketError

urls = ["http://broadcast.lds.org/churchmusic/MP3/1/2/nowords/271.mp3",
"http://s1.fans.ge/mp3/201109/08/John_Legend_So_High_Remix(fans_ge).mp3",
"http://megaboon.com/common/preview/track/786203.mp3"]

DESKTOP_PATH = os.path.expanduser("~/Desktop")


queue = Queue.Queue()
STOP_REQUEST = threading.Event()


def unGracefullExit(sigNum, stack):
    # restore the original signal handler as otherwise evil things will happen
    # when CTRL+C is pressed, and our signal handler is not re-entrant
    signal.signal(signal.SIGINT, original_sigint)
    # ensure no thread runs after process is killed
    STOP_REQUEST.set()
    # handle unix signal recived and exit
    sys.stderr.write("Received signal %d " % (sigNum))
    os.kill(os.getpid(), signal.SIGINT)
    # restore the exit gracefully handler here    
    signal.signal(signal.SIGINT, unGracefullExit)

class ThreadedFetch(threading.Thread):
    """ docstring for ThreadedFetch
    """
    def __init__(self, queue, logging):
        super(ThreadedFetch, self).__init__()
        self.queue = queue
        self._log = logging
        self.kill_received = False

    def run(self):

        while not STOP_REQUEST.isSet():
            # grabs url of link and path to saveTo and save to lst
            host = self.queue.get()
            start = FileDownloader(self._log, self, self.queue)
            # submit the url for download and location where to save.
            start.downloadFile(host[0], host[1])


class Watcher(object):
    """ This class solves two problems with multithreaded
    programs in Python, (1) a signal might be delivered
    to any thread (which is just a malfeature) and (2) if
    the thread that gets the signal is waiting, the signal
    is ignored (which is a bug).

    The watcher is a concurrent process (not thread) that
    waits for a signal and the process that contains the
    threads.  See Appendix A of The Little Book of Semaphores.
    http://greenteapress.com/semaphores/

    I have only tested this on Linux.  I would expect it to
    work on the Macintosh and not work on Windows.
    """

    def __init__(self):
        """ Creates a child thread, which returns.  The parent
            thread waits for a KeyboardInterrupt and then kills
            the child thread.
        """
        self.child = os.fork()
        if self.child == 0:
            return
        else:
            self.watch()

    def watch(self):
        try:
            os.wait()
        except KeyboardInterrupt:
            # I put the capital B in KeyBoardInterrupt so I can
            # tell when the Watcher gets the SIGINT
            print "KeyBoardInterrupt\nExiting"
            self.kill()
        sys.exit()

    def kill(self):
        try:
            os.kill(self.child, signal.SIGKILL)
        except OSError: pass

class FileDownloader(object):
    """ FileDownloader class that downloads a file.
    """

    def __init__(self, logging, thread=None, queue=None):
        super(FileDownloader, self).__init__()
        self._log = logging
        self.queue = queue
        self.thread = thread

    def downloadFile(self, url, saveTo=None):
        """ this class performs file download job

            Args:
                url(str): url of the file to download
                saveTo(str): path where you want file
                            to be saved on disk
        """

        file_name = url.split('/')[-1]
        self.thread.setName("Parent_%s_thread" % file_name.split(".")[0])
        if not saveTo:
            saveTo = DESKTOP_PATH
        try:
            u = urllib2.urlopen(url)
        except urllib2.URLError , er:
            self._log.error("%s for %s failed to download." , er.reason, file_name)
            self.queue.task_done()
            self._log.info("Exiting: %s", self.thread.getName())
        except _SocketError , err:
            self._log.error("%s \n %s failed to download.", err, file_name)
            self.queue.task_done()
        except KeyboardInterrupt:
            print >>sys.stderr, "Interrupt recived"
            os.kill(os.getpgid(), signal.SIGINT)
        else:
            if not self.thread:
                self._fileWriteToDisk(saveTo, u, file_name)
            else:
                th = threading.Thread(
                        target=self._fileWriteToDisk,
                        args=(saveTo, u, file_name),
                        name="fileWrite_Child_of_%s" % self.thread.getName(),
                        )
                # if the user clicks close while the thread is still running,
                # then the programme will wait till the save is done,
                # then it will close.
                # STOP_REQUEST is false initially so and parent thread waits for this
                # child thread to finish first but if user presses ctrl+c STOP_REQUEST
                # becomes TRUE and parent daeamon thread doesnt waits for child.
                th.daemon = STOP_REQUEST.isSet()
                th.start()
                time.sleep(0.1)
                self._log.info("Saving %s to disk", file_name)


    def _fileWriteToDisk(self, saveTo, urlObject, file_name):
        """ This method performs the task to write the file downlaoded to disk

            Args:
                saveTo(str): location where you want file to be saved on disk
                urlObject(urllib2.urlopen): url object to read the buffer
                file_name(str): name of file to be saved.
        """

        path = os.path.join(saveTo, file_name)
        try:
            f = open(path, 'wb')
        except IOError , er:
            self.queue.task_done()
            self._log.error(er)
            return
        meta = urlObject.info()
        file_size = int(meta.getheaders("Content-Length")[0])
        self._log.info("Downloaded: %s : %s ", file_name, sizeof(file_size))
        file_size_dl = 0
        block_sz = 8192
        while True:
            buffer = urlObject.read(block_sz)
            if not buffer:
                break

            file_size_dl += len(buffer)
            f.write(buffer)
            status = r"%10d  [%3.2f%%]" % (file_size_dl, file_size_dl * 100. / file_size)
            status = status + chr(8)*(len(status)+1)
            sys.stdout.write('%s\r' % status)
            time.sleep(.05)
            sys.stdout.flush()
            if file_size_dl == file_size:
                self._log.info("Download Completed %s%% for file %s, saved to %s", file_size_dl * 100. / file_size, file_name, saveTo)

        f.close()
        # signals to queue job is done
        self.queue.task_done()

class FullPaths(argparse.Action):
    """ Expand user- and relative-paths
    """
    def __call__(self, parser, namespace, values, option_string=None):
        setattr(namespace, self.dest, os.path.abspath(os.path.expanduser(values)))

def sizeof(bytes): 
    """ Takes the size of file or folder in bytes and 
        returns size formatted in kb, MB, GB, TB or PB. 

        Args:
            bytes(int): size of the file in bytes
        Return:
            (str): containing size with formatting.
    """
    alternative = [ 
        (1024 ** 5, ' PB'), 
        (1024 ** 4, ' TB'), 
        (1024 ** 3, ' GB'), 
        (1024 ** 2, ' MB'), 
        (1024 ** 1, ' KB'), 
        (1024 ** 0, (' byte', ' bytes')), 
    ] 

    for factor, suffix in alternative: 
        if bytes >= factor: 
            break
    amount = int(bytes/factor) 
    if isinstance(suffix, tuple): 
        singular, multiple = suffix 
        if amount == 1: 
            suffix = singular 
        else: 
            suffix = multiple 
    return "%s %s" % (str(amount), suffix)

def main(appName, flag='with'):
    parser = argparse.ArgumentParser(prog='FileDownloader',
        description='Utility to download files from internet')
    parser.add_argument('-v', '--verbose', default=logging.DEBUG,
        help='by default its on, pass None or False to not spit in shell')
    parser.add_argument('-st', '--saveTo', action=FullPaths,
        help='location where you want files to download to')
    parser.add_argument('-urls', nargs='+', type=str,
        help='urls of files you want to download.')
    args = parser.parse_args()


    logFile = os.path.join(DESKTOP_PATH, '%s.log' % appName)

    lgr = function_logger(appName, logFile, args.verbose, logging.DEBUG, console_level=logging.DEBUG)


    if flag == 'with':
        Watcher()
    elif flag != 'without':
        lgr.info('unrecognized flag: %s', flag)
        sys.exit()

    # spawn a pool of threads, and pass them queue instance 
    for i in range(len(urls)):
        t = ThreadedFetch(queue, lgr)
        t.daemon = True
        t.start()

    try:
        urls_saveTo = {}
        for url in args.urls:
            urls_saveTo[url] = args.saveTo
        # urls_saveTo = {urls[0]: args.saveTo, urls[1]: args.saveTo, urls[2]: args.saveTo}
        # populate queue with data 
        for item, value in urls_saveTo.iteritems():
            queue.put([item, value])

        # wait on the queue until everything has been processed
        queue.join()
        print '*** Done'
    except (KeyboardInterrupt, SystemExit):
        lgr.critical('! Received keyboard interrupt, quitting threads.')

def function_logger(appName, logFile, fileDebugLevel, file_level, console_level=None):

    logger = logging.getLogger(appName)
    # By default, logs all messages
    logger.setLevel(logging.DEBUG)

    if console_level != None:
        # StreamHandler logs to console
        ch = logging.StreamHandler()
        ch.setLevel(fileDebugLevel)
        ch_format = logging.Formatter('%(levelname)s - %(message)s')
        ch.setFormatter(ch_format)
        logger.addHandler(ch)

    fh = logging.FileHandler(logFile)
    fh.setLevel(file_level)
    fh_format = logging.Formatter('%(asctime)s - (%(threadName)-10s) - %(levelname)s:  %(message)s')
    fh.setFormatter(fh_format)
    logger.addHandler(fh)

    return logger

if __name__ == "__main__":
    # change the name of MainThread.
    threading.currentThread().setName("FileDownloader")
    myapp = threading.currentThread().getName()
    # store the original SIGINT handler for check while re-entry 
    original_sigint = signal.getsignal(signal.SIGINT)
    # Register signal in main thread
    signal.signal(signal.SIGINT, unGracefullExit)
    main(myapp)