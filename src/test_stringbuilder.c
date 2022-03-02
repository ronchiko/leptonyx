
#include <string.h>

#include "leptonyx/stringbuilder.h"

#include "testing.h"


int test_create_string_builder_when_string_empty_then_create_empty_stringbuilder(void) {
	int result = 0;

	leptonyx_string_builder sb = leptonyx_create_string_builder("");

	ASSERT(sb.alloced == 0);
	ASSERT(sb.length == 0);
	ASSERT(sb.buffer == NULL);

cleanup:
	leptonyx_free_string_builder(&sb);

	return result;
}

int test_create_string_builder_when_string_null_then_create_empty_stringbuilder(void) {
	int result = 0;

	leptonyx_string_builder sb = leptonyx_create_string_builder(NULL);

	ASSERT(sb.alloced == 0);
	ASSERT(sb.length == 0);
	ASSERT(sb.buffer == NULL);

cleanup:
	leptonyx_free_string_builder(&sb);
		
	return result;
}

int test_create_string_builder_when_string_valid_then_create_initialized_stringbuilder(void) {
	int result = 0;

	leptonyx_string_builder sb = leptonyx_create_string_builder("Hello, World!");

	ASSERT(strcmp(sb.buffer, "Hello, World!") == 0);

cleanup:
	leptonyx_free_string_builder(&sb);
		
	return result;
}

int test_string_builder_append_when_string_valid_then_append_string(void) {
	int result = 0;

	leptonyx_string_builder sb = leptonyx_create_string_builder("Hello, ");
	leptonyx_string_builder_append(&sb, "World!");

	ASSERT(strcmp(sb.buffer, "Hello, World!") == 0);

cleanup:
	leptonyx_free_string_builder(&sb);
		
	return result;
}

int test_string_builder_append_when_string_empty_then_dont_append(void) {
	int result = 0;

	leptonyx_string_builder sb = leptonyx_create_string_builder("Hello, ");
	leptonyx_string_builder_append(&sb, "");

	ASSERT(strcmp(sb.buffer, "Hello, ") == 0);

cleanup:
	leptonyx_free_string_builder(&sb);
		
	return result;
}

int test_string_builder_append_when_string_null_then_dont_append(void) {
	int result = 0;

	leptonyx_string_builder sb = leptonyx_create_string_builder("Hello, ");
	leptonyx_string_builder_append(&sb, NULL);

	ASSERT(strcmp(sb.buffer, "Hello, ") == 0);

cleanup:
	leptonyx_free_string_builder(&sb);
		
	return result;
}

int test_string_builder_append_when_source_string_empty_then_append_string(void) {
	int result = 0;

	leptonyx_string_builder sb = leptonyx_create_string_builder(NULL);
	leptonyx_string_builder_append(&sb, "World!");

	ASSERT(strcmp(sb.buffer, "World!") == 0);

cleanup:
	leptonyx_free_string_builder(&sb);
		
	return result;
}

int test_string_builder_append_when_source_string_empty_then_append_raw_string(void) {
	int result = 0;

	const char chars[] = { '0', 0, 'h', 'g', 1 };

	leptonyx_string_builder sb = leptonyx_create_string_builder(NULL);
	leptonyx_string_builder_append_raw(&sb, chars, 5);

	ASSERT(memcmp(sb.buffer, chars, 5) == 0);

cleanup:
	leptonyx_free_string_builder(&sb);
		
	return result;
}

TESTS(
	TEST(test_create_string_builder_when_string_empty_then_create_empty_stringbuilder);
	TEST(test_create_string_builder_when_string_null_then_create_empty_stringbuilder);
	TEST(test_create_string_builder_when_string_valid_then_create_initialized_stringbuilder);

	TEST(test_string_builder_append_when_string_valid_then_append_string);
	TEST(test_string_builder_append_when_source_string_empty_then_append_string);
	TEST(test_string_builder_append_when_string_empty_then_dont_append);
	TEST(test_string_builder_append_when_string_null_then_dont_append);
	TEST(test_string_builder_append_when_source_string_empty_then_append_raw_string);
)