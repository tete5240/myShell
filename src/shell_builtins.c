#include "./include/shell_builtins.h"

BuiltinCommand builtin_cmd[] = {
    {"cd", &cd_cmd},
    {"echo", &echo_cmd},
    {"exit", &exit_cmd},
    {"pwd", &pwd_cmd},
    {NULL, NULL}
};

int is_builtin_command (char* command) {
    for (int i = 0; builtin_cmd[i].command_name != NULL; i++) {
        if (!strcmp(command, builtin_cmd[i].command_name)){
            //return the index if the command is builitin
            return i;
        }
    }
    // return -1 if the command is not builtin
    return -1;
}

int execute_builtin_command (int command_index, char** arguments) {
    int error_flag = builtin_cmd[command_index].func(arguments);
    if (error_flag) return 1;
    return 0;
}

int cd_cmd (char** arguments) {
    int error_flag = chdir(arguments[0]);
    if (error_flag) {
        perror("cd");
        return 1;
    }
    return 0;
}

int echo_cmd (char** arguments) {
    for (int i = 0; arguments[i] != NULL && i < 10; i++) {
        printf("%s ", arguments[i]);
    }
    printf("\n");
    return 0;
}

int exit_cmd (char** arguments) {
    exit(0);
    return 0; //never executed
}

int pwd_cmd (char** arguments) {
    char cwd[100];
    getcwd(cwd, sizeof(cwd));
    printf("%s\n", cwd);
    return 0;
}