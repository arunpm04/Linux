# Linux
This repo contains some example codes intended to run on linux platform.  

###### IPC
A collection of sample C programs to illustrate Inter process communication mechanism.  
1. [x] Signals  
2. [x] Message Queues  
   - Generate the binaries using makefile. Run `msg_sender` and `msg_receiver` to see the communication. 
3. [x] Semaphores  
   - Generate example binary with `make semaphoretest` and run `semaphoretest` to see how it works.  
4. [x] Shared Memory  
   - Generate example binary with `make sharedmemtest` and use `shmreader and shmwriter` to see how it works.  
5. [x] Sockets  

###### Valgrind : for memory error/leakage detection
  Dependency: valgrind package support.  
  Usage:  
    Change permission settings to executable for IPC/check_leak.sh (chmod a+x IPC/check_leak.sh).  
    Run ./check_leak.sh <binary_name>  

