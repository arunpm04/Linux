#Makefile_Begin

VERBOSE=@
USER=$(shell whoami)
CWD=$(shell pwd)
MACHINE_TYPE=$(shell uname -m)

CC=gcc
CFLAGS=-Werror=unused-variable -I. -DAPP_DEBUG_EN=3
LDFLAGS=

.PHONY: all signals messaging semaphoretest sockettest

#==============================================================================
# Build all Applications
#==============================================================================
all: signals messaging semaphoretest sockettest

clean: clean_signals clean_messaging clean_semaphoretest clean_sockettest

#==============================================================================
signals:
	$(CC) $(CFLAGS) $(LDFLAGS) -o signals $(CWD)/signals.c
clean_signals:
	$(RM) signals

messaging:
	$(CC) $(CFLAGS) -c $(CWD)/msg_send.c $(CWD)/msg_receive.c $(CWD)/app_mq.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o msg_sender $(CWD)/msg_send.c $(CWD)/app_mq.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o msg_receiver $(CWD)/msg_receive.c $(CWD)/app_mq.c
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

# Makefile_End
