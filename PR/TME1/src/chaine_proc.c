#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[]){
  int nb=atoi(argv[1])+1;
  pid_t listPID[nb];
  int tube[2];
  pid_t fils;
  int nbPID=1;
  int i;
  int pere=0;
  int value;
  listPID[0]=getpid();
  pipe(tube);

  while(!pere){
    if((fils=fork())==0){
      listPID[nbPID]=getpid();
      if(++nbPID == nb){
	for(i=nb-1;i>-1;i--){
	  printf("Pid des processus %d : %d\n",i,listPID[i]);
	}
	close(tube[0]);
	value=(int)(rand () /(((double) RAND_MAX +1) /100));
	printf("Valeur generer : %d\n\n", value);
	write(tube[1],&value,sizeof(int));
	
	return EXIT_SUCCESS;
      }
    }else{
      pere=1;
      if(listPID[0]==getpid()){
	close(tube[1]);
	read(tube[0],&value,sizeof(int));
	printf("Valeur recu : %d\n\n", value);
      }
      wait(NULL);
      printf("Mon pid : %d \nPere pid : %d \nFils pid : %d\n\n",getpid(),getppid(),fils);
      return EXIT_SUCCESS;
    }
  
  }
}

/*
int main(int argc, char *argv[]){
  int nb=atoi(argv[1])+1;
  pid_t listPID[nb];
  pid_t fils;
  int nbPID=1;
  int i;
  int pere=0;
  listPID[0]=getpid();

  while(!pere){
    if((fils=fork())==0){
      listPID[nbPID]=getpid();
      if(++nbPID == nb){
	for(i=nb-1;i>-1;i--){
	  printf("Pid des processus %d : %d\n",i,listPID[i]);
	}
	return EXIT_SUCCESS;
      }
    }else{
      pere=1;
      wait(NULL);
      printf("Mon pid : %d \n Pere pid : %d \n Fils pid : %d\n",getpid(),getppid(),fils);
      return EXIT_SUCCESS;
    }
  
  }
}
*/
