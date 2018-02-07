#Makefile_Begin

VERBOSE=@
USER=$(shell whoami)
CWD=$(shell pwd)
MACHINE_TYPE=$(shell uname -m)

CC=gcc
CFLAGS=-Werror=unused-variable -I. -DAPP_DEBUG_EN=3
LDFLAGS= -lm -lpthread

.PHONY: all signals messaging semaphoretest sockettest

#==============================================================================
# Build all Applications
#==============================================================================
all: signals messaging semaphoretest sockettest sharedmemtest

clean: clean_signals clean_messaging clean_semaphoretest clean_sockettest clean_sharedmemtest

#==============================================================================
signals:
	$(CC) $(CFLAGS) $(LDFLAGS) -o signals $(CWD)/signals.c
clean_signals:
	$(RM) signals

messaging:
	$(CC) $(CFLAGS) -o msg_sender $(CWD)/msg_send.c $(CWD)/app_mq.c $(LDFLAGS)
	$(CC) $(CFLAGS) -o msg_receiver $(CWD)/msg_receive.c $(CWD)/app_mq.c $(LDFLAGS)
clean_messaging:
	$(RM) msg_sender msg_receiver $(CWD)/app_mq.o $(CWD)/msg_send.o $(CWD)/msg_receive.o

semaphoretest:
	$(CC) $(CFLAGS) $(LDFLAGS) -o semaphoretest $(CWD)/semaphore_example.c -lpthread
clean_semaphoretest:
	$(RM) semaphoretest $(CWD)/semaphore_example.o

sockettest:
	$(CC) $(CFLAGS) $(LDFLAGS) -o sockettestServer $(CWD)/socket_wrapper.c $(CWD)/socket_server.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o sockettestClient $(CWD)/socket_client.c
clean_sockettest:
	$(RM) sockettestServer sockettestClient $(CWD)/socket_wrapper.o $(CWD)/socket_server.o

sharedmemtest:
	$(CC) $(CFLAGS) -o shmwriter $(CWD)/test_sharedmem_write.c $(CWD)/app_shm.c $(LDFLAGS)
	$(CC) $(CFLAGS) -o shmreader $(CWD)/test_sharedmem_read.c $(CWD)/app_shm.c $(LDFLAGS)

clean_sharedmemtest:
	$(CC) $(CFLAGS) -o shmwriter $(CWD)/test_sharedmem_write.c $(CWD)/app_shm.c $(LDFLAGS)
	$(CC) $(CFLAGS) -o shmreader $(CWD)/test_sharedmem_read.c $(CWD)/app_shm.c $(LDFLAGS)

# Makefile_End
