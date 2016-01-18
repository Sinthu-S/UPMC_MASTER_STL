#define _SVID_SOURCE 1
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>

struct msqid_ds buf;

/*Message recu par le pere*/
struct message_pere{
  long id;
  int msgFils_id;
  int nbMess;
}msgPere;

/*Message recu par les fils*/
struct message_fils{
  long id;
  int val;
}msgFils;


int main(int argc, char** argv){

 key_t cle;
 int msgPere_id, msgFils_id;
 int nbProc;
 int nbFils, nbMessage;
 int sum=0;
 pid_t pid;
 msgPere.id=1;
 msgFils.id=2;


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
   pid=fork();
  
 }while(nbProc > 0 && pid != 0);

 if(pid == 0){
   printf("\n---------> Fils %d", getpid());
       /*Creation file msg pour fils */
   cle = ftok(argv[0], (char)getpid());
   if(( msgFils_id = msgget(cle, 0666 | IPC_CREAT))==-1){
     perror("erreur recup id file de message");
     exit(0);
   }

   /*Generation de la valeur*/
   srand(getpid());
   msgPere.nbMess=(int) (nbFils*(float)rand()/ RAND_MAX)+1;
   msgPere.msgFils_id=msgFils_id;

   /*Envoi de la valeur au pere*/
   if(msgsnd(msgPere_id , &msgPere, sizeof(int)*2,0) == -1){
     perror("erreur lecture msg");
     exit(0);
   }
   printf("\n---------> Fils %d envoie val=%d\n", getpid(), msgPere.nbMess);

   /*Lit tout les message envoyee par le pere*/
   while(msgPere.nbMess >0){
     
     if(msgrcv(msgFils_id, &msgFils, sizeof(int), 2, 0) == -1){
       perror("erreur envoie msg");
       exit(0);
     }
     /*fait la somme*/
     sum += msgFils.val;
     msgPere.nbMess--;
     printf("---------> Fils Valeur recu  %d pid %d\n", msgFils.val,getpid());
   }
   
   printf("----------------------------------------------------------->Somme des valeurs   %d pid %d\n", sum, getpid());

   /*detruit file de message du fils*/
   msgctl(msgFils_id, IPC_RMID,NULL);
  
   return 0;
 }else{
   /*Pour tous les fils lecture puis envoi des message*/
   while(nbFils>0){
     if(msgrcv(msgPere_id , &msgPere, sizeof(int)*2, 1,0) == -1){
       perror("erreur lecture msg");
       exit(0);
     }

     printf("\n-------------------------> Pere %d lecture val = %d\n", getpid(), msgPere.nbMess);

     
     for(nbMessage=msgPere.nbMess; nbMessage>0; nbMessage--){
       srand(msgFils.val);
       msgFils.val=(int) (100*(float)rand()/ RAND_MAX)+1;
       if(msgsnd(msgPere.msgFils_id, &msgFils, sizeof(int), 0) == -1){
	      perror("erreur envoie msg");
	 exit(   0);
       }
       printf("-------------------------> Pere Valeur envoyee  %d pid %d\n", msgFils.val, getpid());
     }
     nbFils--;
   }
      
   msgctl(msgPere_id, IPC_RMID,NULL);   
 }
   
 return 0;
}
