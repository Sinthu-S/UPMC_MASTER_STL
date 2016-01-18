#define SVID_SOURCE 1
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>

struct msqid_ds buf;
struct message{
 long id;
 int val;
}msg;

int msg_id;



int remonte_pic(int n){
 int nbProc=n;
 int sum=0;
 pid_t pid;



 do{
   nbProc--;
   pid=fork();
 }while(nbProc > 0 && pid != 0);

 if(pid == 0){

   srand(getpid());
   msg.val=(int) (10*(float)rand()/ RAND_MAX);
   msg.id=1;
   if(msgsnd(msg_id, &msg, sizeof(int), 0) == -1){
     perror("erreur envoie msg");
     exit(0);
   }

   printf("----->Valeur generer %d pid %d\n", msg.val,getpid());
   return -1;
 }else{
 
   while(nbProc<n){
     wait(NULL);
     nbProc++;
   }
    printf("\nLecture des messages\n\n");
   while(nbProc>0){
     if(msgrcv(msg_id , &msg , sizeof(int), 1,0) == -1){
        perror("erreur lecture msg");
        exit(0);
     }
     sum += msg.val;
     printf("----->Valeur lu  : %d pid %d\n", msg.val, getpid());
     nbProc--;
   }
    printf("\n\nSomme : %d \n\n", sum);
   return 1;
 }
}


int main(int argc, char** argv){

 key_t cle;
 int nb;

 printf("\n\n Debut de programme \n\n");
 if(argc < 2){
     perror("manque argument");
   exit(1);
 }
 nb=atoi(argv[1]);
 cle = ftok(argv[0], (char)getpid());
 if(( msg_id = shmget(cle,sizeof(struct message)*nb, 0666 | IPC_CREAT))==-1){
   perror("erreur creation shm");
   exit(0);
 }


 
 if(remonte_pic(nb)>-1)
   msgctl(msg_id, IPC_RMID,NULL);
 return 0;
}
