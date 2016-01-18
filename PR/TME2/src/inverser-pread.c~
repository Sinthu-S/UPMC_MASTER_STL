        #define _XOPEN_SOUCE 700
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>


int main(int argc, char** argv){
 int fd1;
 int fd2;
 char buff[1];
 int i=-2;//ignorer le '\0' et commencer lecture sur le dernier caractère
 
  if(argc < 2){
     perror("manque parametre");
     exit(1);
  }
 
 fd1=open( argv[1], O_RDONLY, S_IRUSR);
 fd2=open( "./result", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
 
 while(lseek(fd1,i,SEEK_END)!=-1 && read(fd1, buff, 1) > 0){
      printf("lit %c\n",buff[0]);
      write(fd2,buff,1);
      i--;
 }
 
 return 0;
 
}
