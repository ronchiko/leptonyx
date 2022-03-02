
#include <string.h>
#include <stdlib.h>

#include "leptonyx/stringbuilder.h"

#define MINIMUM_APPENDING_LENGTH 100

leptonyx_string_builder leptonyx_create_empty_string_builder(void) {
	return (leptonyx_string_builder) {
		.alloced = 0,
		.length = 0,
		.buffer = NULL
	};
}

leptonyx_string_builder leptonyx_create_string_builder(const char *string) {
	leptonyx_string_builder sb = leptonyx_create_empty_string_builder();
	
	if (!string) 
		return sb;

	if (sb.length = strlen(string)) {
		sb.alloced = sb.length + 1;
		sb.buffer = malloc(sizeof(leptonyx_byte) * sb.alloced);

		strncpy(sb.buffer, string, sb.length);
		sb.buffer[sb.length] = 0;
	}

	return sb;
}

leptonyx_byte *leptonyx_string_builder_adopt_string(leptonyx_string_builder *sb, leptonyx_size *length) {
	if (!sb) return NULL;

	leptonyx_byte *pointer = sb->buffer;

	if(length) *length = sb->length;

	sb->buffer = NULL;
	sb->alloced = 0;
	sb->length = 0;

	return pointer;
}

leptonyx_size leptonyx_string_builder_copy_string(leptonyx_string_builder *sb, leptonyx_byte *buffer) {
	if(!sb || !buffer) return 0;

	strncpy(sb->buffer, buffer, sb->alloced);
	return sb->length; 
}

void leptonyx_string_builder_append(leptonyx_string_builder *sb, const char *string) {
	if(!sb || !string) return;

	leptonyx_size length = strlen(string);
	if(!length) return;

	if (sb->length + length + 1 >= sb->alloced) {
		leptonyx_size extend = max(length + 1, MINIMUM_APPENDING_LENGTH);
	
		sb->buffer = realloc(sb->buffer, sizeof(leptonyx_byte) * (sb->alloced += extend));
	}

	strncpy(sb->buffer + sb->length, string, length * sizeof(char));
	sb->buffer[sb->length += length] = 0;
}


void leptonyx_string_builder_append_raw(leptonyx_string_builder *sb, const char *raw, leptonyx_size count) {
	if(!sb || !raw) return;

	if(!count) return;

	if (sb->length + count + 1 >= sb->alloced) {
		leptonyx_size extend = max(count + 1, MINIMUM_APPENDING_LENGTH);
	
		sb->buffer = realloc(sb->buffer, sizeof(leptonyx_byte) * (sb->alloced += extend));
	}

	memcpy(sb->buffer + sb->length, raw, count * sizeof(char));
	sb->buffer[sb->length += count] = 0;
}


void leptonyx_free_string_builder(leptonyx_string_builder *sb) {
	if (!sb) return;

	if (sb->alloced > 0) free(sb->buffer);
	
	sb->length = 0;
	sb->alloced = 0;
	sb->buffer = NULL;
}

