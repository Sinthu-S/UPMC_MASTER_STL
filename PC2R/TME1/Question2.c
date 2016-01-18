#include <stdio.h>
#include <stdlib.h>

int main(){
  int i=0;

  if(fork() != 0){
    printf("Processus pere, entrer une valeur\n");
    scanf("%d",&i);
    printf("Processus pere, valeur de i : %d\n", i);
  }else{
    sleep(4);
    printf("Processus fils, valeur de i : %d\n", i);
  }
    
}
