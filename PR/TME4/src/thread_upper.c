#define _XOPEN_SOURCE 700
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <pthread.h>


void* funcThread(void* arg){
  unsigned int tid=(unsigned int)pthread_self();
  printf("Debut tid %u %s \n", tid, *(char**)arg);
  upper(*(char**)arg);
  printf("Fin tid %u \n",tid);  
  return NULL;
}


int main(int argc, char** argv){

  int nbFichier = argc-1;
  pthread_t tid[nbFichier];
  int i=nbFichier-1;
  
  printf("nb argument %d %d\n  ",argc, i);
  while(i>-1){
      printf("%d\n  ", i);
    if(pthread_create(&tid[i], NULL, funcThread, (void*)&argv[i+1]) != 0){
      perror("erreur creation thread");
     
    }
    i--;
  }
  i++;
   printf("%d\n  ", i);
  
  while(i<nbFichier){
    if(pthread_join(tid[i],NULL) != 0){
       perror("erreur attente thread");
  
    }
    i++;
  }
 
  return 0;
}
