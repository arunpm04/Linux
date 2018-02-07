#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "app_shm.h"
#include "app_debug.h"

static int shmid;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void sem_lock(void)
{
	pthread_mutex_lock(&mutex);
}

void sem_unlock(void)
{
	pthread_mutex_unlock(&mutex);
}

/**
 * @brief		: Initializes shared memory mutex lock.
 */
void sem_init(void)
{
	pthread_mutexattr_t shared;
	pthread_mutexattr_init(&shared);
	pthread_mutexattr_setpshared(&shared, PTHREAD_PROCESS_SHARED);
	pthread_mutex_init(&mutex, &shared);
}

/**
 * @brief		: Initializes shared memory.
 * @param1[in]	: Key to be passed to shmget.
 * @return		: return value from shmget;
 */
int shm_init(key_t key)
{
	shmid = shmget(key, SHM_MAP_SIZE, IPC_CREAT | 0660);
	if (shmid < 0) {
		shmid = shmget(key, 0, 0);
	}
	if (shmid < 0) {
		ERR("Shm_init failed\n");
		return FAILURE;
	} else {
		DBG("Shm_init success; shmid = %d\n", shmid);
	}
	return shmid;
}

/**
 * @brief		: Read shared memory.
 * @param1[in]	: memory offset to access.
 * @param2[out]	: destination buffer pointer.
 * @param3[in]	: data length to be read.
 * @return		: SUCCESS or FAILURE.
 */
int shm_read(int offset, void *buf, int length)
{
	char *pSrc = NULL;

	if (shmid < 0) {
		ERR("shm_init failed\n");
		return FAILURE;
	}
	pSrc = shmat(shmid, 0, 0);
	if (pSrc == NULL) {
		ERR("shm_read: attach failed");
		return FAILURE;
	}
	memcpy(buf, (pSrc + offset), length);
	if (shmdt(pSrc) == FAILURE) {
		ERR("shm_read: detach failed");
		return FAILURE;
	}
	return SUCCESS;
}

/**
 * @brief		: Writes to shared memory.
 * @param1[in]	: memory offset to access.
 * @param2[out]	: source buffer pointer.
 * @param3[in]	: data length to write.
 * @return		: SUCCESS or FAILURE.
 */
int shm_write(int offset, void *buf, int length)
{
	char *pDst;
	if (shmid < 0) {
		ERR("shm_init failed\n");
		return FAILURE;
	}
	pDst = shmat(shmid, 0, 0);
	if (pDst == NULL) {
		ERR("shm_write: attach failed");
		return FAILURE;
	}
	sem_lock();
	memcpy(pDst + offset, buf, length);
	sem_unlock();
	if (shmdt(pDst) == FAILURE) {
		ERR("shm_write: detach failed");
		return FAILURE;
	}
	return SUCCESS;
}
