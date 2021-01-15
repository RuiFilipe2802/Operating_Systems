#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

//    SERVIDOR

int main(int argc, char *argv[]){

  write(1, "BEM VINDO\n", sizeof("BEM VINDO\n"));
  // CLIENTE -> SERVIDOR
  mkfifo("fifoC_S", 0666);
  // SERVIDOR -> CLIENTE
  mkfifo("fifoS_C", 0666);
  int wri = open("logs.txt", O_WRONLY | O_CREAT | O_TRUNC, 0600);
  int rea = open("logs.txt", O_RDONLY, 0600);
  int r;
  int size;
  int args;

  int fd = open("fifoC_S", O_RDONLY);
  read(fd, &args, sizeof(int));         // GET NUMBER OF ARGUMENTS
  printf("%d\n", args);
  read(fd, &size, sizeof(int));         // GET SIZE MESSAGE
  printf("%d\n", size);
  char buffer[size];
  read(fd, buffer, size-1);               // GET MESSAGE
  write(1, buffer, size);

  
  return 0;
}
