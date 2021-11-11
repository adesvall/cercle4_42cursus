
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>


int main() {
	char *text;

	text = malloc(20);
	int pid = fork();
	if (pid != 0)
		free(text);
}