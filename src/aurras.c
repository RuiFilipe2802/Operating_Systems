#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

//     CLIENTE

int main(int argc, char *argv[]){

    int fd;
    int fd2;
    char *args[10];
    int sizeArgs=0;
    int i;
    int size;
    char *arguments[10];
    char str[100];
    int argum = argc-2;
    //write(fd, buffer, sizeof(buffer));

    if(argc == 1){ //     Show usage protocol
        write(1, "./aurras transform input-filename output-filename filter id-1 filter id-2 ...\n", 79);
        return 1;
    }

    if((strcmp(argv[1],"status") == 0) && argc == 2){
        // TODO
        write(1, "STATUS...", 10);
    }

    if(strcmp(argv[1], "transform") == 0){
        if(argc < 3){
           perror("Command invalid");
           return 1;
        }
        fd = open("fifoC_S", O_WRONLY);
        for(i = 0;i < argum;i++){
            arguments[i] = argv[i+2];    
            strcat(str,arguments[i]);
            strcat(str," ");
            size = size + strlen(arguments[i])+1;
        }
        write(fd, &argum, sizeof(int));
        write(fd, &size, sizeof(int));
        write(fd, str, sizeof(str));
    }

    return 0;
}

