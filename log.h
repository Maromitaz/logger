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

#define MAX_FILE_NAME 255

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <direct.h>

// Will set the file path to the point of execution, or simply said: where program in storage

char file_path[MAX_PATH] = { 0 };
char save_to[MAX_FILE_NAME] = "log.txt";

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

void file_init() {
	if (!GetModuleFileNameA(NULL, file_path, MAX_PATH)) {
		printf("Error while trying to get the execution path, error: %d", GetLastError());
	}
	size_t file_buffer_size = strlen(file_path);
	for (file_buffer_size; file_buffer_size >= 0; file_buffer_size--) {
		if (file_path[file_buffer_size] == '/' || file_path[file_buffer_size] == '\\') {
			break;
		}
	}
	file_path[file_buffer_size + 1] = '\0';
}

void set_path(char* c_path) {
	strcpy(file_path, c_path);
}

void set_path_to_temp() {
	if (!GetTempPathA(MAX_PATH, file_path)) {
		printf("Error while trying to get the temp folder path, error: %d", GetLastError());
	}
}

void set_file_name(char* c_name) {
	strcpy(save_to, c_name);
}

#ifdef __cplusplus
}
#endif // __cplusplus

#else
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#define MAX_PATH 255

char file_path[MAX_PATH] = { 0 };
char save_to[MAX_FILE_NAME] = "log.txt";


#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

// Defining the 
#ifdef __linux__
#define EXEC_PATH_OS_DEFINED "/proc/self/exe"
#elif __bsdi__
#define EXEC_PATH_OS_DEFINED "/proc/curproc/file"
#endif // __linux__ && __bsdi__

void file_init() {
	if (readlink(EXEC_PATH_OS_DEFINED, file_path, MAX_PATH) == -1) {
		printf("Error while trying to get the execution path, error: %d", errno);
	}
	size_t file_buffer_size = strlen(file_path);
	for (file_buffer_size; file_buffer_size >= 0; file_buffer_size--) {
		if (file_path[file_buffer_size] == '/') {
			break;
		}
	}
	file_path[file_buffer_size + 1] = '\0';
}

void set_path(char* c_path) {
	strcpy(file_path, c_path);
}

void set_path_to_temp() {
	strncpy(file_path, "/tmp/", sizeof("/tmp/"));
}

void set_file_name(char* c_name) {
	strcpy(save_to, c_name);
}

#ifdef __cplusplus
}
#endif // __cplusplus


#endif // _WIN32


struct {
	char terminal_font[8];
	char* log_level;
	char terminal_reset[5];
}log_level[] = {
	{.terminal_font = "\033[37;1m", .log_level = "[INFO] ", .terminal_reset = "\033[0m"},
	{.terminal_font = "\033[33;1m", .log_level = "[WARNING] ", .terminal_reset = "\033[0m"},
	{.terminal_font = "\033[31;1m", .log_level = "[ERROR] ", .terminal_reset = "\033[0m"},
	{.terminal_font = "\033[31;1m", .log_level = "[PANIC] ", .terminal_reset = "\033[0m"}
};

// https://en.wikipedia.org/wiki/ANSI_escape_code


enum {
	LOG_INFO = 0,
	LOG_WARNING = 1,
	LOG_ERROR = 2,
	LOG_PANIC = 3
};

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

void save_log_to_file(char* log_message) {
	char* save_path = (char*)malloc(strlen(file_path) + strlen(save_to) + 1);
	memset(save_path, 0, sizeof(save_path));
	strcat(save_path, file_path);
	strcat(save_path, save_to);
	FILE* file = fopen(save_path, "a");

    time_t rawtime;
    struct tm * timeinfo;
    
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    fprintf(file, "[%2d/%2d/%d %2d:%2d:%2d] - ", timeinfo->tm_mday,
            timeinfo->tm_mon + 1, timeinfo->tm_year + 1900,
            timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
	fprintf(file, log_message);
	fprintf(file, "\n");

	fclose(file);
	free(save_path);
}
#ifdef __cplusplus
}
#endif // __cplusplus

#define log(level, args, ...) _log(level, args, __VA_ARGS__, (void *)0)

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus
void _log(bool log_to_file, short level, char* args, ...) {
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
	if (log_message != NULL) {
		memset(log_message, 0, allocation_size + 2);
		strcat(log_message, log_level[level].log_level);
	}
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
	if(log_to_file) save_log_to_file(log_message);
	free(log_message);
	if (level == LOG_PANIC) exit(1);
}
#ifdef __cplusplus
}
#endif // __cplusplus

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

#define custom_log(log_to_file, log_level, ...) _custom_log(log_to_file, log_level, __VA_ARGS__, (void *)0)

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus
void _custom_log(bool log_to_file, struct custom_log_level log_level, char* begin, ...) {
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

	if(log_to_file) save_log_to_file(log_message);
	free(log_message);
}
#ifdef __cplusplus
}
#endif //__cplusplus

#endif // maromitaz_cli_log
