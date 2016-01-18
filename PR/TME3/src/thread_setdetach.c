#define _XOPEN_SOUCE 700
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 5

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int val;
int indice;


void* funcThread(void* arg){
  int valrand;
  srand(pthread_self());
  valrand=(int) (10*((double)rand())/ RAND_MAX);
  printf("Numero de generer  %d \n tid %d \n", valrand, (long unsigned)(int)pthread_self());
  pthread_mutex_lock(&mutex);
  val+=valrand;
  indice++;
  if(indice==N)
    pthread_cond_signal(&cond);
  pthread_mutex_unlock(&mutex);
  pthread_exit((int)arg*2);
}


void* threadAffiche(void* arg){
  pthread_mutex_lock(&mutex);
  pthread_cond_wait(&cond, &mutex);
 
  printf("\n tid : %d \n Valeur final : %d\n",(long unsigned)(int)pthread_self(), val);
  pthread_mutex_unlock(&mutex);
  
}



int main(){
  pthread_t tid[N+1];
  int valRetour[N];
  int i=N-1;
  int flag=0;
  pthread_attr_t attr;
  
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

  pthread_mutex_lock(&mutex);
  val=0;
  indice=0;
  pthread_mutex_unlock(&mutex);

  if(pthread_create(&tid[N], NULL, threadAffiche, NULL) != 0){
      perror("erreur creation thread affichage");
      exit(1);
    }

  while(i>-1){
    valRetour[i]=i;
    if(pthread_create(&tid[i], &attr, funcThread, NULL) != 0){
      perror("erreur creation thread");
      exit(1);
    }
  
    i--;
  }

  if(pthread_join(tid[N],NULL) != 0){
       perror("erreur attente thread");
       exit(1);
    }
 
 
  
  return 0;
}
 
