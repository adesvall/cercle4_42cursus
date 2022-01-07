
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <wait.h>

void	handle_sig(int sig)
{
	if (sig == SIGQUIT)
	{
		//write(1, "\b\b  \b\b", 6);
	}
}

int	sig_init(void)
{
	if (signal(SIGQUIT, handle_sig))
		return (1);
	return (0);
}

int main() {
	int status =0;
	int pid = fork();

	sig_init();
	if (pid == 0)
		execv("/usr/bin/cat", (char*[2]){"cat", NULL});
	else
	{
		waitpid(pid, &status, 0);
		printf("%d\n", errno);
	}
	printf("STATUS = %d, exit=%d, termsig=%d\n", status, WEXITSTATUS(status), WTERMSIG(status));
	return 0;
}