#include <stdio.h>
#include <stdlib.h>

int nfork(int nb_fils){
  int nb=0;
  while(nb_fils>nb){
    if(fork()==0){
  
      return 0;
    }else{
      nb++;
    }
  }
  return (nb==0) ? -1 : nb;
}

 int main (int arg, char* argv []) {
    int p;
    int i=1; int N = 3;
    do {
        p = nfork (i) ;
        if (p != 0 )
              printf ("%d \n",p);
    } while ((p ==0) && (++i<=N));
    printf ("FIN \n");    
   return EXIT_SUCCESS;
 }
