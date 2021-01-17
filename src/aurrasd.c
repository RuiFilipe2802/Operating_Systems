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
/*void exeFun(char *path, char *inp, char *out, char *fil){
  int file_input;
  int file_output;
  char iF[9] = "samples/"; 
  pid_t pid;
  pid = fork();
      switch (pid) {
        case -1: //erro
                perror("fork");
                //return 1;
        case 0: //filhos
                
                strcat(path, fil);
                strcat(iF, inp);
                printf("Path:%s\n", path);
                file_input = open(iF, O_RDONLY);
                file_output = open(out, O_WRONLY | O_CREAT | O_TRUNC, 0666);
                dup2(file_input, 0); 
                close(file_input);
                dup2(file_output, 1);
                close(file_output);

                _exit(1); //mata sempre o programa
        default: //pai
                printf("criado pid = %d\n", pid);
      }

}*/

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

  char path[50] = "../";
  strcat(path, argv[2]);
  char filtersDestination[13] = "../";
  strcat(filtersDestination, argv[1]);
  int configFile = open(filtersDestination, O_RDONLY);
  char buf[25];
  int sizeBuf;
  int nProc = 0;
  int nLine = 0;
  int fd ;
  
  char filtersFromClient[10][MAX]; 

  if(argc == 1){ //     Show usage protocol
        write(1, "./aurrasd config-filename filters-folder\n", 42);
        return 1;
  }

  while((sizeBuf = readln(configFile, buf, sizeof(buf))) > 0){
   
    if((nLine % 3) == 0){          // FILTER
      arrFilters[filters][MAX] = malloc(sizeof(buf));
      strncpy(arrFilters[filters][MAX], buf, sizeBuf);
      //printf("FILTER %d: %s\n",filters, arrFilters[filters][MAX]);
      filters++;  
    }

    if((nLine % 3) == 1){           // FILTER EXECUTABLE
      arrExec[exe][MAX] = malloc(sizeof(buf));
      strncpy(arrExec[exe][MAX], buf, sizeBuf);
      //printf("EXECUTABLE %d: %s\n",exe, arrExec[exe][MAX]);
      exe++;   
    }

    if((nLine % 3) == 2){           // NUMBER OF FILTERS
      numFilters = atoi(buf);
      arrN[num] = numFilters;
      nProc = nProc +numFilters;
      //printf("FILTER NUMBER %d: %d\n",num, arrN[num]);
      num++;  
    }
    nLine++;
  }

  //int wri = open("logs.txt", O_WRONLY | O_CREAT | O_TRUNC, 0600);
  //int rea = open("logs.txt", O_RDONLY, 0600);

  printf("%d\n", nProc);

  int r, m;
  int size;
  int args;
  char *argums[50];
  char *p = NULL;
  //int i = 0;
  char *inputFile, *outputFile;
  int j, status;
  


 fd = open("fifoC_S", O_RDONLY);
  while(1){
    while(read(fd, &args, sizeof(int))>0 ){
                                         // GET NUMBER OF ARGUMENTS
      read(fd, &size, sizeof(int));           // GET SIZE MESSAGE
      char buffer[size];
      read(fd, buffer, size);                 // GET MESSAGE
      int i = 0;

      for(p = strtok(buffer, " \n"); p != NULL;p = strtok(NULL, " ")){
            argums[i] = strdup(p);
            printf("Args[%d]:%s\n",i, argums[i]);
             i++; 
    
      }
        inputFile = argums[0];
        outputFile = argums[1];
        printf("%s\n", outputFile);
        char filtro[50];
        printf("Filtro:%s\n", arrExec[0][MAX]);
        printf("%s", argums[2]);
        if(strcmp(argums[2],"alto")){
          printf("boas");
          strcpy(filtro, arrExec[0][MAX]);
          //exeFun(path,inputFile,outputFile,filtro);
        }
        for(m = 2;m < args;m++){ 
            strcpy(filtersFromClient[m-2],argums[m]);
            //printf("%s\n", filtersFromClient[m-2]);
         }         

        sleep(1);
    }
  }


  return 0;
}

/*
for (j = 0; j != nProc; j++) {  //ciclo criacao filhos
      pid = fork();
      switch (pid) {
        case -1: //erro
                perror("fork");
                return 1;
        case 0: //filhos
                
                strcat(path, arrExec[4][MAX]);
                strcat(iF, inputFile);
                file_input = open(iF, O_RDONLY);
                file_output = open(outputFile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
                dup2(file_input, 0); 
                close(file_input);
                dup2(file_output, 1);
                close(file_output);

                _exit(j+1); //mata sempre o programa
        default: //pai
                printf("criado pid = %d\n", pid);
      }
  }
  for (size_t l = 0; l < nProc; l++) { // ciclo espera pela morte de filhos
      pid = wait(&status);
      printf("morreu pid = %d\n", pid);
      if(WIFEXITED(status)){
        printf("exit: %d\n", WEXITSTATUS(status));
      }else{
        printf("filho nao terminou com exit\n");
      }
  }
  */