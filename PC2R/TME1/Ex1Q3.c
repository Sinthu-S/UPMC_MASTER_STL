#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int i=0;

void funcFils(){
   sleep(4);
   printf("Processus fils pid : %d, valeur de i : %d\n", getpid(),  i);
}

int main(){
  pthread_t tid;
  
  printf("Processus pere : %d, entrer une valeur\n", getpid());
  scanf("%d",&i);
  printf("Processus pere : %d, valeur de i : %d\n", getpid(), i);

  if(pthread_create(&tid, NULL, funcFils, NULL) !=0 ){
    perror("erreur creation thread");
    exit(1);
  }

  if(pthread_join(tid, NULL) != 0){
    perror("erreur fin  thread");
    exit(1);
  }
  
}
