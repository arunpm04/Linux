#Makefile_Begin

VERBOSE=@
USER=$(shell whoami)
CWD=$(shell pwd)
MACHINE_TYPE=$(shell uname -m)

CC=gcc
CFLAGS=-Werror=unused-variable -I. -DAPP_DEBUG_EN=3
LDFLAGS=

.PHONY: all signals

#==============================================================================
# Build all Applications
#==============================================================================
all: signals messaging

clean: clean_signals clean_messaging

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

# Makefile_End
