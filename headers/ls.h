#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

#define next_line printf("\n")
#define MAX_ARG 100 // The max arguments support is 100

void ls_arg_call(char* arg){
    next_line;
    struct dirent *p;       // readdir() return a pointer to struct dirent
    DIR* folder_object;

    getcwd(arg, sizeof(arg));

    folder_object = opendir(arg);
    if(folder_object == NULL){
        // because the folder doesn't exist, so finding the file in the current directory
        char curr_arg[1024];
        getcwd(curr_arg, sizeof(curr_arg));

        folder_object = opendir(curr_arg);

        // PRINTING THE CONTENTS OF GIVEN FOLDER
        while ((p = readdir(folder_object)) != NULL){
            if(!strcmp(p->d_name, arg)){
                printf("%s", p->d_name);
                return;
            }
        }   

        // NO FILE DIRECTORY FOUND BY GIVEN NAME
        printf("Sorry:(\nNo file or directory found: \"%s\"", arg);
        return;
    }

    // PRINTING THE CONTENTS OF GIVEN FOLDER
    while ((p = readdir(folder_object)) != NULL){
        printf("%s\n", p->d_name);
    }
}


void ls_no_arg(){ 
    next_line;
    struct dirent *p;   // readdir() returns a pointer to struct dirent
    DIR* folder_object;
    
    char arg[1024];
    getcwd(arg, sizeof(arg));

    folder_object = opendir(arg);

    // PRINTING THE CONTENTS OF GIVEN FOLDER
    while ((p = readdir(folder_object)) != NULL){
        printf("%s\n", p->d_name);
    }
}


void ls_handler(char* argv[]){
    if(argv[1] == NULL){
        // calling ls with no argument
        ls_no_arg();
    }
    else{
        // calling ls for each of its arguments
        int ind = 1;
        while(ind<=MAX_ARG && argv[ind]!=NULL){
            ls_arg_call(argv[ind++]);
        }
    }
}