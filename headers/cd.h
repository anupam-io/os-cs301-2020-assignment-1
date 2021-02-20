#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>

int cd(char *pth){
    int errnum;
    if(pth == NULL){
        exit(0);
    }

    char path[100]; // setting the max length as 100
    strcpy(path, pth);
    
    // Halting if input is too long 
    if(strlen(path)>100){
        printf("The input is exceeding the max length 100.\nreturning...");
        exit(0);
    }

    if(chdir(pth) == -1){
        errnum = errno;
        fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
    }
    
    return 0;
}

int cd_handler(char* argv[]){
    char s[100]; // char array for storing dir name

    // printing the current dir
    getcwd(s,sizeof(s));    printf("Directory before: %s\n", s);

    // setting the dir using cd() call
    cd(argv[1]);

    // again printing the current dir
    getcwd(s,sizeof(s));    printf("Directory after : %s\n", s);
    

    return 0;
}

