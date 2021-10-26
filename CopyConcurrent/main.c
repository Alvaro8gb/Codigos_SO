#define BLOCK 1923

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h> 
#include <stdio.h>

char buf[BLOCK] = "xxxxxxx...xxxxx";

void copia_bloque(int fdo, int fdd) {
  read(fdo, buf, BLOCK);
  write(fdd, buf, BLOCK);
}

void main() {
  pid_t pid;
  int fdo, fdd;
 

  for (int i = 0; i < 2 ; i++) {
    fdo = open("/home/ab-82/Desktop/SO/Codigos_SO/CopyConcurrent/inFile", O_RDONLY);
    fdd = open("output", O_RDWR | O_CREAT | O_TRUNC, 0666);

    lseek(fdo, i * BLOCK, SEEK_SET);
    lseek(fdd, 2 * i * BLOCK, SEEK_SET);
     
    pid = fork();
    
    if (pid == 0) {
      
      copia_bloque(fdo, fdd);
      exit(0);
    }

    close(fdo);
    close(fdd);
  }

  while (wait(NULL) != -1) {};

 
  printf("Finish\n ");
 
}
