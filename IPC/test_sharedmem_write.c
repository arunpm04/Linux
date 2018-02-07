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

	/* One time initialization only needed.
	 * To enable lock-unlock of shared memeory write. */
	sem_init();

	if (shm_init(SHM_KEY) == FAILURE)
		return 0;

	sleep(1);

	for (i = 0; i < 10*2; i ++) {
		if (i%2)
			sprintf((char *)&app_info.version, "1.2.3.4.5");
		else
			sprintf((char *)&app_info.version, "AbCdEfGhIjKlMnOpQrStUvWxYz");
		app_info.testVar = i;
		shm_write(0, &app_info, sizeof(app_info));
		usleep(APP_MS_DELAY);
	}

	return SUCCESS;
}
