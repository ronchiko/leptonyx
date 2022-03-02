
#include <string.h>

#include "leptonyx/stringbuilder.h"
#include "leptonyx/log.h"
#include "leptonyx/socket.h"

static leptonyx_bool gKillSwitch = LEPTONYX_FALSE;

void on_connection_accepted(leptonyx_socket socket) {
	leptonyx_socket_message message = leptonyx_socket_recv(socket);
	if (message.count == 0 || !message.bytes) {
		leptonyx_log_error("Got empty message");
		return;
	}

	leptonyx_socket_send(socket, message);

	if (memcmp(message.bytes, "quit", message.count) == 0) {
		gKillSwitch = LEPTONYX_TRUE;
	}

}

int main(int argc, char *argv[]) {
	leptonyx_log_info("Starting Leptonyx HTTP server");

	if (!leptonyx_init_sockets()) {
		leptonyx_log_fatal("Couldn't initialize sockets");
		return 1;
	}
	
	leptonyx_socket socket = leptonyx_create_socket(
		LEPTONYX_INET_ADDRESS_FAMILY, LEPTONYX_STREAM_SOCKET_TYPE, LEPTONYX_IP_TCP_SOCKET_PROTOCOL);
	
	leptonyx_socket_bind(socket, leptonyx_parse_ipv4("0.0.0.0"), 5000);
	leptonyx_socket_listen(socket, &on_connection_accepted, &gKillSwitch);
	
	leptonyx_close_socket(socket);	

	leptonyx_cleanup_sockets();
	leptonyx_log_info("Leptonyx out!");
	return 0;
}