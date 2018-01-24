#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "socket_wrapper.h"
#include "app_debug.h"

TCP_Socket_Server_Info_t server_socket_info;
static int server_exit_triggered;

/*
 * @brief		: Handler to process the client messages.
 * @param1[in]	: pointer to the client request buffer.
 * @param2[out]	: pointer to the server response buffer.
 * @retval		: If failure; -1; else length of response in bytes.
 */
int process_request(char *request, char *response)
{
	if (strcmp(request, "test")) {
		sprintf(response, "test passed\n");
		return strlen(response);
	}
	return -1;
}

/* TCP Socket Server Application */
int main(void)
{
	size_t c, read_size;
	int process_status;
	char client_message[SOCKET_BUF_SIZE];
	char response_buffer[SOCKET_BUF_SIZE];

	/* RESTART_SOCKET */
	do {
		/* Reset all */
		server_socket_info.socket_state = TCPSOK_NONE;
		server_socket_info.socket_desc = TCPSOK_NONE;
		server_socket_info.sock_opt = 1;
		bzero(&server_socket_info.server, sizeof(server_socket_info.server));
		server_socket_info.server.sin_family = AF_INET;
		server_socket_info.server.sin_addr.s_addr = INADDR_ANY;
		server_socket_info.server.sin_port = htons(TCP_SOCEKT_PORT);
		server_socket_info.client_sock = TCPSOK_NONE;

		do {
			switch (server_socket_info.socket_state) {
				case TCPSOK_NONE:
					server_socket_info.socket_desc = socket(AF_INET , SOCK_STREAM , 0);
					if (server_socket_info.socket_desc == -1) {
						ERR("Socket[%d] creation failed\n", TCP_SOCEKT_PORT);
						sleep(2);
					} else {
						DBG("Socket[%d] creation success\n", TCP_SOCEKT_PORT);
						server_socket_info.socket_state = TCPSOK_SOCKET_DONE;
					}
					break;
				case TCPSOK_SOCKET_DONE:
					/* avoid "Address already in use" error message */
					if (setsockopt(server_socket_info.socket_desc, SOL_SOCKET, SO_REUSEADDR, &server_socket_info.sock_opt, sizeof(server_socket_info.sock_opt)) == -1) {
						ERR("Setsockopt failed\n");
						sleep(2);
					} else {
						DBG("Setsockopt success\n");
						server_socket_info.socket_state = TCPSOK_OPTION_DONE;
					}
					break;
				case TCPSOK_OPTION_DONE:
					if (bind(server_socket_info.socket_desc, (struct sockaddr *)&server_socket_info.server, sizeof(server_socket_info.server)) != 0) {
						server_socket_info.retry_count++;
						ERR("Socket bind failed [%d]\n", server_socket_info.retry_count);
						sleep(2);
					} else {
						DBG("Socket bind success\n");
						server_socket_info.socket_state = TCPSOK_BIND_DONE;
					}
					break;
				case TCPSOK_BIND_DONE:
					/* Listen */
					if (listen(server_socket_info.socket_desc, 2) != 0) {
						ERR("Socket listen failed\n");
						sleep(2);
					} else {
						DBG("Socket listen success, Waiting for incoming connections from client...\n");
						server_socket_info.socket_state = TCPSOK_LISTEN_DONE;
					}
					break;
				case TCPSOK_LISTEN_DONE:
					/* accept connection from an incoming client */
					c = sizeof(struct sockaddr_in);
					server_socket_info.client_sock = accept(server_socket_info.socket_desc, (struct sockaddr *)&server_socket_info.client, (socklen_t*)&c);
					if (server_socket_info.client_sock < 0) {
						ERR("Socket accept failed\n");
						sleep(2);
					} else {
						DBG("Socket accept success\n");
						server_socket_info.socket_state = TCPSOK_ACCEPT_DONE;
					}
					break;
				case TCPSOK_ACCEPT_DONE:
					/* All seems fine. Ready for data transfer. */
					break;
			}
		} while ((server_socket_info.socket_state != TCPSOK_ACCEPT_DONE) || (server_exit_triggered == 0));

		/* Get data from client */
		while (server_exit_triggered == 0) {
			/* Check if data is available for read. */
			memset(client_message, 0, sizeof(client_message));
			if ((read_size = recv(server_socket_info.client_sock , client_message , SOCKET_BUF_SIZE, 0)) > 0) {
				DBG("Data - %s\n", client_message);
				process_status = process_request(client_message, response_buffer);
				if (process_status > 0) {
				} else {
					sprintf(response_buffer, "Cannot process client request\n");
				}
				server_socket_info.bytes = send(server_socket_info.client_sock, response_buffer, strlen(response_buffer), MSG_CONFIRM);
				if (server_socket_info.bytes == -1) {
					ERR("Send failed\n");
				}
			} else if (read_size == 0) {
				ERR("Client disconnected from Server\n");
				server_cleanup_socket(&server_socket_info);
				break;
			} else if (read_size < 0) {
				ERR("Error on socket recv(): %s\n", strerror(errno));
				server_cleanup_socket(&server_socket_info);
				break;
			} else if (server_exit_triggered != 0) {
				server_cleanup_socket(&server_socket_info);
				break;
			}
		}
	} while (server_exit_triggered == 0);

	/* System exit triggered. */
	ERR("Server exit triggered: %d\n", server_exit_triggered);
}
