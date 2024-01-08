#ifndef _SHELL_BUILTINS_H_
#define _SHELL_BUILTINS_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

// function pointer for builtin command functions
typedef int (*BuiltinCmd)(char **);

// struct for mapping function name and function pointer
typedef struct {
    char *command_name; 
    BuiltinCmd func;
} BuiltinCommand;

// returns -1 when the command is not builtin
// else, returns the index of function pointer 
int is_builtin_command (char* command_name);

// execute command with given index
int execute_builtin_command (int command_index, char** arguments);

// builtin commands must have int return type and char** arguments
int cd_cmd (char** arguments);
int exit_cmd (char** arguments);
int echo_cmd (char** arguments);
int pwd_cmd (char** arguments);

#endif // _SHELL_BUILTINS_H_