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

int initSong(char pathp[],int i,int max) {
  int shmd, nextshmd;
  struct song_node *data;

  shmd=shmget(KEY2+i,SEG_SIZE,0);
//  printf("Got here.");
    if (shmd<0) printf("Error opening shared memory.");

  data=(struct song_node *) shmat(shmd,0,0);
  data->next = 0;
//  printf("The id is: %d\n",shmd);
// if (max-i>1){
//   nextshmd=shmget(KEY2+1+i,SEG_SIZE,0);
//   data->next= nextshmd;
//
//
// }
//   else data->next = 0;
//   strncpy(data->path, pathp, 150);//puts path onto shared memory pieces
// //    printf("%s and %d", data->path,data->next);
// //  printf("This is in init: %s",data->path);
  return shmd;
}

struct song_node * populate_songs(int num) {
  printf("# songs found: %d\n", num);
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
        printf("i: %d\n", i);
        shmd = initSong(fpath,i,num);
        printf("shmd: %d initialized.\n", shmd);
      //  printf("In populate: %s",s  ong->path);
        enter_song_data(shmd);
        add_song(shmd);

//times++;
  i++;
      }
      cur = readdir(dir);
  //  }
  }
  //  printf("%p vs. %p",song, data);
    // shmdt(song);

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
  printf(" %s: %s (%s), genre %d \n",myNode->artist,myNode->song_name,myNode->album_name,myNode->genre);
}

int print_song_shmd(int shmd ) {
  struct song_node * myNode = shmat(shmd, 0, 0);
  printf(" %s: %s (%s)\n",myNode->artist,myNode->song_name,myNode->album_name);
  return myNode->next;
}

//prints each artist bucket (start w first shmd)
void print_list(int shmd) {
  //make new node copy, so as not to modify original pointer.
  // struct song_node * newNode = shmat(shmd, 0, 0);

  //if current node is null, print nothing!
  if (shmd == 0) {
    printf("{}\n");
    return;
  }
  //if it's not null:
  //loop which stops once there is no next node.
<<<<<<< HEAD
  while (shmd) {
    printf("shmd:%d\n", shmd);
    shmd = print_song_shmd(shmd);
    printf("next song in bucket...\n");
  }
=======
  while (newNode->next != 0) {
    printf(" %s: %s (%s), genre %d \n",newNode->artist,newNode->song_name,newNode->album_name,newNode->genre);
      newNode=(struct song_node *) shmat(newNode->next,0,0);
  }
  printf(" %s: %s (%s), genre %d \n", newNode->artist,newNode->song_name,newNode->album_name,newNode->genre);
>>>>>>> 7f535b8f56689e1a0bcd334b148df777f0b47333
  //there is no next node, but still need to print current (last) node:
  //printf(" %s: %s ",newNode->artist,newNode->name);
  printf("\n");
  //nvm if there is no next
  //printf("]");
  return;
}

//prints entire library based on artists array
void print_library() {
  int i=0;
  while (artists[i]){
    //printf("shmd: %d\n", artists[i]);
    print_list(artists[i]);
    i++;
    printf("checking next bucket...\n");
  }
}


//prompts user to enter data for a song, fills in this data to struct
void enter_song_data(int shmd) {
  struct song_node * myNode = shmat(shmd, 0, 0);
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

<<<<<<< HEAD
  //get album info
=======
  //get album
>>>>>>> 7f535b8f56689e1a0bcd334b148df777f0b47333
  printf("Enter album name: ");
  fgets(input, 100, stdin);
  sep = &input[0];
  strncpy(myNode->album_name, strsep(&sep, "\n"), 100);
<<<<<<< HEAD
=======

  //get genre
  printf("Enter genre number:\n");
  printf("0: Blues\n 1: Rock \n 2: Country\n 3: Dance\n4: Hip-hop\n5: Funk\n6: Jazz\n7: Pop\n");
  printf("8: Metal\n9: Oldies\n10:Rhythm and Blues \n11: Rap\n 12: Classical\n 13: Reggae\n14: Indie\n15: Other\n");
  fgets(input, 100, stdin);
  sep = &input[0];
  int g;
  sscanf(sep, "%d", &g);
  myNode->genre = g;

>>>>>>> 7f535b8f56689e1a0bcd334b148df777f0b47333
  // strncpy(sep, input, 100);
  // sep = strsep(&sep, "\n");
  // strncpy(input, sep, 100); <- trying to get rid of \n
  print_song(myNode);
}


//SONG LIBRARY FUNCTIONS----------------------------
void initialize_table() {
  int i=0;
  for (int i=0;i<100;i++) {
    artists[i] = 0;
  }
}

void add_song(int newSongshmd) {
  printf("adding ");
  int i=0;
  int shmd2;
  struct song_node * newSong = shmat(newSongshmd,0,0);
  print_song(newSong);

  struct song_node * curSong;
  int placed = 0;

  //loop through albums to see if album already added
  while (artists[i] && placed == 0) {
    shmd2 = artists[i];
    curSong = shmat(shmd2,0,0);
    printf("\tchecking ");
    print_song(curSong);
    //found album!
    if (strcmp(newSong->artist, curSong->artist) == 0) {
      printf("placing at [%d]\n",i);
      //loop until end of songs in album to place new song
      while(curSong->next) {
        shmd2 = curSong->next;
        curSong = shmat(shmd2, 0, 0);
      }
      curSong->next = newSongshmd;
      placed = 1;
    }
    i++;
  }
  //didn't find album in list, add to end
  if (placed == 0) {
    printf("placing at [%d]\n",i);
    artists[i] = newSongshmd;
  }
}
