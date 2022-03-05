
#include <stdlib.h>
#include <string.h>

#include "leptonyx/socket.h"

leptonyx_message leptonyx_create_empty_message(void) {
	return (leptonyx_message){ 
		.bytes = NULL,
		.count = 0
	};
}

leptonyx_message leptonyx_create_message(const char *restrict string) {
	leptonyx_message message = leptonyx_create_empty_message();
	if (!string) {
		return message;
	}

	if(message.count = strlen(string)) {
		message.bytes = malloc(sizeof(leptonyx_byte) * message.count);

		strncpy(message.bytes, string, message.count);
		return message;
	} else 
		return message;
}