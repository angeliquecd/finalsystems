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
  char s[100];
  printf("Welcome to the music center! How would you like to proceed?\n");
  printf("Type PLAY to play music\n");
  printf("Type CREATE to create a new playlist\n");
  printf("Type BROWSE to browse the library\n");
      //type artist, song title, album
  printf("Type ADD to add a song to your library\n");
  printf("Enter your selection: ");
  fgets(s,100,stdin);
  printf("%s",s);
if (strcmp(s,"PLAY\n")==0){
  printf("Type the name of the song, artist, playlist or album you'd like to listen to:");
  //i think we can take out the possibility of songs w the same name as the album and artists w the same name as the song
  fgets(s,100,stdin);
  strsep(s,"\n");
  printf("%s",s);
  //searches songs
//  if song name matches it plays and that's that
    //if song has album name in id it plays and album mode is set, same for artist
//searches playlists
  //if it finds playlist name, does a for or while loop of songs in the playlist
  //if album mode is set, after first song plays it seeks out the next song with that album in its id etc
  //same with artist mode
  //
  }
if (strcmp(s,"BROWSE")==0){
  //prints library
  //this is where you can search for, delete songs
  //add songs?
}
if (strcmp(s,"CREATE")==0){
  //makes a lil shell where you can write to playlists
  //i think we agreed that playlists are text files w a list of song addresses
}
}
