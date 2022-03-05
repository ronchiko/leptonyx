
#include <WinSock2.h>

#include "leptonyx/stringbuilder.h"
#include "leptonyx/socket.h"
#include "leptonyx/log.h"

#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_WAIT		10

typedef leptonyx_socket_address_family af_t;
typedef leptonyx_socket_protocol proto_t;
typedef leptonyx_socket_type sock_type_t;

int leptonyx_init_sockets(void) {
	static WSADATA data;

	if(WSAStartup(MAKEWORD(2, 2), &data) != 0) {
		return 0;
	}

	return 1;
}

void leptonyx_cleanup_sockets(void) {
	WSACleanup();
}

leptonyx_socket leptonyx_create_socket(af_t _af, proto_t _type, sock_type_t _proto) {
	if (_af < 0 || _af >= __LEPTONYX_ADDRESS_FAMILIES_END__ ||
		_type < 0 || _type >= __LEPTONYX_SOCKET_TYPES_END__ ||
		_proto < 0 || _proto >= __LEPTONYX_SOCKET_PROTOCOLS_END__) return NULL;
	
	int af = leptonyx_to_address_family[_af]; 
	int	proto = leptonyx_to_protocol[_proto];
	int	type = leptonyx_to_socket_type[_type];

	SOCKET sock;
	if((sock = socket(af, type, proto)) == INVALID_SOCKET) {
		return NULL;
	}

	return (leptonyx_socket)sock;
}

void leptonyx_close_socket(leptonyx_socket sock) {
	if (!sock) return;
	
	closesocket((SOCKET)sock);
}

leptonyx_error leptonyx_socket_send_in_batches(leptonyx_socket sock, leptonyx_message message, leptonyx_size batch_size) {
	if (!sock) return LEPTONYX_SOCKET_ERROR;
	
	for(int sent = 0; sent < message.count; sent += batch_size) {
		int bytes_sent = 0;
		if((bytes_sent = send((SOCKET)sock, message.bytes + sent, batch_size, 0)) <= 0) {
			// Error
			return LEPTONYX_SOCKET_ERROR;
		}
	}

	return LEPTONYX_OK;
}

leptonyx_error leptonyx_socket_send(leptonyx_socket sock, leptonyx_message message) {
	if (!sock) return LEPTONYX_SOCKET_ERROR;

	int bytes_sent = 0;
	if((bytes_sent = send((SOCKET)sock, message.bytes, message.count, 0)) <= 0) {
		// Error
		return LEPTONYX_SOCKET_ERROR;
	} 

	return LEPTONYX_OK;
}

leptonyx_message leptonyx_socket_recv(leptonyx_socket sock) {
	leptonyx_message result = leptonyx_create_empty_message();
	if (!sock) return result;

	leptonyx_string_builder sb = leptonyx_create_empty_string_builder();

	char buffer[1024];
	int bytes_recieved = 0;
	do {
		bytes_recieved = recv((SOCKET)sock, buffer, 1024, 0);
		leptonyx_log_info("Recieved %d bytes", bytes_recieved);
		
		if (bytes_recieved > 0)
			leptonyx_string_builder_append_raw(&sb, buffer, bytes_recieved);
	} while(bytes_recieved == 1024);

	result.bytes = leptonyx_string_builder_adopt_string(&sb, &result.count);
	leptonyx_free_string_builder(&sb);

	return result;
}

leptonyx_error leptonyx_socket_connect(leptonyx_socket sock, leptonyx_ipv4_address ip, leptonyx_port port) {
	if (!sock) return LEPTONYX_SOCKET_ERROR;
	
	struct sockaddr_in server; 
	memset(&server, 0, sizeof server);	

	char ipv4str[16];
	leptonyx_format_ipv4(ip, ipv4str, 15);
	ipv4str[15] = 0;

	server.sin_addr.s_addr = inet_addr(ipv4str);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);

	if(connect((SOCKET)sock, (struct sockaddr *)&server, sizeof server) < 0) {
		return LEPTONYX_SOCKET_ERROR;
	}

	return LEPTONYX_OK;
}

leptonyx_error leptonyx_socket_bind(leptonyx_socket sock, leptonyx_ipv4_address address, leptonyx_port port) {
	if(!sock) return LEPTONYX_SOCKET_ERROR;

	struct sockaddr_in server;
	memset(&server, 0, sizeof server);

	char ipv4str[16];
	leptonyx_format_ipv4(address, ipv4str, 15);
	ipv4str[15] = 0;

	server.sin_addr.s_addr = inet_addr(ipv4str);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);

	if (bind((SOCKET)sock, (struct sockaddr *)&server, sizeof server) != 0) {
		return LEPTONYX_SOCKET_ERROR;
	}

	return LEPTONYX_OK;
}

void leptonyx_socket_listen(leptonyx_socket sock, leptonyx_socket_callback callback, leptonyx_bool *kill) {

	if(listen((SOCKET)sock, SOMAXCONN) == SOCKET_ERROR) {
		return;
	}

	while (!*kill) {
		struct sockaddr inaddr;
		int length = sizeof inaddr;
		ZeroMemory(&inaddr, length);

		SOCKET acceptedSock;
		if((acceptedSock = accept((SOCKET)sock, &inaddr, &length)) == SOCKET_ERROR) {
			leptonyx_log_error("Failed to accept socket");
			continue;
		}

		(*callback)((leptonyx_socket)acceptedSock);

		closesocket((SOCKET)acceptedSock);
	}
}

void leptonyx_socket_select(leptonyx_socket sock, leptonyx_socket_callback callback, leptonyx_bool *kill) {
	WSAPOLLFD fdarray = { 0 };
	fdarray.fd = (SOCKET)sock;
	fdarray.events = POLLRDNORM;

	if(listen((SOCKET)sock, SOMAXCONN) == SOCKET_ERROR) {
		return;
	}

	for (;!*kill;) {
		// Check if we have a socket to accept from the listener
		int result;
		if((result = WSAPoll(&fdarray, 1, DEFAULT_WAIT)) == SOCKET_ERROR) {
			*kill = LEPTONYX_TRUE;
			return;
		}

		if (result) {
			if (fdarray.revents & POLLRDNORM) {
				
				SOCKET accpted_socket = accept((SOCKET)sock, NULL, NULL);
				if(accpted_socket == INVALID_SOCKET) {
					continue;
				}

				(*callback)((leptonyx_socket)accpted_socket);

				closesocket(accpted_socket);
			}
		}
	}

}