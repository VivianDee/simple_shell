#ifndef MAIN_H
#define MAIN_H

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

char *_strtok(char *string1, const char *string2);
char *_strtok2_strings(char *string1, char *string2[]);
size_t _getline(char **lineptr, size_t *n, FILE *stream);
int command_buffer(char *input, char *parameter[]);
void update_pwd_in_env();
void change_directory(char *parameters[]);
void remove_comments(char *parameters[]);
int echo_command(char *parameters[]);
int check_builtin(char *parameters[]);
int command_exists(char *parameters[]);
int execute_command(char *parameters[], int background);
void remove_spaces_around_delimiter(char *input, const char *delimiter);
int countDelimiter(char *input, char *delimiters[], char *logicalOps[]);
void check_command(char *input);
int main(int ac, char **av);


#endif
