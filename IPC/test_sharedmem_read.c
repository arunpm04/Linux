#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "app_debug.h"
#include "app_shm.h"

#define APP_MS_DELAY	(1000*500)

int main(void)
{
	int i;
	AppInfo_t app_info;
//	sem_init();

	if (shm_init(SHM_KEY) == FAILURE)
		return 0;

	sleep(1);

	for (i = 0; i < 10*2; i++) {
		shm_read(0, &app_info, sizeof(app_info));
		printf("Read: %d\n", app_info.testVar);
		printf("Read: %s\n", app_info.version);
		usleep(APP_MS_DELAY);
	}

	return SUCCESS;
}
