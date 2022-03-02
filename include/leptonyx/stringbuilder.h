#pragma once

#include "leptonyx/common.h"


typedef struct leptonyx_string_builder {
	leptonyx_size length;
	leptonyx_size alloced;
	leptonyx_byte *buffer;
} leptonyx_string_builder;

leptonyx_string_builder leptonyx_create_empty_string_builder(void);
leptonyx_string_builder leptonyx_create_string_builder(const char *string);

void leptonyx_string_builder_append(leptonyx_string_builder *sb, const char *string); // Expects null terminated string
void leptonyx_string_builder_append_raw(leptonyx_string_builder *sb, const char *raw, leptonyx_size count);

// After this call the string builder reverts to an empty state, the caller is responsible for releasing the buffer
leptonyx_byte *leptonyx_string_builder_adopt_string(leptonyx_string_builder *sb, leptonyx_size *length);

// Clones the string into a user allocated buffer, without destroying the string
leptonyx_size leptonyx_string_builder_copy_string(leptonyx_string_builder *sb, leptonyx_byte *buffer);

void leptonyx_free_string_builder(leptonyx_string_builder *);

