#ifndef maromitaz_cli_log
#define maromitaz_cli_log

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

#ifndef __cplusplus
typedef signed char bool;
#	define true 1
#	define false 0
#endif

char* file_name = "log.txt";

// https://en.wikipedia.org/wiki/ANSI_escape_code
char f[] = "\033[0m";
struct log_data_type {
	char terminal_font[8];
	char* log_level;
	char terminal_reset[5];
};

struct log_data_type log_level[] = {
	{.terminal_font = "\033[37;1m", .log_level = "[INFO] ", .terminal_reset = "\033[0m"},
	{.terminal_font = "\033[33;1m", .log_level = "[WARNING] ", .terminal_reset = "\033[0m"},
  {.terminal_font = "\033[31;1m", .log_level = "[ERROR] ", .terminal_reset = "\033[0m"},
  {.terminal_font = "\033[31;1m", .log_level = "[PANIC] ", .terminal_reset = "\033[0m"}
;

enum {
	LOG_INFO = 0,
	LOG_WARNING = 1,
	LOG_ERROR = 2,
	LOG_PANIC = 3
};

#ifdef __cplusplus
extern "C"{
#endif
void save_log_to_file(char* log_message) {
	FILE* file = fopen(file_name, "a");
	fprintf(file, log_message);
	fprintf(file, "\n");
	fclose(file);
}
#ifdef __cplusplus
}
#endif

#define log(level, args, ...) _log(level, args, __VA_ARGS__, (void *)0)

#ifdef __cplusplus
extern "C"{
#endif
void _log(short level, char* args, ...) {
	if (level < LOG_INFO || level > LOG_PANIC) {
		fprintf(stderr, "%s Logging level unknown", log_level[3]);
		exit(1);
	}

	size_t allocation_size = strlen(args);

	va_list ptr;
	va_start(ptr, args);
	for (char* arg = va_arg(ptr, char*); arg != NULL; arg = va_arg(ptr, char*)) {
		allocation_size += strlen(arg);
	}
	va_end(ptr);
	allocation_size += strlen(log_level[level].log_level);

	char* log_message = (char*)malloc(allocation_size + 2);
	memset(log_message, 0, allocation_size + 2);
	strcat(log_message, log_level[level].log_level);
	strcat(log_message, args);

	printf("%s", log_level[level].terminal_font);
	printf("%s", log_level[level].log_level);
	printf("%s", log_level[level].terminal_reset);
	printf("%s", args);

	va_start(ptr, args);
	for (char* arg = va_arg(ptr, char*); arg != NULL; arg = va_arg(ptr, char*)) {
		printf("%s", arg);
		strcat(log_message, arg);
	}
	va_end(ptr);

	printf("\n");
	save_log_to_file(log_message);
	free(log_message);
	if (level == LOG_PANIC) exit(1);
}
#ifdef __cplusplus
}
#endif

struct custom_log_level
{
	short color;
	char* log_symbol;
};

enum COLORS {
	BLACK,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	MAGENTA,
	CYAN,
	WHITE
};

char colors_array[][3] = {
	"30",
	"31",
	"32",
	"33",
	"34",
	"35",
	"36",
	"37"
};

#define custom_log(log_level, begin, ...) _custom_log(log_level, begin, __VA_ARGS__, (void *)0)

#ifdef __cplusplus
extern "C"{
#endif
void _custom_log(struct custom_log_level log_level, char* begin, ...) {
	size_t alloc = 0;

	printf("\033[%s", colors_array[log_level.color]);
	printf("m");

	printf("[%s] \033[0m", log_level.log_symbol);
	alloc += strlen(log_level.log_symbol) + 2;

	printf("%s", begin);
	alloc += strlen(begin);

	va_list ptr;
	va_start(ptr, begin);
	for (char* next = va_arg(ptr, char*); next != NULL; next = va_arg(ptr, char*)) {
		alloc += strlen(next);
		printf("%s", next);
	}
	va_end(ptr);

	printf("\n");

	char* log_message = (char*)malloc(alloc + 2);
	memset(log_message, 0, alloc + 2);
	strcat(log_message, "[");
	strcat(log_message, log_level.log_symbol);
	strcat(log_message, "] ");
	strcat(log_message, begin);

	va_start(ptr, begin);
	for (char* next = va_arg(ptr, char*); next != NULL; next = va_arg(ptr, char*)) {
		strcat(log_message, next);
	}
	va_end(ptr);

	save_log_to_file(log_message);
	free(log_message);
}
#ifdef __cplusplus
}
#endif

#endif
