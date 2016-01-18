#define SVID_SOURCE 1
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <time.h>

/*
On suppose que les processus sont lancés separement (pas de fork)
le programme prend en parametre le nombre de processus total 
*/



void wait_barrier(int *valAddr, int nb){
  int i=0;

  for(
}




int main(int argc, char** argv){
  int shm, sem;
  int nbProc;
  int *valAddr;
  pid_t pid;

  int nbProc = atoi(argv[0]);


  if(( shm= shm_open("shm_remonte", O_RDWR|O_CREAT, 0600))==-1){
    perror("erreur creation shm");
    exit(0);
  }

  
  if(ftruncate(shm_id, sizeof(sem_t)*nbProc) == -1){
    perror("erreur ftruncte");
    exit(0);
  }
 
  valAddr = mmap(NULL, sizeof(sem_t)*nbProc, PROT_READ | PROT_WRITE, MAP_SHARED, shm_id, 0);

  
 
  printf ("avant barrière\n");
  wait_barrier (nbProc);
  printf ("après barrière\n");



 

 return 0;
}
