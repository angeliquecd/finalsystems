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

struct song_node * initSong(char pathp[]) {
  struct song_node * new = malloc(sizeof(struct song_node));
  new->path = pathp;
  return new;
}

struct song_node * populate_song() {
    char * dirname = "song/";
    DIR * dir = malloc(sizeof(DIR *));
    dir = opendir(dirname);
    if (printDirStatus(dir) == NULL) {
      printf("Directory invalid\n");
      return 0;
    }
    printf("Searching songs/ ... \n");
    struct dirent * cur = readdir(dir);

    struct stat * info; //var to store status of each file
    char fpath[100]; //stores file path
    //make names into arrays to use with strcpy
    if (cur != NULL) {
      info = malloc(sizeof(struct stat));
      strcpy(fpath, )
    }
}

struct song_node * newSong(char artisty[],char songy[],char albumy[],char pathy[],int genrey){
  struct song_node *new = malloc(sizeof(struct song_node));
  strncpy(new->artist, artisty, 100);
  strncpy(new->song_name,songy,100);
  strncpy(new->album_name, albumy, 100);
  strncpy(new->path, pathy, 100);
  new->genre = genrey;
  new->next = NULL;
  return new;
}

void print_song(struct song_node * myNode){
  printf(" %s: %s (%s)\n",myNode->artist,myNode->song_name,myNode->album_name);
}

void print_list(struct song_node * myNode) {
  //make new node copy, so as not to modify original pointer.
  struct song_node * newNode = myNode;
  //if current node is null, print nothing!
  if (newNode == NULL) {
    printf("{}\n");
    return;
  }
  //if it's not null:
  //loop which stops once there is no next node.
  while (newNode->next != NULL) {
    printf(" %s: %s |",newNode->artist,newNode->song_name);
    newNode = newNode->next;
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
  //get song Name
  printf("Enter song name: ");
  fgets(input, 100, stdin);
  myNode->song_name = input;

  //get artist
  printf("Enter artist name: ");
  fgets(input, 100, stdin);
  myNode->artist = input;

}
