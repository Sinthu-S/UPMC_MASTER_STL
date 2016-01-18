#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


int indice;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_modif = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_fin = PTHREAD_COND_INITIALIZER;

void* thread_func(void* arg){
  pthread_t* tid=*(pthread_t**)arg;
  pthread_mutex_lock(&mutex);
  printf("Nouvelle thread %d\n", indice);
  indice--;
  pthread_cond_signal(&cond_modif);
  if(indice>0){
   
    printf("Creation nouvelle thread %d\n", indice);
   
    if(pthread_create(&tid[indice], NULL, thread_func, arg) != 0){
	 perror("erreur creation thread");
	 exit(1);
    }
  }
  pthread_cond_wait(&cond_fin, &mutex);  
  pthread_mutex_unlock(&mutex);
  printf("Fin thread");
  pthread_exit(NULL); 
    
}

int main(int argc, char** argv){
  indice = 3;
  pthread_t tid[indice];
  int i=indice-1;
  
    if(pthread_create(&tid[0], NULL, thread_func, &tid) != 0){
	 perror("erreur creation thread");
	 exit(1);
      }


    pthread_mutex_lock(&mutex);
    while(indice>0){
      pthread_cond_wait(&cond_modif, &mutex); 
    }
    pthread_mutex_unlock(&mutex);
    printf("Tous mes descendants sont créés\n");
    pthread_cond_broadcast(&cond_fin);
   
    
    
    while(i>-1){
      if(pthread_join(tid[i], NULL) != 0){
	perror("erreur attente thread");
	exit(1);
      }
      i--;
    }
    return 0;
}
      
