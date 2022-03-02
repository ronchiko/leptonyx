
#include <WinSock2.h>
#include "leptonyx/socket.h"

const int leptonyx_to_protocol[] = {
	[LEPTONYX_IP_TCP_SOCKET_PROTOCOL] = IPPROTO_TCP,
	[LEPTONYX_IP_UDP_SOCKET_PROTOCOL] = IPPROTO_UDP
};

const int leptonyx_to_address_family[] = {
	[LEPTONYX_INET_ADDRESS_FAMILY] = AF_INET,
	[LEPTONYX_INET6_ADDRESS_FAMILY] = AF_INET6
};

const int leptonyx_to_socket_type[] = {
	[LEPTONYX_DGRAM_SOCKET_TYPE] 	= SOCK_DGRAM,
	[LEPTONYX_STREAM_SOCKET_TYPE] 	= SOCK_STREAM
};