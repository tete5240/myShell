#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#define MAX_DIR_NAME 20

int main (int argc, char* argv[]) {
    // error message for inapropriate usage
    if (argc != 2) { 
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // make directory name from the first argument
    char dir_name[MAX_DIR_NAME];
    strncpy(dir_name, argv[1], MAX_DIR_NAME - 1);
    dir_name[MAX_DIR_NAME - 1] = '\0';

    // set mode of the directory
    // owner has read, write, and execute permission defaultly
    mode_t mode = S_IRUSR | S_IWUSR | S_IXUSR; 

    // if the directory isn't made, print error and terminate the process
    if (mkdir(dir_name, mode) == -1) {
        perror("Failed to make new directory");
        return 1;
    }
    return 0;
}