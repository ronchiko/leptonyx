#pragma once

#include <stdint.h>

typedef uint8_t		leptonyx_bool;
typedef int8_t 		leptonyx_byte;
typedef uint32_t 	leptonyx_size;

typedef uint8_t 	leptonyx_error;

enum {
	LEPTONYX_TRUE 	= 1,
	LEPTONYX_FALSE	= 0
};

enum {
	LEPTONYX_OK = 0,
	LEPTONYX_SOCKET_ERROR = 1,
};