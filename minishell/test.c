
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

volatile int myvar = 0;

int main() {
	int a =0;
	
	int pid = fork();
	if (pid > 0) {
		while (myvar < 100){
			myvar++;

		}
	} else {
		while (myvar < 150){
			myvar++;

		}
	}
	printf("%d : %d\n", pid, myvar);
	sleep(2);
	if (pid > 0) {
	} else {
		myvar++;
	
	}
	printf("%d : %d\n", pid, myvar);
 }