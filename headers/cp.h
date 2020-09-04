#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>

// copy function from one file to another
int cpy(char *from, char *to) {
    FILE *from, *to;
    int c;

    if ((to = fopen(to, "w")) && (from = fopen(from, "r"))) {
        while ((c = getc(from)) != EOF)
            putc(c, from);    // copying characters one by one 


        fclose(from);
        fclose(to);         // closing the files

        return 0;
    }
    return -1;
}

int cp_handler(char *argv[]) {

    struct stat buffer;
    int exist = stat(argv[1], &buffer);

    if(S_ISDIR(buffer.st_mode)){        
        char newdir_name[1000] = "";
        strcat(newdir_name, argv[1]);    strcat(newdir_name, "-copy");

        
        mkdir(newdir_name, 0777);   // making a new directory

        struct dirent *de;          // pointer for directory entries
    
        
        DIR *dr = opendir(argv[1]); // opendir() returns a pointer of DIR type   
    
        
        while ((de = readdir(dr)) != NULL){ // reading each file name using readdir()
            //printf("%s\n", de->d_name);
            
            char fn1[1000] = "";
            strcat(fn1, argv[1]);    
            strcat(fn1, "/");
            strcat(fn1, de->d_name);    // saving original file name in char array
            
            
            char fn2[1000] = "";
            strcat(fn2, newdir_name);    
            strcat(fn2, "/");
            strcat(fn2, de->d_name);    // saving new file name in char array
            

            // check is there is a file or folder
            stat(de->d_name, &buffer);
            if(S_ISDIR(buffer.st_mode)){
                printf("cp: folder detected \"%s\"\n", de->d_name);
                continue;
            }

            if (cpy(fn2, fn1) == -1) {
                // Error showing usign errno
                int errnum = errno;
                printf("cp: unable to copy characters.\n%s", strerror(errnum));
                
            }
        }
    
        closedir(dr); // closing dir
        printf("Copied Successfully.");
        
        exit(0);        
    } else if (exist == 0){
        char *fn1 = argv[1];
        char *fn2 = argv[2];

        //printf("file exists.");
        if (cpy(fn2, fn1) == -1) {
            int errnum = errno;
            printf("cp: unable to copy characters.%s", strerror(errnum));
            exit(1);
        }
        printf("Copied Successfully.");
    } else {
        printf("cp: nothing found by the name \"%s\"", argv[1]);
        exit(1);
    }

    exit(0);
}
