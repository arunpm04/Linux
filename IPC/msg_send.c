#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "app_debug.h"
#include "app_mq.h"

int main(void)
{
	int mqID;
	int mq_free_space;

	mqID = mq_init(MQ_KEY);
	if (mqID >= 0) {
		int i;
		char msg[64];
		DBG("Message sending at 1 sec interval for 10 times...\n");
		for (i = 0; i < 300; i++) {
			//sleep(1);
			sprintf(msg, "Message %d", i);
			mq_free_space = mq_check_free_precent(mqID);
			if (mq_free_space == -1)
				ERR("mq_check_free_size failed\n");
			else if (mq_free_space > 10) {
				/* 10 % free space is enough. */
				mq_send(mqID, msg, (uint16_t)strlen(msg));
			}
		}
		DBG("Exiting...\n");
	} else
		ERR("Message queue init failed\n");

	return 0;
}
