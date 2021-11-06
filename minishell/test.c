

volatile int myvar = 0;

int main() {
	extern int myvar;
	
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
	printf("%d : %d\n", pid, myvar);
 }