#include "logger.h"
#include "g_main.h"
#include <stdarg.h>


/** Minimum level of severity of logs to print */
static int logLevel = 0;

void L_InitLogger(int level) {
	logLevel = level;
}

void logFunc(FILE* file, int level, const char* format, va_list argv) {
	if (level >= logLevel) {
		printf("[%5.2f]: ", gameClock);

		vfprintf(file, format, argv);
	}
}


/** Logs a message with a default log level of 1 */
void L_Log(const char* format, ...) {
	va_list argv;
	va_start(argv, format);

	logFunc(stdout, 1, format, argv);

	va_end(argv);
}

void L_LogLevel(int level, const char* format, ...) {
	va_list argv;
	va_start(argv, format);

	logFunc(stdout, level, format, argv);

	va_end(argv);
}

/** Logs an error with a default log level of 1 */
void L_Err(const char* format, ...) {
	va_list argv;
	va_start(argv, format);

	logFunc(stderr, 1, format, argv);

	va_end(argv);
}

void L_ErrLevel(int level, const char* format, ...) {
	va_list argv;
	va_start(argv, format);

	logFunc(stderr, level, format, argv);

	va_end(argv);
}

