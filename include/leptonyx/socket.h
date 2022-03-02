#pragma once

#include "leptonyx/common.h"
#include "leptonyx/af.h"

typedef enum {
	LEPTONYX_STREAM_SOCKET_TYPE,
	LEPTONYX_DGRAM_SOCKET_TYPE,

	__LEPTONYX_SOCKET_TYPES_END__
} leptonyx_socket_type;

typedef enum {
	LEPTONYX_INET_ADDRESS_FAMILY,
	LEPTONYX_INET6_ADDRESS_FAMILY,

	__LEPTONYX_ADDRESS_FAMILIES_END__
} leptonyx_socket_address_family;

typedef enum {
	LEPTONYX_IP_TCP_SOCKET_PROTOCOL,
	LEPTONYX_IP_UDP_SOCKET_PROTOCOL,

	__LEPTONYX_SOCKET_PROTOCOLS_END__
} leptonyx_socket_protocol;

typedef struct {
	leptonyx_size count;
	leptonyx_byte *bytes;
} leptonyx_socket_message;

leptonyx_socket_message leptonyx_create_empty_message(void);
leptonyx_socket_message leptonyx_create_message(const char *restrict message);

typedef void *leptonyx_socket;

int leptonyx_init_sockets(void);
void leptonyx_cleanup_sockets(void);

leptonyx_socket leptonyx_create_socket(leptonyx_socket_address_family, leptonyx_socket_type, leptonyx_socket_protocol);

void leptonyx_socket_set_nonblocking(leptonyx_socket socket, leptonyx_bool nonblocking);

leptonyx_error leptonyx_socket_bind(leptonyx_socket socket, leptonyx_ipv4_address host, leptonyx_port port);
leptonyx_error leptonyx_socket_connect(leptonyx_socket sock, leptonyx_ipv4_address ip, leptonyx_port port);

typedef void (*leptonyx_socket_callback)(leptonyx_socket);

void leptonyx_socket_listen(leptonyx_socket socket, leptonyx_socket_callback callback, leptonyx_bool *killswitch);
void leptonyx_socket_select(leptonyx_socket socket, leptonyx_socket_callback callback, leptonyx_bool *killswitch);

leptonyx_socket_message leptonyx_socket_recv(leptonyx_socket socket);

leptonyx_error leptonyx_socket_send(leptonyx_socket socket, leptonyx_socket_message message);
leptonyx_error leptonyx_socket_send_in_batches(leptonyx_socket socket, leptonyx_socket_message message, leptonyx_size batch_size);

void leptonyx_close_socket(leptonyx_socket socket);