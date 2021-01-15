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
  //char arraRec[10];
  int sizeR;
  int tamanho;
  char *rec[tamanho];


  int fd = open("fifoC_S", O_RDONLY);
  read(fd, &tamanho, sizeof(int));
  printf("Tamanho:%d\n", tamanho);
  for(int i = 0; i<tamanho; i++){
    read(fd, &sizeR, sizeof(int));
    printf("tamanho:%d\n", sizeR);
    char arraRec[sizeR];
    read(fd, &arraRec,sizeR);
    rec[i]= arraRec;
    printf("Arg:%s\n", rec[i]);
  }

    return 0;
}
