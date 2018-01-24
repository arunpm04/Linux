#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

/* Singal handlers */
void custom_sighup(int sig)
{
	signal(SIGHUP, custom_sighup); /* reset signal */
	printf("CHILD: I have received a SIGHUP\n");
}

void custom_sigint(int sig)
{
	signal(SIGINT, custom_sigint); /* reset signal */
	printf("CHILD: I have received a SIGINT\n");
}

void custom_sigquit(int sig)
{
	printf("Quit signal received; exiting...!!!\n");
	exit(0);
}


int main(void)
{
	int pid;

	/* get child process */
	if ((pid = fork()) < 0) {
		perror("fork");
		exit(1);
	}

	if (pid == 0) {
		/* child */
		signal(SIGHUP, custom_sighup); /* set function calls */
		signal(SIGINT, custom_sigint);
		signal(SIGQUIT, custom_sigquit);
		for(;;); /* loop for ever */
	} else {
		/* Parent */
		/* pid hold id of child */
		printf("\nPARENT: sending SIGHUP\n\n");
		kill(pid, SIGHUP);
		sleep(3); /* pause for 3 secs */
		printf("\nPARENT: sending SIGINT\n\n");
		kill(pid, SIGINT);
		sleep(3); /* pause for 3 secs */
		printf("\nPARENT: sending SIGQUIT\n\n");
		kill(pid, SIGQUIT);
		sleep(1);
	}
}

