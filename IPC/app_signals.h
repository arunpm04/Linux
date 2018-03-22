#ifndef __APP_SIGNALS_H__
#define __APP_SIGNALS_H__

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

struct sigaction app_sig_act;

void app_sig_handler(int signo, siginfo_t *info, void *ctx);
int app_sig_init(int signo);
int app_sig_send(int pid, int signo, int Data);

#endif /* __APP_SIGNALS_H__ */
