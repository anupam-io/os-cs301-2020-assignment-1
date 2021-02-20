/*  This project is made by Anupam Kumar
    Assignment 1 OS-2020
    18110022 B.Tech-18
    Email: anupam.kumar@iitgn.ac.in
*/

#include <sys/wait.h>
#include <readline/readline.h> 
#include <readline/history.h> 

#include "headers/ls.h"
#include "headers/grep.h"
#include "headers/cat.h"
#include "headers/cp.h"
#include "headers/cd.h"
#include "headers/mkdir.h"
#include "headers/pwd.h"

extern int errno;   // for detecting errors

#define next_line printf("\n")
#define MAX_ARG 100 // max arg supported is 100

int main(int argc, char **argv){
    // INITIALIZATION STEP
    printf("*** WELCOME TO MY SHELL ***\n***    Version 1.0.0    ***");
    char* token;    int i;
    char* buff;     char *myargs[MAX_ARG+1];


    // INTERPRET STEP
    // Run command loop.
    while(1){
        // Taking the input   
        buff = readline("\niceCREAM>>>");
        if(strlen(buff)){
            add_history(buff); // adding into history
        } else {
            continue;
        } 

        // Processing the input into tokens
        i = 0;    
        token = strtok(buff, " ");
        while(token!=NULL){
            myargs[i++] = strdup(token);
            token = strtok(NULL, " ");
            if(i == MAX_ARG)break;
        }

        // Handling overflow
        if(i == MAX_ARG){
            printf("Max argument limit exceeded.\n Max argument limit is 100. \nPlease try again.");
            continue;
        }
        myargs[i] = NULL; // making the last unused command as null



        // Executing special commands
        if(!strcmp(myargs[0], "help")){
            printf("Shell created by Anupam Kumar.\nhelp: for getting help information.\n\nversion: for more on version information.\n\nexit: for exiting the shell.\n\n");
            continue;
        } else if (!strcmp(myargs[0], "version")){
            printf("First version of iceCREAM.\n1.0.0\n");
            continue;
        } else if (!strcmp(myargs[0], "exit")){
            printf("Bye Bye user.\n");
            exit(0);
        } else if (!strcmp(myargs[0], "hi")){
            printf("Hi User. Don't crash this.");
            continue;
        } 
        
        // Main commands implemented are ls, grep, cat, cp, cd, mkdir, pwd
        else if (!strcmp(myargs[0], "ls")){
            int rc = fork(); // calling fork to create a subprocess
            if(rc == 0){
                ls_handler(myargs); exit(0); // child will exit after its job
            }
            else{
                wait(0); continue;  // parent will wait and continue run-command loop
            }
        }
        else if (!strcmp(myargs[0], "grep")){
            int rc = fork();
            if(rc == 0){
                grep_handler(myargs); exit(0);
            }
            else{
                wait(0); continue;
            }
        }
        else if (!strcmp(myargs[0], "cat")){
            int rc = fork();
            if(rc == 0){
                cat_handler(myargs); exit(0);
            }
            else{
                wait(0); continue;
            }
        }
        else if (!strcmp(myargs[0], "cp")){
            int rc = fork();
            if(rc == 0){
                cp_handler(myargs); exit(0);
            }
            else{
                wait(0); continue;
            }
        }
        else if (!strcmp(myargs[0], "cd")){
            int rc = fork();
            if(rc == 0){
                cd_handler(myargs); exit(0);
            }
            else{
                wait(0); continue;
            }
        }
        else if (!strcmp(myargs[0], "mkdir")){
            int rc = fork();
            if(rc == 0){
                mkdir_handler(myargs); exit(0);
            }
            else{
                wait(0); continue;
            }
        }
        else if (!strcmp(myargs[0], "pwd")){
            int rc = fork();
            if(rc == 0){
                pwd_handler(myargs); exit(0);
            }
            else{
                wait(0); continue;
            }
        }





        // Execution comes here when none of the above command is executed

        // Execution of built-in system calls using execvp
        int rc = fork(); 
        if(rc == 0){
            if(execvp(myargs[0], myargs)<0){
                int errnum = errno;
                printf("%s", strerror(errnum));
                exit(1);
            }
            exit(0);
        } else {
            wait(NULL);
        }
        
        // Cleaning input buffers
        free(token);    free(buff);
    }

    // TERMINATE STEP
    // Perform any shutdown/cleanup.
    return EXIT_SUCCESS;
}
