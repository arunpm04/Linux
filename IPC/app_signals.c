#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "app_signals.h"
#include "app_debug.h"

struct sigaction app_sig_act;

/* @func		: app_sig_handler
 */
void app_sig_handler(int signo, siginfo_t *info, void *ctx)
{
	switch (signo) {
		case SIGINT:
			DBG("Siqueue data from info->si_int is %d\n", info->si_int);
			DBG("Siqueue data from info->si_value.sival_int is %d\n", info->si_value.sival_int);
			break;
		default:
			return;
			exit(0);
	}
}

/* @func		: mq_init
 * @param[in]	: Signal to be captured.
 * @return		: 0 if Success; else -1.
 */
int app_sig_init(int signo)
{
	app_sig_act.sa_sigaction = app_sig_handler;
	sigemptyset(&app_sig_act.sa_mask);
	sigaddset(&(app_sig_act.sa_mask), signo);
	/* Information transfer switch */
	app_sig_act.sa_flags = SA_SIGINFO;
	if (sigaction(signo, &app_sig_act, NULL) == -1) {
		ERR("Sigaction failed\n");
		return -1;
	}
	return 0;
}

/* @func		: mq_init
 * @param1[in]	: PID to be signalled.
 * @param2[in]	: Signal to be used.
 * @param3[in]	: pointer to Data payload.
 * @return		: 0 if Success; else -1.
 */
int app_sig_send(int pid, int signo, int Data)
{
	union sigval mysigval;
	mysigval.sival_int = Data;
	if (sigqueue(pid, signo, mysigval) == -1) {
		ERR("Sigqueue failed\n");
		return -1;
	}
	return 0;
}

