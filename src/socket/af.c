
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "leptonyx/af.h"

#define EXTRACT_IPV4_SEGMENT(v, s) (((v) >> ((s) << 3)) & 0xFF)

leptonyx_ipv4_address leptonyx_parse_ipv4(const char *address) {
	leptonyx_ipv4_address ipv4 = LEPTONYX_IPV4_ANY;
	if (!address) return ipv4;

	uint8_t i = 0;
	for(; i < 4 && *address; ++i) {
		int next = 0;
		for(;next < 4 && *(address + next) != '.' && *(address + next) != 0; ++next);

		if (next >= 4 || next <= 0) return LEPTONYX_IPV4_ANY;

		char digits[4];
		memcpy(digits, address, next * sizeof(char));
		digits[next] = 0;

		int32_t segment = atoi(digits); 
		if (0 > segment || segment >= 256) 
			return LEPTONYX_IPV4_ANY;

		ipv4 |= ((uint8_t)segment) << (i << 3);
		address += next + 1;
	} 

	if(i != 4) { return LEPTONYX_IPV4_ANY; }

	return ipv4;
}

void leptonyx_format_ipv4(leptonyx_ipv4_address ipv4, char *buffer, leptonyx_size limit) {
	snprintf(buffer, limit, "%d.%d.%d.%d", EXTRACT_IPV4_SEGMENT(ipv4, 0), EXTRACT_IPV4_SEGMENT(ipv4, 1),
		EXTRACT_IPV4_SEGMENT(ipv4, 2), EXTRACT_IPV4_SEGMENT(ipv4, 3));
}