#define SVID_SOURCE 1
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <time.h>



 int sem_id;

void wait_barrier(int n){
  struct sembuf operation;
  operation.sem_op=-1;
  semop(sem_id, &operation, 1);
  operation.sem_op=0;
  semop(sem_id, &operation, 1);
}

void process (int NB_PCS) {
   printf ("avant barrière\n");
   wait_barrier (NB_PCS);
   printf ("après barrière\n");
   exit (0);
}


int main(int argc, char** argv){
  key_t key;
  int nbProc, nbFils;
  pid_t pid;
  

  if(argc < 2){
    perror("manque argument");
    exit(1);
  }

  nbProc=atoi(argv[1]);
  nbFils=nbProc;
  key=ftok(argv[0], (char)getpid());
  sem_id = semget(key, 1, IPC_CREAT | 0666);
  semctl(sem_id, 0, SETVAL, nbProc);

 
  do{
    nbProc--;
    pid=fork();
  }while(nbProc>0 && pid!=0);

  if(pid == 0){
    process(nbProc);
   
  }else{
    while(nbFils>0){
      wait(NULL);
      nbFils--;
    }
    
    semctl(sem_id, 0, IPC_RMID, 0);
    
  }
  return 0;
}

