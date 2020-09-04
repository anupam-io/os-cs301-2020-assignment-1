#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int grep_handler(char *argv[]) {
    FILE *stream;   
    char *line = NULL;
    size_t len = 0; 
    ssize_t nread;
    char* pattern = argv[1];

    if(argv[2] == NULL){
        // no file passed
        nread = getline(&line, &len, stdin);    // taking input from stdin
        if(strstr(line, pattern) != NULL){
            printf("Line 1: %s", line);
        }
        exit(0);
    }

    stream = fopen(argv[2], "r"); // opening the file

    if(argv[1] == NULL){
        // grep is passed no command-line arguments
        printf("grep <pattern> [file_name]\n");
        exit(1); 
    } else if(stream == NULL) {
        printf("grep: cannot open file %s \n", argv[2]);
        exit(1);
    }


    int line_no = 1;
    while ((nread = getline(&line, &len, stream)) != -1) {  // reading each line using getline()
        if(strstr(line, pattern) != NULL){
            printf("Line %d: %s", line_no++, line);
        }
    }

    free(line); free(pattern);
    fclose(stream);
    exit(0);
}
