#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <fcntl.h>
#include <errno.h>
 
int cat_handler(char *argv[]) { 
    for(int i = 1; argv[i]!=NULL; i++) {            /*iterate the loop for total argument count.*/
        printf("File no %d \"%s\"contents: \n", i, argv[i]);
        FILE *stream; 

        char *line = NULL;
        size_t len = 0; 
        
        stream = fopen(argv[i], "r");   // opening file

        if(stream == NULL){
            int errnum = errno;
            printf("cat: unable to read file \"%s\"\n%s", argv[i], strerror(errnum));
            exit(1);
        }

        while (getline(&line, &len, stream) != -1) { // reading each line using getline()
            printf("%s", line);
        }
        fclose(stream);     // closing file
        printf("\n");
    }

    exit(0);
}