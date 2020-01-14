#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/wait.h>
#include "song.h"
#define KEY 10001
#define KEY2 1232
#define SEG_SIZE sizeof(struct song_node)
struct song_node * initSong(char pathp[],int i,int max) {
  int shmd, nextshmd;
  struct song_node *data;
  struct song_node *datanext;
  shmd=shmget(KEY2+i,SEG_SIZE,0);
//  printf("Got here.");
    if (shmd<0) printf("Error opening shared memory.");
  data=(struct song_node *) shmat(shmd,0,0);
//  printf("The id is: %d\n",shmd);
if (max-i>1){
  nextshmd=shmget(KEY2+1+i,SEG_SIZE,0);
  data->next= nextshmd;}
  else data->next = 0;
  strncpy(data->path, pathp, 150);//puts path onto shared memory pieces
//    printf("%s and %d", data->path,data->next);
//  printf("This is in init: %s",data->path);
  return data;
}

struct song_node * populate_songs(int num) {
    struct song_node * song;
    int shmd;
    struct song_node *data;
    char * dirname = "songs/";
    int i=0;
    DIR * dir = malloc(sizeof(DIR *));
    dir = opendir(dirname);
    if (!dir) {
      printf("Directory invalid\n");
      return 0;
    } else printf("Success opening directory!\n");
    printf("Searching songs/ ... \n");
    struct dirent * cur = readdir(dir);
int times=0;
    struct stat * info; //var to store status of each file
    char fpath[100]; //stores file path
    //make names into arrays to use with strcpy
    while (cur != NULL) {
    //  while(times<1){
      //info = malloc(sizeof(struct stat));
      //check that entry is not a directory
      if (cur->d_type != DT_DIR) {
        strcpy(fpath, cur->d_name);
        printf("file: %s\n", fpath);
        song = initSong(fpath,i,num);
      //  printf("In populate: %s",song->path);
        enter_song_data(song);
        printf("artist: %s | name: %s\n\n", song->artist, song->song_name);
//times++;
  i++;
      }
      cur = readdir(dir);
  //  }
  }
  //  printf("%p vs. %p",song, data);
    shmdt(song);
    return song;
  }

struct song_node * newSong(char artisty[],char songy[],char albumy[],char pathy[],int genrey){
  struct song_node *new = malloc(sizeof(struct song_node));
  strncpy(new->artist, artisty, 100);
  strncpy(new->song_name,songy,100);
  strncpy(new->album_name, albumy, 100);
  strncpy(new->path, pathy, 100);
  new->genre = genrey;
  new->next = 0;
  return new;
}

void print_song(struct song_node * myNode){
  printf(" %s: %s (%s)\n",myNode->artist,myNode->song_name,myNode->album_name);
}

void print_list(struct song_node * myNode) {
  //make new node copy, so as not to modify original pointer.
  struct song_node *data;
  struct song_node * newNode = myNode;
  //if current node is null, print nothing!
  if (newNode == NULL) {
    printf("{}\n");
    return;
  }
  //if it's not null:
  //loop which stops once there is no next node.
  while (newNode->next != 0) {
    printf(" %s: %s |",newNode->artist,newNode->song_name);
      newNode=(struct song_node *) shmat(newNode->next,0,0);
  }
  printf(" %s: %s",newNode->artist, newNode->song_name);
  //there is no next node, but still need to print current (last) node:
  //printf(" %s: %s ",newNode->artist,newNode->name);
  printf("\n");
  //nvm if there is no next
  //printf("]");
  return;
}
//prompts user to enter data for a song, fills in this data to struct
void enter_song_data(struct song_node * myNode) {
  char input[100];
  char * sep; // used for strsep
  //get song Name
  printf("Enter song name: ");
  fgets(input, 100, stdin);
  //strncpy(input, strsep(&strncpy(sep, input, 100), "\n")); <- was trying to get rid of the /n after the input
  sep = &input[0];
  strncpy(myNode->song_name, strsep(&sep, "\n"), 100);

  //get artist
  printf("Enter artist name: ");
  fgets(input, 100, stdin);
  sep = &input[0];
  strncpy(myNode->artist, strsep(&sep, "\n"), 100);
  // strncpy(sep, input, 100);
  // sep = strsep(&sep, "\n");
  // strncpy(input, sep, 100); <- trying to get rid of \n
}

// int main() {
//   populate_songs();
//   return 0;
// }
