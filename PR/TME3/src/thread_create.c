#define _XOPEN_SOUCE 700
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 5



void* funcThread(void* arg){
  int num=*(int*)arg;
  printf("Numero de création %d \n tid %d \n", num, (long unsigned)pthread_self());
  pthread_exit(2*num);
}

int main(){
  pthread_t tid[N];
  int valRetour[N];
  int i=N-1;

  while(i>-1){
    valRetour[i]=i;
    if(pthread_create(&tid[i], NULL, funcThread, (void*)&valRetour[i]) != 0){
      perror("erreur creation thread");
      exit(1);
    }
    i--;
  }

  i++;
    
  while(i<N){
    if(pthread_join(tid[i],(void**) &valRetour[i]) != 0){
       perror("erreur attente thread");
       exit(1);
    }
    i++;
  }

  i--;
  while(i>-1){
    printf("Numero %d, val %d\n", i, valRetour[i]);
    i--;
  }
  
  return 0;
  
}
