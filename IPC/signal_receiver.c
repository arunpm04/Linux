#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "app_signals.h"
#include "app_debug.h"

int main(void)
{
	if (app_sig_init(SIGINT) == -1) {
		ERR("app_sig_init failed\n");
		exit(EXIT_FAILURE);
	}
	for (;;) {
		DBG("waiting a SIGINT signal....\n");
		pause();
	}
	return 0;
}
