#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    int pid;

    if (argc<1){
        perror("There is no one to give alarm!");
        exit(1);
    }

    pid = atoi(argv[1]);
    kill(pid, SIGALRM);

return 0;
}
