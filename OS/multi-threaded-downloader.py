import requests
import click
import threading

def Downloader(start, end, url, file_name):
    headers = {'Range':'bytes=%d-%d'%(start, end)}
    r = requests.get(url, headers=headers, stream=True)
    with open(file_name, "r+b") as fp:
        fp.seek(start)
        var = fp.tell()
        fp.write(r.content)

@click.command(help="Multi Threaded Downloader.\
    Author: Sushant(CS1807)* and Devam (CS1805)")
@click.option("--number_of_threads", default=4, help="Number of threads.")
@click.option("--resume_file", help="Name of the download file that we want to resume.")
@click.option("--name", type=click.Path(), help="Desired Name of the file along with its extension.")
@click.argument("url_of_file", type=click.Path())
def file_dowloader(url_of_file, name, number_of_threads, resume_file):
    r = requests.head(url_of_file)
    try:
        file_size = int(r.headers['Content-Length'])
    except:
        print("Invalid URL")
        return

    if name:
        file_name = name
    else:
        file_name = url_of_file.split('/')[-1]
    
    part = int(file_size)/number_of_threads
    fp = open(file_name, "wb")
    fp.write(b'\0' * file_size)
    fp.close()

    for i in range(number_of_threads):
        start = part * i
        end = start + part
        t = threading.Thread(
                target=Downloader, 
                kwargs={
                    'start':start,
                    'end':end,
                    'url':url_of_file,
                    'file_name':file_name
                })
        t.setDaemon(True)
        t.start()
        main_thread = threading.current_thread()
        for t in threading.enumerate():
            if t is main_thread:
                continue
            t.join()
            print("{file_name} Downloaded".format(file_name=file_name))

if __name__ == "__main__":
    file_dowloader()


