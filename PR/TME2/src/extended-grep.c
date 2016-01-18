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

int chercheChaine(char* nom, char* buff, char* chaine){
  
   
   if((f=fopen(nom,"r"))== NULL){
     perror("erreur d'ouverture du fichier %s", nom);
     return 1;
   }
   while(fgets(buff, sizeof(buff), f)!=NULL){
      if(strstr(buff, chaine)==NULL){
         printf(" Nom du fichier : %s", nom);
         (flag == 0) ? flag=1;
         close(f);
         return 0;
      }
   }
   
   

int main(int argc, char** argv){
   char *buff_path;

    File *f=NULL;
   
   if(argc < 3){
      perror("manque parametre(s)");
      exit(1);
   }

   
   if((pt_Dir = opendir(*argv[1])) == NULL){
      perror("erreur opendir");
      exit(1);
   }      
   
   buff_path=malloc(3*sizeof(*argv[2]));
   
   while ((dirEnt= readdir (pt_Dir)) !=NULL) {
		printf ("Repertoire %s\n", dirEnt->d_name);
	}
	closedir (pt_Dir);
	
	return 0;
   
   
      



}
