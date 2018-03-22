#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "app_signals.h"
#include "app_debug.h"

int main(int argc, char *argv[])
{
	pid_t pid = atoi(argv[1]);

	for (int i = 0; i < 10;  i++) {
		if (app_sig_send(pid, SIGINT, i) == 0) {
			DBG("Signalled %d with data %d\n", pid, i);
			sleep(1);
		} else {
			ERR("app_sig_send fauled\n");
			break;
		}
	}
    return 0;
}
