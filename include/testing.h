#pragma once

#include "leptonyx/log.h"

#define TESTS(...) int main(void) {\
	int result = 0;\
	__VA_ARGS__\
	return result;\
}

#define TEST(name) printf("Running test '"#name"'\n"); if(name()) { leptonyx_log_fatal(#name" Failed"); result |= 1; }

#define ASSERT(expr) if(!(expr)) { leptonyx_log_error("'"#expr"' failed"); result = 1; goto cleanup; }