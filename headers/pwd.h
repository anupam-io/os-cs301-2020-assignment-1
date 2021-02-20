#include <unistd.h>
#include <stdio.h>
#include <limits.h>

int pwd_handler() {
    char cwd[1000]; // char array for storing the directory name
    
    if (getcwd(cwd, sizeof(cwd)) != NULL) { // getcwd return a string when successful
        printf("%s\n", cwd);
    } else {
        int errnum = errno;
        printf("%s", strerror(errnum));
        return 1;
    }
    return 0;
}