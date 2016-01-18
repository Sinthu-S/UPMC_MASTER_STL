#define _SVID_SOURCE 1
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>



struct message_pere{
 long id;
 int val;
}msg;



int main(int argc, char** argv){

key_t cle;
int msgPere_id, msgFils_id;
int nbProc;
 int nbFils, nbMessage, indiceType=0;
int sum=0;
pid_t pid;


if(argc < 2){
    perror("manque argument");
  exit(1);
}

nbProc=atoi(argv[1]);
nbFils=nbProc;

printf("\n\n Debut de programme nbProc : %d \n\n", nbProc);

/*Creation file msg du pere*/
cle = ftok(argv[0], (char)getpid());
if(( msgPere_id = msgget(cle, 0666 | IPC_CREAT))==-1){
  perror("erreur recup id file de message");
  exit(0);
}


/*Creation des fils*/
do{
  nbProc--;
  /*Incrementation de indiceType pour identifier les fils*/
  indiceType++;
  
  pid=fork();
 
}while(nbProc > 0 && pid != 0);

if(pid == 0){
  printf("\n---------> Fils %d", getpid());


  /*Generation de la valeur*/
  srand(getpid());
  msg.val=(int) (nbFils*(float)rand()/ RAND_MAX)+1;
  indiceType *= 2;/*si paire envoyee par fils si impaire envoyee par pere*/
  msg.id=indiceType;
  nbMessage=msg.val;
  /*Envoi de la valeur au pere*/
  if(msgsnd(msgPere_id , &msg, sizeof(int),0) == -1){
    perror("erreur lecture msg");
    exit(0);
  }
  printf("\n---------> Fils %d envoie val=%d\n", getpid(), msg.val);

  /*Lit tout les message envoyee par le pere*/
  while(nbMessage>0){
   
    if(msgrcv(msgPere_id, &msg, sizeof(int), indiceType+1 , 0) == -1){
      perror("erreur envoie msg");
      exit(0);
    }
    /*fait la somme*/
    sum += msg.val;
    nbMessage--;
    printf("---------> Fils Valeur recu  %d pid %d\n", msg.val,getpid());
  }
 
  printf("----------------------------------------------------------->Somme des valeurs   %d pid %d\n", sum, getpid());

  
  return 0;
}else{
  /*Pour tous les fils lecture puis envoi des message*/
  printf("\n---------> Pere %d", getpid());
  nbProc=nbFils;
  while(nbFils>0){
    if(msgrcv(msgPere_id , &msg, sizeof(int), (nbFils)*2,0) == -1){
      perror("erreur lecture msg");
      exit(0);
    }

    printf("\n-------------------------> Pere %d lecture val = %d\n", getpid(), msg.val);

   
    for(nbMessage=msg.val; nbMessage>0; nbMessage--){
      srand(msg.val);
      msg.val=(int) (100*(float)rand()/ RAND_MAX)+1;
      msg.id=(nbFils)*2+1;
      if(msgsnd(msgPere_id, &msg, sizeof(int), 0) == -1){
              perror("erreur envoie msg");
         exit(   0);
      }
      printf("-------------------------> Pere Valeur envoyee  %d pid %d\n", msg.val, getpid());
    }
    nbFils--;
  }


  while(nbProc>0){
    wait(NULL);
    nbProc--;
  }
     
  msgctl(msgPere_id, IPC_RMID,NULL);  
}
 
return 0;
}
