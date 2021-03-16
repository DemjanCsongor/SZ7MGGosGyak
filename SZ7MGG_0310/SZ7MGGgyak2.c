#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int main(void){

	char a[100];

    printf("Enter a command, that you want to execute: ");

    scanf("%s", a);

	system(a);

	return 0;
}