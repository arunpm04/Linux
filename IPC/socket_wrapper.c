/*
 * socket_wrapper.c
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

#include "socket_wrapper.h"
#include "app_debug.h"

void server_cleanup_socket(TCP_Socket_Server_Info_t *socket_info)
{
	if (socket_info->client_sock != TCPSOK_NONE) {
		shutdown(socket_info->client_sock, SHUT_RDWR);
		close(socket_info->client_sock);
		socket_info->client_sock = TCPSOK_NONE;
	}
	if (socket_info->socket_desc != TCPSOK_NONE) {
		shutdown(socket_info->socket_desc, SHUT_RDWR);
		close(socket_info->socket_desc);
		socket_info->socket_desc = TCPSOK_NONE;
	}
}
