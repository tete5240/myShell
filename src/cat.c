#include <stdio.h>
#include <string.h> 
#define MAX_LINE_CONTENT 100

int main(int argc, char *argv[]) {
    // error message for inapropriate usage
    if (argc != 2) { 
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    char file_name[100];
    strcpy(file_name, argv[1]); 

    FILE* fp = fopen(file_name, "r");
    // error message for the situation when the file isn't opened
    if (fp == NULL) {
        perror("File does not exist");
        return 1;
    }

    // print the content line by line
    char content[MAX_LINE_CONTENT];
    while (fgets(content, MAX_LINE_CONTENT, fp) != NULL) {
        printf("%s\n", content);
    }

    fclose(fp);
    return 0;
}
