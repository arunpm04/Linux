#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "app_debug.h"
#include "app_mq.h"

int main(void)
{
	int mqID;
	uint16_t size;

	mqID = mq_init(MQ_KEY);
	if (mqID >= 0) {
		char buff[100];
		DBG("Waiting...\n");
		while (1) {
			mq_recv(mqID, (uint8_t *)&buff, &size);
			DBG("Received: %s\n", buff);
			if (strcmp(buff, "Message 9") == 0) {
				DBG("Received last message\n");
				exit(0);
			}
		}
	} else
		ERR("mq_init failed\n");

	return 0;
}
