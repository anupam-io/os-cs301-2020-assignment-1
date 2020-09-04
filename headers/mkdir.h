#include <stdio.h> 
#include <stdlib.h> 
#include <sys/stat.h>
#include <errno.h>

void mkdir_handler(char* argv[]) { 
	int check = mkdir(argv[1],0777); 

	if (!check) {
		printf("Directory created!!!\n"); 
    }
	else { 
		int errnum = errno;
		printf("%s: %s\n", strerror(errnum), argv[1]);
		exit(1); 
	}
    exit(0);
} 
