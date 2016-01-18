#include <stdio.h>
#include <stdlib.h>


int main(int args, char** argv){
  pid_t pid=fork();
  printf("pid %d\n", pid);
}
