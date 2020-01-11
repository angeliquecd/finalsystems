#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
//this is what executes at runtime
int main(int argc, char *argsv[]){
  char * s;
  printf("Welcome to the music center! How would you like to proceed?\n");
  printf("Type PLAY to play music\n");
  printf("Type CREATE to create a new playlist\n");
  printf("Type BROWSE to browse the library\n");
      //type artist, song title, album
  printf("Type ADD to add a song to your library\n");
  printf("Enter your selection: ");
  fgets(s,100,stdin);
if (strcmp(s[0],"PLAY\n")==0){
  printf("Would you like to play a playlist or a song?\n");
  fgets(s,100,stdin);
  if (strcmp(s[0],"SONG")==0){
    printf("Type the name of the song.");
//    fgets(    );
  //  sprintf(a,"")
  //  execvp("play",)
  }
}
}
