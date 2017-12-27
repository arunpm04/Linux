#Makefile_Begin

VERBOSE=@
USER=$(shell whoami)
CWD=$(shell pwd)
MACHINE_TYPE=$(shell uname -m)

CC=gcc
CFLAGS=-Werror=unused-variable -I.
LDFLAGS=

.PHONY: all signals

#==============================================================================
# Build all Applications
#==============================================================================
all: signals

clean: clean_signals

#==============================================================================
signals:
	$(CC) $(CFLAGS) $(LDFLAGS) -o signals $(CWD)/signals.c
clean_signals:
	$(RM) signals

# Makefile_End
