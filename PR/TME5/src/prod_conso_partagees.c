#define SVID_SOURCE 1
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <time.h>

#define PRODUCTEUR int c;  while((c = getchar()) != EOF){ push(c); }

#define CONSOMMATEUR while(1) { putchar(pop()); fflush(stdout); }

int shm_id;
int sem_id;
int* valAddr;
struct sembuf operation[2];

void push(char c){

  /*ajoute un element*/
  operation[0].sem_num=0;
  operation[0].sem_op=1;
  operation[0].sem_flg=0;

  /*enleve une place*/
  operation[1].sem_num=1;
  operation[1].sem_op=-1;
  operation[1].sem_flg=0;
  
  semop(sem_id, &operation, 2);

  *(valAddr +  semctl(sem_id, 0, GETVAL, 0)) = c; 
  printf("\nProducteur pid : %d push %c \n",getpid(),c);
  
}

char pop(){
 char c;
 /*enleve un element*/
 operation[0].sem_num=0;
 operation[0].sem_op=-1;
 operation[0].sem_flg=0;

 /*ajoute une place*/
 operation[1].sem_num=1;
 operation[1].sem_op=1;
 operation[1].sem_flg=0;
 
 semop(sem_id, &operation, 2);

 c = *(valAddr +  semctl(sem_id, 0, GETVAL, 0)); 
 printf("\nConsomateur pid : %d pop %c \n",getpid(),c);
 return c;
}




int main(int argc, char** argv){

  key_t key;
  pid_t pid;
  int nbProd, nbConso, nbFils;
  int boolProdConso; /*0 : producteur  1 : consomateur*/

  if(argc < 3){
   perror("manque argument");
   exit(1);
  }
  
  nbProd=atoi(argv[1]);
  nbConso=atoi(argv[2]);
  nbFils= nbProd + nbConso;

  /*Creation memoire partagee*/
  key = ftok(argv[0], (char)getpid());
  if(( shm_id = shmget(key,sizeof(char)*10, 0666 | IPC_CREAT))==-1){
    perror("erreur creation shm");
    exit(0);
  }

  if((sem_id = semget(key, 2, IPC_CREAT | 0666))==-1){
    perror("erreur creation sem");
    exit(0);
  }

  semctl(sem_id, 0, SETVAL, 0);/*borne inferieur de la pile*/
  semctl(sem_id, 1, SETVAL, 9);/*borne superieur de la pile*/
  
  valAddr=shmat(shm_id, 0, 0666);

  do{
    if(nbProd>0){
      nbProd--;
      boolProdConso=0;
    }else{
      nbConso--;
      boolProdConso=1;
    }
    pid=fork();
  }while((nbProd+nbConso)>0 && pid!=0);

  /*Parite Fils */
  if(pid == 0){

    /*Partie Produtiteur*/
    if(boolProdConso == 0){

      printf("\nProducteur creer pid : %d \n",getpid());
      PRODUCTEUR
  
      
    }else{/*Partie Consomateur*/

      CONSOMMATEUR
    }
    
      
    
  }else{/*Parite Pere*/



    /*Fin des Fils*/
    while(nbFils>0){
      wait(NULL);
      nbFils--;
    }

     msgctl(shm_id, IPC_RMID,NULL);
     msgctl(sem_id, IPC_RMID,NULL);  

  }
  return 0;
}
