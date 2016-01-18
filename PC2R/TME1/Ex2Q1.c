#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NB_THREAD 10

int SHARED_compteur;
pthread_t tid[NB_THREAD];

void funcThread(){
  int temp=SHARED_compteur;
   
   sched_yield();
   // temp++;
   SHARED_compteur = temp + 1;
   sched_yield();
   printf("Processus fils pid : %d, valeur de temp : %d\n", getpid(),  temp);
 
}

int main(){
  int i=0;

  SHARED_compteur = 0;

  for(i=0; i<NB_THREAD; i++){
    if(pthread_create(&tid[i], NULL, funcThread, NULL) !=0 ){
      perror("erreur creation thread");
      exit(1);
    }
  }

  /** attente active**/
  /*
  while(SHARED_compteur < NB_THREAD ){
  
  }
  */

  
  for(i=0; i<NB_THREAD; i++){
     if(pthread_join(tid[i], NULL) != 0){
       perror("erreur fin  thread");
       exit(1); 
     }
  }
  printf("TERMINE\n");
}
