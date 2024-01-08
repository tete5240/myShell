#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "./include/shell_builtins.h"

// each command are parsed into this container
typedef struct {
    char command_name[10]; 
    char *arguments[20];
    int argument_count; 
} Command;

void parse (char*, Command*);

int main (void) {
    // get the path of shell itself
    char exe_path[100];
    ssize_t len = readlink("/proc/self/exe", exe_path, sizeof(exe_path) - 1);
    exe_path[len - 5] = '\0';

    // generate th path of the home directory
    char current_path[100];
    strcpy(current_path, exe_path);
    strcat(current_path, "../home");    
    chdir(current_path);  // set default dir to home
    
    char raw_input[100];       
    Command command;            

    do {
        getcwd(current_path, 100);
        printf("%s> ", current_path);      

        // get input from the command line and delete '\n'
        fgets(raw_input, sizeof(raw_input), stdin);
        raw_input[strcspn(raw_input, "\n")] = 0;

        parse(raw_input, &command);

        // if the command is buitin, call builtin and continue
        // idx -1 means that the command is not builtin
        int idx = is_builtin_command(command.command_name);
        if (idx != -1) {
            int error_flag = execute_builtin_command(idx, command.arguments);
            if (error_flag) { perror("Command error"); }
            continue;
        }

        pid_t pid = fork(); // Create a child process.
        if (pid == -1) {
            perror("fork"); // Handle fork failure.
            exit(EXIT_FAILURE);
        } 
        else if (pid == 0) {
            // Child process: attempt to run the given command.
            char execute_file[100];
            strcpy(execute_file, exe_path); // Construct the path for the executable.
            strcat(execute_file, command.command_name);
            
            char *args[11];
            args[0] = command.command_name; // Set up arguments for execvp.
            for(int i = 0; i < command.argument_count; i++) {
                args[i+1] = command.arguments[i];
            }
            args[command.argument_count + 1] = NULL;

            execvp(execute_file, args); // Execute the command.
            perror("execvp"); // Only reached if execvp fails.
            exit(EXIT_FAILURE);
        } 
        else {
            // Parent process: wait for the child to complete.
            int status;
            waitpid(pid, &status, 0);
        }
    } while(1);

    return 0;
}


void parse (char* raw_input, Command* command) {  
    char *token = strtok(raw_input, " ");
    command->argument_count = 0;

    if (token != NULL) {
        strncpy(command->command_name, token, sizeof(command->command_name) - 1);
        command->command_name[sizeof(command->command_name) - 1] = '\0';        
        token = strtok(NULL, " ");
    }

    while (token != NULL && command->argument_count < 10) {
        // Duplicate and store the argument
        command->arguments[command->argument_count] = strdup(token); 
        command->argument_count++;
        token = strtok(NULL, " ");
    }

    // Ensure NULL termination for execvp
    command->arguments[command->argument_count] = NULL; 
}

