#define _XOPEN_SOUCE 700
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 5

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int val;



void* funcThread(void* arg){
  int valrand;
  srand(pthread_self());
  valrand=(int) (10*((double)rand())/ RAND_MAX);
  printf("Numero de generer  %d \n tid %d \n", valrand, (long unsigned)(int)pthread_self());
  pthread_mutex_lock(&mutex);
  val+=valrand;
  pthread_mutex_unlock(&mutex);
  
}

int main(){
  pthread_t tid[N];
  int valRetour[N];
  int i=N-1;

  pthread_mutex_lock(&mutex);
  val=0;
  pthread_mutex_unlock(&mutex);

  while(i>-1){
    if(pthread_create(&tid[i], NULL, funcThread, NULL) != 0){
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

 
 
  printf("Valeur final : %d\n", val);
  
  
  return 0;
}
