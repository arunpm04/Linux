#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include "socket_wrapper.h"
#include "app_debug.h"

/* TCP Socket Client Application */
int main(int argc, char *argv[])
{
	TCP_Socket_Client_Info_t client_info;
	int rc, length = sizeof(int);
	size_t read_size;
	char client_message[SOCKET_BUF_SIZE];
	char server[255];
	char temp;
	struct hostent *hostp;
	char data[100] = "This is a test string from client lol!!! ";

	/*If the server hostname is supplied*/
	if (argc > 1) {
		/*Use the supplied argument*/
		strcpy(server, argv[1]);
		printf("Connecting to %s : %d ...\n", server, TCP_SOCEKT_PORT);
	} else {
		/*Use the default server name or IP*/
		strcpy(server, SERVER_ADDRESS);
	}

	/* get a socket descriptor */
	if((client_info.socket_desc = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		ERR("Client-socket() error\n");
	} else
		DBG("Client-socket() OK\n");

	memset(&client_info.serveraddr, 0x00, sizeof(struct sockaddr_in));
	client_info.serveraddr.sin_family = AF_INET;
	client_info.serveraddr.sin_port = htons(TCP_SOCEKT_PORT);

	if ((client_info.serveraddr.sin_addr.s_addr = inet_addr(server)) == (unsigned long)INADDR_NONE) {
		hostp = gethostbyname(server);
		if(client_info.hostp == (struct hostent *)NULL) {
			ERR("HOST NOT FOUND --> h_errno = %d\n", h_errno);
			ERR("Command usage: %s <server name or IP>\n", argv[0]);
			close(client_info.socket_desc);
			exit(-1);
		}
		memcpy(&client_info.serveraddr.sin_addr, client_info.hostp->h_addr, sizeof(client_info.serveraddr.sin_addr));
	}

	/* connect() to server. */
	if ((rc = connect(client_info.socket_desc, (struct sockaddr *)&client_info.serveraddr, sizeof(client_info.serveraddr))) < 0) {
		ERR("Client-connect() error");
		close(client_info.socket_desc);
		exit(-1);
	}
	else
		DBG("Connection established...\n");

	while (1) {
		rc = send(client_info.socket_desc, data, sizeof(data), MSG_CONFIRM);
		if(rc < 0) {
			ERR("Client-write() error");
			rc = getsockopt(client_info.socket_desc, SOL_SOCKET, SO_ERROR, &temp, &length);
			if(rc == 0) {
				/* Print out the asynchronously received error. */
				errno = temp;
				perror("SO_ERROR was");
				break;
			}
			close(client_info.socket_desc);
			exit(-1);
		}

		if ((read_size = recv(client_info.socket_desc, client_message , SOCKET_BUF_SIZE, 0)) > 0) {
			DBG("Data - %s\n", client_message);
		} else if (read_size == 0) {
			ERR("Client disconnected from Server\n");
			break;
		} else if (read_size < 0) {
			ERR("Error on socket recv(): %s\n", strerror(errno));
			break;
		}
		sprintf(data, "Sample data from client");
		sleep(5);
	}

	shutdown(client_info.socket_desc, SHUT_RDWR);
	close(client_info.socket_desc);
	ERR("Client exiting...\n");
	return 0;
}
