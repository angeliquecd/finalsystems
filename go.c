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
#include "song.c"
#define KEY2 1232

#define SEG_SIZE sizeof(struct song_node)
//this is what executes at runtime
int initmem(){
  int i=0;
  int shmd;
  char * dirname = "songs/";
  DIR * dir = malloc(sizeof(DIR *));
  dir = opendir(dirname);
  if (!dir) {
    printf("Directory invalid\n");
    return 0;
  }
  struct dirent * cur = readdir(dir);
  while (cur != NULL) {
    if (cur->d_type != DT_DIR) {
        shmd=shmget(KEY2+i,SEG_SIZE, IPC_CREAT | 0644);
      //  printf("Id created: %d\n",shmd);
    //    printf("I is: %d\n",i);
          i++;
    }
    cur = readdir(dir);
  }
  return i;
}
int main(int argc, char *argsv[]){
  int shmd, q;
  int i=0;
  char s[100];
  char * sep;
  struct song_node *data;
i=initmem();
  printf("Welcome to the music center! How would you like to proceed?\n");
    while (strcmp(s,"EXIT")!=0){
  printf("Type POPULATE to populate the library\n");//temporary button
  printf("Type PLAY to play music\n");
  printf("Type CREATE to create a new playlist\n");
  printf("Type BROWSE to browse the library\n");
      //type artist, song title, album
  printf("Type ADD to add a song to your library\n");
  printf("Type DELETE to delete the library and free up space on your harddrive\n");
    printf("Type EXIT to exit the program\n");
  printf("Enter your selection: ");

  fgets(s,100,stdin);
  sep = &s[0];
  printf("You chose: %s\n",strsep(&sep,"\n"));
// if (strcmp(s,"PLAY")==0){
//   printf("\nWould you like to play a song, album, artist or playlist?\n");
//   //i think we can take out the possibility of songs w the same name as the album and artists w the same name as the song
//   fgets(s,100,stdin);
//   strsep(&sep,"\n");
//   printf("You chose: %s\n",s);
//   if (strcmp(s,SONG)==0){
//     printf("Type the name and artist of the song you would like to play.\n");
//     char * path;
//     char * song;
//     fgets(song,100, stdin);
//   //  path= searchsongs(song); //will return the path, null if there is no such song
//   // if path!=NULL then
//   f=fork();
//   if (f){
//     wait(&status);
//   }
//   else{
//     char * commands[];
//     comands[0]="play"
//     commands[1]=path
//     execvp("play","")
//   }
//   }
//   shmd=shmget(KEY2,SEG_SIZE,0);
//   printf("You ")
//   //printf("Did that");
//   data=( struct song_node *) shmat(shmd,0,0);
//   findsong();
//   fork();{


  //searches songs
//  if song name matches it plays and that's that
    //if song has album name in id it plays and album mode is set, same for artist
//searches playlists
  //if it finds playlist name, does a for or while loop of songs in the playlist
  //if album mode is set, after first song plays it seeks out the next song with that album in its id etc
  //same with artist mode
  //
  //}
if (strcmp(s,"POPULATE")==0){
  //printf("Song library: ");
  // struct song_node *hello =initSong("hell0",0);
  // // printf("%s",hello->path);
  // shmd=shmget(KEY2,1,0);
  //   data=( struct song_node *) shmat(shmd,0,0);
  // printf("%p or %d",data,shmd);
  populate_songs(i);
  //prints library
  //this is where you can search for, delete songs
  //add songs?
}
if (strcmp(s,"BROWSE")==0){
   int a =0;
  shmd=shmget(KEY2+a,SEG_SIZE,0);
  if (shmd<0) printf("Error with browse. %d",errno);
  //printf("Did that");
  data=( struct song_node *) shmat(shmd,0,0);
//  printf("%p or %d",data,shmd);
printf("Song library: \n");
//printf("The id is: %d",shmd);
  //print_song(data);
  print_list(data);
}
if (strcmp(s,"CREATE")==0){
  //makes a lil shell where you can write to playlists
  //i think we agreed that playlists are text files w a list of song addresses
}
if (strcmp(s,"DELETE")==0){
  int a;
  for ( a=0;a<i;a++){
  shmd=shmget(KEY2+a,SEG_SIZE,0);
  q=shmctl(shmd,IPC_RMID,0);
}
printf("Library deleted.");
}
shmdt(data);
}
printf("\nExiting the program.\n");
}
