/*
 * socket_wrapper.h
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>

/* Preprocessor macros */
#define SERVER_ADDRESS		"localhost"
#define TCP_SOCEKT_PORT		8000
#define SOCKET_BUF_SIZE		1024

/* Data types and enums */
typedef enum {
	TCPSOK_NONE = -1,
	TCPSOK_SOCKET_DONE = 0,
	TCPSOK_OPTION_DONE,
	TCPSOK_BIND_DONE,
	TCPSOK_LISTEN_DONE,
	TCPSOK_CONNECT_DONE,
	TCPSOK_ACCEPT_DONE,
} TCP_Socket_State_t;

typedef struct {
	int sock_opt;
	int socket_state;
	int retry_count;
	int bytes;
	struct sockaddr_in server;
	struct sockaddr_in client;
	int socket_desc;
	int client_sock;
} TCP_Socket_Server_Info_t;

typedef struct {
	int socket_state;
	int bytes;
	int socket_desc;
	struct sockaddr_in serveraddr;
	struct hostent *hostp;
} TCP_Socket_Client_Info_t;

/* Forward declaration */
void server_cleanup_socket(TCP_Socket_Server_Info_t *);

/* EoF */
