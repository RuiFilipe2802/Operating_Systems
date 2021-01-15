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
    char buffer[25] = "Boas, ta tudo?\n";
    char *args[10];
    fd = open("fifoC_S", O_WRONLY);
    int sizeArgs=0;
    //write(fd, buffer, sizeof(buffer));

    if(argc == 1){ //     Show usage protocol
        write(1, "./aurras transform input-filename output-filename filter id-1 filter id-2 ...", 78);
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
       int tam= argc - 2;
        write(fd, &tam,sizeof(int));
        for(int i = 2; i < argc; i++){
            args[i-2] = argv[i];
            //printf("%s\n", args[i-2]);
            sizeArgs =strlen(args[i-2])+1;
            printf("Tamanho:%d\n", sizeArgs);
            write(fd, &sizeArgs,sizeof(int));
            write(fd, args[i-2], sizeArgs);
        }

        //printf("Tamanho:%d\n", sizeArgs);
        //write(fd, &sizeArgs,sizeof(int));
        //write(fd, &args[0], sizeArgs);

   }



    return 0;
}
