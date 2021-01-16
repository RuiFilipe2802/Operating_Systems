#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#define MAX 50

//    SERVIDOR


int readln(int fd, char *line, int size){
  int i=0, n;
  while(i < size && (n = read(fd, &line[i], 1)) == 1 && line[i] != '\n'){
    i++;
  }
  return i;
}


int main(int argc, char *argv[]){
  

  char *arrFilters[10][MAX];    // ARRAY WITH FILTERS
  char *arrExec[10][MAX];       // ARRAY WITH FILTER EXECUTABLES 
  int arrN[10];                 // ARRAY WITH NUMBER OF FILTERS
  int filters, exe, num, numFilters;
  write(1, "WELCOME\n", 9);
  mkfifo("fifoC_S", 0666);      // CLIENTE -> SERVIDOR
  mkfifo("fifoS_C", 0666);      // SERVIDOR -> CLIENTE

  char buf[25];
  int sizeBuf;
  int nLine = 0;
  int configFile = open("/home/rui/Desktop/grupo-xx/etc/aurrasd.conf", O_RDONLY);
  while((sizeBuf = readln(configFile, buf, sizeof(buf))) > 0){
   
    if((nLine % 3) == 0){          // FILTER
      arrFilters[filters][MAX] = malloc(sizeof(buf));
      strncpy(arrFilters[filters][MAX], buf, sizeBuf);
      printf("FILTER %d: %s\n",filters, arrFilters[filters][MAX]);
      filters++;  
    }

    if((nLine % 3) == 1){           // FILTER EXECUTABLE
      arrExec[exe][MAX] = malloc(sizeof(buf));
      strncpy(arrExec[exe][MAX], buf, sizeBuf);
      printf("EXECUTABLE %d: %s\n",exe, arrExec[exe][MAX]);
      exe++;   
    }

    if((nLine % 3) == 2){           // NUMBER OF FILTERS
      numFilters = atoi(buf);
      arrN[num] = numFilters;
      printf("FILTER NUMBER %d: %d\n",num, arrN[num]);
      num++;  
    }
    nLine++;
  }


/*
  int wri = open("logs.txt", O_WRONLY | O_CREAT | O_TRUNC, 0600);
  int rea = open("logs.txt", O_RDONLY, 0600);
  int r;
  int size;
  int args;
  char *argums[100];
  char *p = NULL;
  int i = 0;
  char *inputFile;

  

  int fd = open("fifoC_S", O_RDONLY);
  read(fd, &args, sizeof(int));           // GET NUMBER OF ARGUMENTS
  read(fd, &size, sizeof(int));           // GET SIZE MESSAGE
  char buffer[size];
  read(fd, buffer, size-1);               // GET MESSAGE

  for(p = strtok(buffer, " \n"); p != NULL;p = strtok(NULL, " ")){
    argums[i] = strdup(p);
    i++; 
  }
  inputFile = argums[1];
  write(1,inputFile, sizeof(inputFile));
  */
  return 0;
}
