#define _XOPEN_SOURCE 700
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int indiceArgument;


void* funcThread(void* arg){
  unsigned int tid=(unsigned int)pthread_self();
  int indice;
  char** tab=(char**)arg;
  printf("Debut tid %u\n", tid);
  pthread_mutex_lock(&mutex);
  while(indiceArgument>1){ /* argument 1 etant le nombre de thread*/
     indice= indiceArgument--;
    pthread_mutex_unlock(&mutex);
    printf("Thread %u traitement argument %d\n  ",tid, indice);
    upper(tab[indice]);
    
    pthread_mutex_lock(&mutex); 
  }
  pthread_mutex_unlock(&mutex);
    
  
  printf("Fin tid %u \n",tid);
  return NULL;
}


int main(int argc, char** argv){
  
  indiceArgument = argc-1;
 
  int i=atoi(argv[1]);
  int nbThread=i;
  pthread_t tid[i];
  
  if(argc < 3){
     perror("nombre d'argument insuffisant");
     exit(1);
  }

  
  
  printf("nb argument %d %d\n  ",argc, i);
  while(i>0){
    if(pthread_create(&tid[i-1], NULL, funcThread, (void*)argv) != 0){
      perror("erreur creation thread");
      
    }
    i--;
  }
  

  
   while(i<nbThread){

     if(pthread_join(tid[i],NULL) != 0){
       perror("erreur attente thread");
       
     }
     i++;
   }

    printf("Fin  \n");
   
  return 0;
}
