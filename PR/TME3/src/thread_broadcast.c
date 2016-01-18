#define _XOPEN_SOUCE 700
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 5

/*les threads ne sont pas détachés*/

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int val;
int indice;


void wait_barrier(int n){
  
  pthread_mutex_lock(&mutex);
  indice++;
  pthread_cond_broadcast(&cond);
  while(indice!=n){
    pthread_cond_wait(&cond, &mutex);
  }
  pthread_mutex_unlock(&mutex);
}

void* thread_func (void *arg) {
   printf ("avant barriere\n");
   wait_barrier (N);
   printf ("après barriere\n");
   pthread_exit ( (void*)0);
}



int main(){
  pthread_t tid[N];
  int i=N-1;
  indice=0;




  while(i>-1){
 
    if(pthread_create(&tid[i], NULL, thread_func, NULL) != 0){
      perror("erreur creation thread");
      exit(1);
    }
    i--;
  }

  i++;
    
  while(i<N){
    if(pthread_join(tid[i],NULL) != 0){
       perror("erreur attente thread");
      exit(1);
    }
    i++;
  }

 
  
  
  return 0;
}
