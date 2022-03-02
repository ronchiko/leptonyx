
#include <stdio.h>
#include <stdarg.h>

#include "leptonyx/log.h"

#define INFO_LOG_PREFIX 	"\033[34;1mINFO\033[0m"
#define WARN_LOG_PREFIX 	"\033[33;1mWARNING\033[0m"
#define ERROR_LOG_PREFIX 	"\033[31mERROR\033[0m"
#define FATAL_LOG_PREFIX 	"\033[31;1mFATAL\033[0m"

static int logger_busy = 0;

static void leptonyx_log_generic(const char *prefix, const char *fmt, va_list args) {
	while(logger_busy); logger_busy = 1;

	if(prefix) {
		printf("[%s]: ", prefix);
	}

	vprintf(fmt, args);
	printf("\n");
	logger_busy = 0;

	va_end(args);
}

void leptonyx_log_info(const char *fmt, ...) {
	va_list list;
	va_start(list, fmt);

	leptonyx_log_generic(INFO_LOG_PREFIX, fmt, list);
}

void leptonyx_log_error(const char *fmt, ...) {
	va_list list;
	va_start(list, fmt);

	leptonyx_log_generic(ERROR_LOG_PREFIX, fmt, list);
}

void leptonyx_log_fatal(const char *fmt, ...) {
	va_list list;
	va_start(list, fmt);

	leptonyx_log_generic(FATAL_LOG_PREFIX, fmt, list);
}