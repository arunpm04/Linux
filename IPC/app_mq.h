#ifndef __MSG_DEF_H__
#define __MSG_DEF_H__

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdint.h>

#define MQBUFSIZE (sizeof(message_buf_t)-sizeof(long))

typedef struct buf {
	long mtype;
	uint16_t length;
	uint8_t mtext[64];
} message_buf_t;

/* Application Related */
#define MQ_KEY	12345

/* Forward declaration */
int mq_init(int msgKey);
int mq_kill(int qid);
int mq_send(int mqId, uint8_t *buf, uint16_t size);
int mq_recv(int mqId, uint8_t *buf, uint16_t *size);

#endif /* __MSG_DEF_H__ */
