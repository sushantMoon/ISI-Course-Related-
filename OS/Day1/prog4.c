#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    pid_t status_fork = fork();
    int status_execv;
    if (status_fork == -1) {
        printf("Error : Child could not be created !!\n");
    }
    else if(status_fork == 0) {
        char *argv[] = {"/bin/ls", "-lah", NULL};
        status_execv = execv(argv[0], argv);
        if (status_execv == -1){
            printf("Error: Execv failed in the child process\n");
        }
        exit(0);
    }
    else {
        printf("In Parent Process: ");
        printf("Pid for the child %d\n", status_fork);
        exit(0);
    }
    
    return 0;
}
