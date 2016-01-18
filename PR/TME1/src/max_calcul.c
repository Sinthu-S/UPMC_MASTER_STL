#include <stdio.h>
#include <stdlib.h>
#include "../include/max_func.h"
// .. pour le dossier parents

int main(int argc, char *argv[]){
  int taille=argc-1;
  int tab[taille];
  int i;
  if(taille==0){
    printf("Aucun argument\n");
    
  }else{  
    for(i=0;i<taille;i++){
      tab[i]=atoi(argv[i+1]);

    }
    printf("Le maximum est : %d \n",max_func(tab,taille));
  }
  return 0;
}
