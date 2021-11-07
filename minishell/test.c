
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

volatile int myvar = 0;

void handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\nSIGINT\n", 8);
		printf(%);
	}
}

int	sig_init(void)
{
	struct sigaction act;

	act.sa_handler = &handle_sig;
	if (sigaction(SIGINT, &act, NULL))
		return (1);
	if (sigaction(SIGQUIT, &act, NULL))
		return (1);
	return (0);
}
int main() {
	int a =0;
	sig_init();
	
	int pid = fork();
	if (pid > 0) {
		myvar++;
	} else {
		
	}
	printf("%d : %d\n", pid, myvar);

	if (pid > 0) {
	} else {
		myvar++;
	
	}
	while (1){

	}
	printf("%d : %d\n", pid, myvar);
 }