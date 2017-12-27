#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "app_debug.h"
#include "app_mq.h"

int main(void)
{
	int mqID;

	mqID = mq_init(MQ_KEY);
	if (mqID >= 0) {
		int i;
		char msg[64];
		DBG("Message sending at 1 sec interval for 10 times...\n");
		for (i = 0; i < 10; i++) {
			sleep(1);
			sprintf(msg, "Message %d", i);
			mq_send(mqID, msg, (uint16_t)strlen(msg));
		}
		DBG("Exiting...\n");
	} else
		ERR("Message queue init failed\n");

	return 0;
}
