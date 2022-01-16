#include <stdio.h>

#include <stdlib.h>

#include <sys/types.h>

#include <unistd.h>

int len = 1024;

char get_character(FILE * fd, int i) {
  char c;
  fseek(fd, i, SEEK_SET);
  if (c = getc(fd) != EOF)
    return c;
  else
    return '0'	;
}

int main() {
  int i;
  FILE * file1;
  char M[len];

  file1 = fopen("test.txt", "rw");

  for (i = 1; i < len; i++) {
    M[i] = get_character(file1, i);
    printf("- %c ",M[i]);
  }
  return 1;
}
