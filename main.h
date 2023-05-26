#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

#define LETTERS 1024

extern char **environ;
/**
 *struct data - Make an alias for struct data
 *@command: is array of commands
 */
typedef struct data
{
	char command[LETTERS];
} data;

void replaceChar(char *str);
char* _strchr(const char* str, char c);
char *remove_leading_spaces(char *input);
char *remove_trailing_spaces(char *input);
void _vsnprintf(const char *format, va_list args, ssize_t *totalBytesWritten);
void free_parameter_array(char *parameter[]);
int command_buffer(char *input, char *parameter[], int *len);
void print_error(char *programName, const char *format, ...);
char *_strtok(char *string1, const char *string2);
char *_strtok2_strings(char *string1, char *string2[]);
size_t _getline(char **lineptr, size_t *n, FILE *stream);
void update_pwd_in_env(void);
void change_directory(char *parameters[]);
void remove_comments(char *parameters[]);
int echo_command(char *parameters[]);
int check_builtin(char *parameters[], char *input, char *programName, struct data *data, int count);
int command_exists(char *parameters[], char *programName, data *data);
int execute_command(char *pmeters[], int bg, char *programName, data *data);
void remove_spaces_around_delimiter(char *input, const char *delimiter);
int countDelimiter(char *input, char *delimiters[], char *logicalOps[]);
void error_data(struct data *data, char *token);
int check_command(char *input, char *programName);
int _putenv(const char *string);
void handle_sig(int signo);
char *_strdup(const char *source);
char *_getenv(const char *name);
int _strncmp(const char *s1, const char *s2, size_t n);
size_t _strlen(const char *str);
char *_strstr(const char *haystack, const char *needle);
int _strcmp(const char *str1, const char *str2);
int _setenv(const char *name, const char *value, int overwrite);
void *_memcpy(void *dest, const void *src, size_t n);
#endif /* MAIN_H */
