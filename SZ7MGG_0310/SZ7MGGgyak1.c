#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){

	int status;

	if ( (status = system("date")) < 0){
		perror("system() error");
	}

	if (WIFEXITED(status)){
		printf("Normal, value retourned = %d\n", WEXITSTATUS(status));
	}
    return 0;
}