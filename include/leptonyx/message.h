#pragma once

#include "leptonyx/common.h"

typedef struct {
	leptonyx_size count;
	leptonyx_byte *bytes;
} leptonyx_message;

leptonyx_message leptonyx_create_empty_message(void);
leptonyx_message leptonyx_create_message(leptonyx_string restrict message);