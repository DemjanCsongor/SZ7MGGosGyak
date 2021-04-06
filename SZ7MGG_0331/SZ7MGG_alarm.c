#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void doNothing();
void doBreak();

int main(){
	int i;
	unsigned int sec=1;

	signal(SIGINT, doBreak);

	for(i = 1; i<8; i++){
	alarm(sec);
	signal(SIGALRM, doNothing);
	printf("%d I will wait, but for how long?\n", i);
	pause();
	}

return 0;
}

void do_nothing(){
	printf("ALARM\n");
}

void do_break(){
	printf("Interruption!\n");
	signal(SIGINT, SIG_IGN);
}
