#include <setjmp.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

/****************************************/
/* Pour la commutation avec les signaux */
/*          2eme partie du TP           */
/****************************************/

#define MASK_ALARM()    sigprocmask(SIG_BLOCK, &mask_alarm, 0)
#define UNMASK_ALARM()  sigprocmask(SIG_UNBLOCK, &mask_alarm, 0)
#define delay 400000

void commut();

sigset_t mask_alarm;

void handler_clock(int n) {
   printf("election  \n");
  commut();
}

void initSig() {
  struct sigaction sa;

  sigemptyset(&mask_alarm);
  sigaddset(&mask_alarm, SIGALRM);
	
  sigaction(SIGALRM, 0, &sa);
  sa.sa_handler = handler_clock;
  sa.sa_flags |= SA_RESTART;
  sigaction(SIGALRM, &sa, 0);
  ualarm(delay, delay);
}

/*************************/
/* Gestion des processus */
/*************************/

// On utilisera cette variable "globale" pour retenir l'adresse du haut de la pile
char *top_stack;

// la dernière entrée du tableau (NPROC) est utilisée pour sauvegarder le main
#define SNONE  0
#define SSLEEP 1
#define SRUN   2
#define MAX_STACK_SIZE 1000
#define NPROC 10

// Cette structure contient tous ce qui necessaire a la gestion d'un processus
struct proc_s {
  int       flag;
  jmp_buf   buf;
  char      stack[MAX_STACK_SIZE];
  int       size;
} tproc[NPROC+1];

// La derniere entree du tableau (NPROC) est utilisee pour sauvegarder le main
//struct proc_s tproc[NPROC+1];

// Identifiant du processus courant
int cur = -1;

int election(int old) {

  /*
    parcourir le tableau et choisir celui qui est pret
  */
  
  // #####################################
  // ############ A COMPLETER ############
  // #####################################
	
  // Cette fonction implemente un simple round robin :
  // => les taches accedent au CPU les une après les autres sans se doubler
  // => on cherche (circulairement) dans le tableau le prochain processus pret (SRUN) 
  // Valeur de retour :
  // - index du processus elu qui doit etre a l'etat SRUN
  // - NPROC (id du main) s'il n'y a plus de processus
  //
  // Attention : cette fonction de modifie pas la variable "cur". 
  // Elle ne fait que retourner l'index d'un processus.


  int i;
  int j=old;
  printf("election %d \n", j);
  for(i=1;i<=NPROC;i++){
    j=(j+i)%(NPROC+1);
    printf("flag %d \n", tproc[j].flag);
    if(tproc[j].flag==SRUN){
      printf("election retour %d \n", j);
	return j;
    }
  }
  return NPROC;

}

int new_proc(int (*nomFonction)(int), int argFonction) {

  /*
    partir de la premier case et chercher une case vide -  SNONE = VIDE
  */

  // #####################################
  // ############ A COMPLETER ############
  // #####################################
	
  // Au demarrage :
  // 1) chercher une entree libre dans la table proc
  // 2) initialiser la structure
  // 3) sauvegarder le processus
  // 4) retourner 0
  // Apres le retour :
  // 1) demarrer la fonction
  // Apres la fin de la foncton (fin du processus)
  // 2) liberer l'entree (etat et desallocation pile)
  // 3) forcer le commut pour laisser la place a un autre processus.

  int i;
  int val;
 printf("new_proc\n");
  for(i=0;i<NPROC+1;i++){
    if(tproc[i].flag==SNONE)
      break;
  }
  if(i==NPROC){
 printf("i == NPROC \n");
    return -1;
  }else{
  printf("new_proc i = %d \n", i);
  tproc[i].flag=SRUN;
  val=sauvegarderProcessus(i);
   printf("val sauvegarde = %d \n", val);
  if(val==0){
 printf("new_proc apelle pas a la fonction\n");
    return 0;
  }else{
 printf("new_proc apelle a la fonction\n");
  (*nomFonction)(argFonction);
  tproc[i].flag=SNONE;
printf("commut new proc\n");
//commut();
kill(getpid(),SIGALRM);
  return 0;
  }
}
}

  /***************************************/
  /* Fonctions permettant la commutation */
  /***************************************/

  int sauvegarderProcessus(int idx) {

    /*
      debut et fin variable local;
      allocation et recopier avec memecpy
      sauvegarder et retourner 0
      avec la fin de la restauration (longjmp)

    
    */

    // #####################################
    // ############ A COMPLETER ############
    // #####################################

    // Lors de l'appel a la fonction :
    // 1) sauvegarder la pile
    // 2) sauvegarder de la taille de pile. Pourquoi la variable locale ne suffit pas ?
    // 3) sauvegarder les registres
    // 4) retourner 0
	
    // En cas de restauration :
    // 1) restaurer la pile
    // 2) UNMASK_ALARM() dans la deuxieme partie (avec les signaux)
    // 3) retourne la valeur fournie par le longjmp


    //idx est different de cur lors du longjmp!!!
int n=55+idx;
 
   int finVal=sigsetjmp(tproc[idx].buf,1);

    if(finVal==0){
      printf("sauvegarde :  %d\n",idx);
 printf("valeur de n avant:  %d\n",n);
    tproc[idx].size=top_stack-(char*)&finVal;
     memcpy(tproc[idx].stack,&finVal,tproc[idx].size);
      return 0;
    }

/*la valeur de finVal est ecraser*/
  
    printf("sauvegarde_retauration cur : %d  %d\n",cur, finVal);
	memcpy(&tproc[cur].stack[0], &finVal, 1);
    memcpy(top_stack-tproc[cur].size, tproc[cur].stack, tproc[cur].size+1);
    printf("sauvegarde_retauration cur apres : %d %d\n",cur,finVal);
 printf("valeur de n aprés:  %d\n",n);

    
    return finVal;
    
  }

int restaurerProcessus(int idx) {

  /*

      maj cur
      et longjmp
    */
	
    // #####################################
    // ############ A COMPLETER ############
    // #####################################

    // 1) enregistre l'index du nouveau processus (idx) comme processus courant
    // 2) lance la restauration des pointeurs
    // ?) la restauration de la pile peut elle avoir lieu dans cette fonction ?
    //comme le setjmp a été fait dans la fonction sauvegarderProcessus il faut faire 
    //la restauration dans cette fonction
    printf("restaure : %d \n",idx);
    cur=idx;
    siglongjmp(tproc[idx].buf,22+idx);

    return 0;
    
    
  }

  void commut() {
    printf("commut com\n");
    MASK_ALARM();
    if(sauvegarderProcessus(cur) == 0)
      restaurerProcessus(election(cur));
    UNMASK_ALARM();
    printf("fin commut\n");
  }

  int f(int p) {
        MASK_ALARM();
    int n = 0;
    int j;
    for(j=0; j<15; j++) { // 20
      printf("----------------------------------------------------------------f(%d) -> %d\n", p, n++);
      usleep(500000);
      // La ligne suivante est a commenter dans la deuxième partie du TP
      printf("commut f\n");
      //commut();
      UNMASK_ALARM();
  kill(getpid(),SIGALRM);
   

    }
    return 0;
  }

  int g(int p) {
    MASK_ALARM();
    int n = 0;
    int j;
    for(j=0; j<12; j++) {// 50
      printf("----------------------------------------------------------------g(%d) -> %d\n", p, n++);
      usleep(300000);
      // La ligne suivante est a commenter dans la deuxième partie du TP
      if(j%2 == 0){
	printf("commut g\n");
	//commut();
	 UNMASK_ALARM();
  kill(getpid(),SIGALRM);
       

      }
    }
    return 0;
  }

  int main() {
	
    // #####################################
    // ############ A COMPLETER ############
    // #####################################
	
    //  sauvegarder l'adresse du sommet de la pile dans la variable globale "top_stack"
 	
    int debut;
    top_stack=(char*)&debut;
  
 MASK_ALARM();
    new_proc(g,0);
    new_proc(f,4);
    UNMASK_ALARM();

    // Comme explique plus haut le main a pour id NPROC (derniere case du
    // tableau)
    cur = NPROC;

    // Dans un deuxieme temps vous decommenter la ligne suivante pour activer les
    // signaux
    initSig();
    printf("commut main\n");
    //commut();
    kill(getpid(),SIGALRM);
    printf("exit!!!\n");
    return 0;
  }
