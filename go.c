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
// #include "songLibrary.c"
#include "song.c"
#define KEY2 1232
#define KEY 10001
#define TAB_SIZE sizeof(int)*100
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
  shmget(KEY,TAB_SIZE, IPC_CREAT | 0644);
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
  printf("Type DELETE to delete the library\n");
  printf("Type EXIT to exit the program\n");
  printf("Enter your selection: ");

  fgets(s,100,stdin);
  sep = &s[0];
  printf("You chose: %s\n",strsep(&sep,"\n"));
if (strcmp(s,"PLAY")==0){
  char play[100] ="play ";
  char ** command=malloc(200);
  command[0]="play";
  printf("\nWould you like to play a SONG, GENRE, ALBUM, ARTIST or PLAYLIST?\n");
  //i think we can take out the possibility of songs w the same name as the album and artists w the same name as the song
  fgets(s,100,stdin);
  strsep(&sep,"\n");
  printf("You chose: %s\n",s);
if (strcmp(s,"PLAYLIST")==0){

}
if (strcmp(s,"ALBUM")==0){

}
if (strcmp(s,"GENRE")==0){

}
if (strcmp(s,"ARTIST")==0){
  printf("Enter the artist name: ");
  fgets(s,100,stdin);
  sep = &s[0];
  strsep(&sep,"\n");
  int a=0;
  int shmd=shmget(KEY,TAB_SIZE,0);
  int * artistshared;
artistshared=shmat(shmd,0,0);
  printf("%d",artistshared[a]);
   while(artistshared[a]){
//   //  printf("%s vs. ",s);
//   //  printf("%s\n",get_artist(artistshared[a]));
     if (strcmp(s,get_artist(artistshared[a]))==0){
       char * path=getPath(artistshared[a]);
//printf("path: %s",path);
char songs[100]="songs/";
  strcat(songs,path);
  printf("songs: %s",songs);
    command[1]=songs;
    printf("%s",command[1]);
      printf("In here");
       execvp("play",command);
    }
    a++;
  }
}
}
if (strcmp(s,"POPULATE")==0){
  //printf("Song library: ");
  // struct song_node *hello =initSong("hell0",0);
  // // printf("%s",hello->path);
  // shmd=shmget(KEY2,1,0);
  //   data=( struct song_node *) shmat(shmd,0,0);
  // printf("%p or %d",data,shmd);
  initialize_table();
  populate_songs(i);
  int c=0;
  printf("artist array shmds: ");
  while (artists[c]){
    printf("%d,  ", artists[c]);
    c++;
  }
  printf("\n");
  //prints library
  //this is where you can search for, delete songs
  //add songs?
}
if (strcmp(s,"BROWSE")==0){
printf("Song library: \n");
// struct song_node * test = shmat(artists[0], 0, 0);
// printf("TEST: %s\n", test->artist);
// printf("next: %d/n", test->next);
// test = shmat(test->next, 0, 0);
// printf("TEST2: %s \n", test->artist);
// shmdt(test);
print_library();

}
if (strcmp(s,"CREATE")==0){
  //makes a lil shell where you can write to playlists
  //i think we agreed that playlists are text files w a list of song addresses
  printf("Welcome to the playlist maker! Enter the title of your new playlist: ");
  //get name of playlist
  char name[100];
  char * sep;
  fgets(name,100,stdin);
  sep = &name[0];
  strsep(&sep,"\n");
  printf("\tYour playlist: %s\n", name);

  //create file for playlist
  int fd = open(strcat(name, ".txt"), O_CREAT | O_RDWR, 664);
  if (fd < 0){
    printf("errno %d error: %s\n", errno, strerror(errno));
  }
  printf("Playlist started! Enter the name of a song to add: ");
  char * song;
  fgets(song,100,stdin);
  strsep(&song,"\n");
  // searchsongs(song);
  write(fd, song, 100);
  if (write < 0){
    printf("errno %d error: %s\n", errno, strerror(errno));
  }
  printf("Are you done building the playlist? y/n ");
  char * done;
  fgets(done,100,stdin);
  strsep(&done,"\n");
  if (strcmp(done, "n") == 0){
    while (strcmp(done, "n") == 0){
      printf("Enter the name of a song to add: ");
      fgets(song,100,stdin);
      strsep(&song,"\n");
      // searchsongs(song);
      write(fd, song, 100);
      if (write < 0){
        printf("errno %d error: %s\n", errno, strerror(errno));
      }
      printf("Are you done building the playlist? y/n ");
      fgets(done,100,stdin);
      strsep(&done,"\n");
    }
}
}
if (strcmp(s,"DELETE")==0){
  int a;
  for ( a=0;a<i;a++){
  shmd=shmget(KEY2+a,SEG_SIZE,0);
  q=shmctl(shmd,IPC_RMID,0);
}
shmd=shmget(KEY,TAB_SIZE,0);
//printf("%d",shmd);
q=shmctl(shmd,IPC_RMID,0);
printf("Library deleted.\n");
}

}
  shmdt(data);
  printf("\nExiting the program.\n");
}
