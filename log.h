#ifndef maromitaz_cli_log
#define maromitaz_cli_log

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

// https://en.wikipedia.org/wiki/ANSI_escape_code
char log_level[3][30] = {
	"\033[37;1m[INFO]\033[0m", 
	"\033[33;1m[WARNING]\033[0m",
	"\033[31;1m[ERROR]\033[0m"
};

enum {
	LOG_INFO = 0,
	LOG_WARNING = 1,
	LOG_ERROR = 2,
};

#define log(level, ...) do{\
	if(level < 0 || level > 2) {\
		printf("%s Logging level unkown", log_level[2]);\
		exit(1);\
	}\
	printf("%s ", log_level[level]);\
	printf(__VA_ARGS__);\
	printf("\n");\
}while(0)

#ifndef __cplusplus
	typedef signed char bool;
#	define true 1
#	define false 0
#endif

struct custom_log_level
{
	char color[3];
	bool bold;
	char* log_symbol;
};

#ifdef __cplusplus
extern
#endif
#define custom_log(log_level, ...){\
	struct custom_log_level log_level_var = log_level;\
	printf("\033[%s", log_level_var.color);\
	if(log_level_var.bold)\
		printf(";1m");\
	else\
		printf("m");\
	printf("[%s] \033[0m", log_level_var.log_symbol);\
	printf("%s\n", __VA_ARGS__);\
}

#endif
