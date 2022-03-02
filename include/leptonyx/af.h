#pragma once

#include <stdint.h>

#include "leptonyx/common.h"

typedef uint16_t leptonyx_port;
typedef uint32_t leptonyx_ipv4_address; 

typedef enum {
	LEPTONYX_IPV4_ANY = 0
} leptonyx_special_ipv4;

leptonyx_ipv4_address leptonyx_parse_ipv4(const char *ipv4);
void leptonyx_format_ipv4(leptonyx_ipv4_address ipv4, char *buffer, leptonyx_size limit);