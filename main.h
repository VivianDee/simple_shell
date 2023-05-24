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

#define LETTERS 1024

extern char **environ;

void free_parameter_array(char *parameter[]);
int execute_command(char *parameters[], int background, char *programName);
int command_buffer(char *input, char *parameter[], int *len);
void print_error(char *programName, const char *format, ...);
void check_command(char *input, char *programName);

#endif
