#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int i, no_child = 10;
    printf("Parent Process PID: %d\n", getpid());
    printf("Printf: Hello World\n");
    for( i = 0; i < no_child; i++){
        pid_t status_fork = fork();
        if (status_fork == -1) {
            printf("Error : Child could not be created !!\n");
        }
        else if (status_fork == 0){
            printf("Pid for the child %d\n", getpid());
            exit(0);
        }
    }
    
    return 0;
}
