#ifndef __APP_SHM_H__
#define __APP_SHM_H__

#define SHM_KEY	9469875
#define SHM_MAP_SIZE	1024

typedef enum {
	FAILURE = -1,
	SUCCESS,
} App_Error_t;

typedef struct {
	int testVar;
	char version[40];
} AppInfo_t;

void sem_init(void);
int shm_init(key_t key);
int shm_read(int offset, void *buf, int length);
int shm_write(int offset, void *buf, int length);

#endif /* __APP_SHM_H__ */
