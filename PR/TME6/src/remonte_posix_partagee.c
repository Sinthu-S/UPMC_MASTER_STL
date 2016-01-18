#define SVID_SOURCE 1
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/mman.h>
#include <time.h>
#include <fcntl.h>



int shm_id;



int remonte_pic(int n){
int nbProc=n;
int sum=0;
int val;
int idFils=-1;
pid_t pid;
int *valAddr;

 valAddr = mmap(NULL, sizeof(int)*n, PROT_READ | PROT_WRITE, MAP_SHARED, shm_id, 0);
do{
  idFils++;
  nbProc--;
  pid=fork();
}while(nbProc > 0 && pid != 0);

if(pid == 0){

  srand(getpid());
  val=(int) (10*(float)rand()/ RAND_MAX);

  *(valAddr + idFils) = val;

  printf("----->Valeur generer %d pid %d\n", val, getpid());
  return -1;
}else{

  while(nbProc<n){
    wait(NULL);
    nbProc++;
  }
   printf("\nLecture des messages\n\n");
  while(idFils>-1){
   
    val = *(valAddr + idFils);
    sum += val;
    printf("----->Valeur lu  :  %d pid %d\n", val, getpid());
    idFils--;
  }
   printf("\n\nSomme : %d \n\n", sum);
  return 1;
}
}


int main(int argc, char** argv){


int nb;

printf("\n\n Debut de programme \n\n");
if(argc < 2){
    perror("manque argument");
  exit(1);
}
nb=atoi(argv[1]);
 
 if(( shm_id= shm_open("shm_remonte", O_RDWR|O_CREAT, 0600))==-1){
  perror("erreur creation shm");
  exit(0);
 }

 if(ftruncate(shm_id, sizeof(int)*nb) == -1){
   perror("erreur ftruncte");
   exit(0);
 }



if(remonte_pic(nb)>-1)
  shm_unlink("shm_remonte");
return 0;
}
