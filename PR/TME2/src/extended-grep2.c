  #define _XOPEN_SOUCE 700
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>

extern int errno;

#define _POSIX_SOUCE 1
#define TAILLE_PATH 100

char buff_path [TAILLE_PATH];
DIR *pt_Dir;
struct dirent* dirEnt;
int flag=0;

int chercheChaine(char* chaine, char* buff, char* nom){
     FILE *f=NULL;
   
 
  if((f=fopen(nom,"r+"))== NULL){
    perror("erreur d'ouverture du fichier");
    return 1;
 
     }
     
     
  while(fgets(buff, sizeof(buff), f)!=NULL){
   
   
     if(strstr(buff, chaine)!=NULL){
        printf(" Nom du fichier : %s\n", nom);
        if(flag < 1)
              flag=1;
        break;
     }

//si la chaîne recherché est coupé
     if(strstr(buff, "\0")==NULL)
       fseek(f, -strlen(chaine)-1, SEEK_CUR);
     
  }
 
  fclose(f);
  return 0;
}
 
 

int main(int argc, char** argv){
  char *buff;

 
  if(argc < 3){
     perror("manque parametre(s)");
     exit(1);
  }

 
  if((pt_Dir = opendir(argv[2])) == NULL){
     perror("erreur opendir");
     exit(1);
  }      
 
  buff=malloc(3*sizeof(*argv[1]));
 
  while ((dirEnt= readdir (pt_Dir)) !=NULL) {       
       chercheChaine(argv[1], buff, dirEnt->d_name);         
              
  }      
  if(flag<1)
       printf("Aucun fichier valide\n");
       
       
        return 0;
 
 
     



}
