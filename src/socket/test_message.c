
#include <string.h>

#include "leptonyx/socket.h"

#include "testing.h"

int test_create_message_when_valid_string_then_create_message(void) {
	int result = 0;

	const char *MESSAGE = "Im a unique message";

	leptonyx_message message = leptonyx_create_message(MESSAGE);
	ASSERT(message.count == strlen(MESSAGE));
	ASSERT(strncmp(message.bytes, MESSAGE, strlen(MESSAGE)) == 0);

cleanup:
	return result;
}

int test_create_message_when_string_null_then_return_empty_message(void) {
	int result = 0;
	
	leptonyx_message message = leptonyx_create_message(NULL);
	ASSERT(message.count == 0);
	ASSERT(message.bytes == NULL);

cleanup:
	return result;
}


int test_create_message_when_string_empty_then_return_empty_message(void) {
	int result = 0;

	leptonyx_message message = leptonyx_create_message("");
	ASSERT(message.count == 0);
	ASSERT(message.bytes == NULL);

cleanup:
	
	return result;
}

TESTS(
	TEST(test_create_message_when_valid_string_then_create_message);
	TEST(test_create_message_when_string_empty_then_return_empty_message);
	TEST(test_create_message_when_string_null_then_return_empty_message);
)