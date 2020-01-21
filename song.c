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
#define TAB_SIZE sizeof(int)*100
#define SEG_SIZE sizeof(struct song_node)

int initSong(char pathp[150],int i,int max) {
  int shmd, nextshmd;
  struct song_node *data;
  shmd=shmget(KEY2+i,SEG_SIZE,0);
//  printf("Got here.");
    if (shmd<0) printf("Error opening shared memory.");

  // data = malloc(sizeof(struct song_node));
  data = (struct song_node *) shmat(shmd,0,0);
  data->next = 0;
  strncpy(data->path, pathp, 150);//puts path onto shared memory pieces
    printf("%s and %d", data->path,data->next);
  printf("This is in init: %s",data->path);

//detatch shared memory
  int status = shmdt(data);
  if (status == -1) printf("error shmdting: %s", strerror(errno));

  return shmd;
}

void clear_library(){
  int i=0;
  int temp_shmid;
  struct song_node * cur;
  while(artists[i]) {
    temp_shmid = artists[i];
    cur = shmat(artists[i], 0, 0);
    while (cur->next){
      printf("\tREMOVING %d\n", temp_shmid);
      shmdt(cur);
      shmctl(temp_shmid, IPC_RMID, NULL);
      cur = shmat(cur->next, 0, 0);
      temp_shmid = cur->next;
    }
    //shmctl(artists[i], IPC_RMID, NULL);
    i++;
  }
}

struct song_node * populate_songs(int num) {
  struct song_node * cur_song; //current song being initialized and created.
  printf("# songs found: %d\n", num);
    struct song_node * song;
    int shmd, status,shmd2;
    int * artistshared;
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
    char fpath[150]; //stores file path
    //make names into arrays to use with strcpy
    while (cur != NULL) {
    //  while(times<1){
      //info = malloc(sizeof(struct stat));
      //check that entry is not a directory
      if (cur->d_type != DT_DIR) {
        strcpy(fpath, cur->d_name);
        printf("file: %s\n", fpath);
        // printf("i: %d\n", i);
        shmd = initSong(fpath,i,num);
        // printf("shmd: %d initialized.\n", shmd);
      //  printf("In populate: %s",s  ong->path);
        enter_song_data(shmd, cur_song);
        cur_song = (struct song_node * )shmat(shmd, 0, 0);
        // printf("init'ed song w artist=%s\n", cur_song->artist);
        // printf("init'ed song w name=%s\n", cur_song->song_name);
        // printf("init'ed song w next=%d\n", cur_song->next);
        add_song(shmd);
        status = shmdt(cur_song);
        if (status == -1) printf("error shmdting: %s", strerror(errno));
  i++;
      }
      cur = readdir(dir);
  }
  //  printf("%p vs. %p",song, data);
    // shmdt(song);
    shmd2=shmget(KEY,TAB_SIZE,0);
    artistshared = (int *) shmat(shmd2,0,0);
    memcpy(artistshared, artists, TAB_SIZE);
    shmdt(artistshared);
    shmd2=shmget(KEY,TAB_SIZE,0);
    artistshared = (int * ) shmat(shmd2,0,0);
    printf("shared memory: [%d] [%d]",artistshared[0],artistshared[1]);
    shmdt(artistshared);
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
  printf(" %s: %s (%s), genre %s \n",myNode->artist,myNode->song_name,myNode->album_name,GENRE_INDEX[myNode->genre]);
}

int print_song_shmd(int shmd, int num) {
  int out; //next shmd, return value
  struct song_node * myNode = (struct song_node * ) shmat(shmd, 0, 0);
  printf("\t[%d] %s: %s (%s)\n",num, myNode->artist,myNode->song_name,myNode->album_name);
  out = myNode->next;
  //detatch shared memory
  int status = shmdt(myNode);
  if (status == -1) printf("error shmdting: %s\n", strerror(errno));

  return out;
}

//prints each artist bucket (start w first shmd)
int print_list(int shmd, int num) {
  //make new node copy, so as not to modify original pointer.
  struct song_node * newNode = (struct song_node * )shmat(shmd, 0, 0);
  if (newNode == -1) {
    printf("error shmating for shmd=%d\n", shmd);
    return -1;
  }

  //if current node is null, print nothing!
  if (shmd == 0) {
    printf("{}\n");
    return -1;
  }
  //if it's not null:
  //loop which stops once there is no next node.
  while (shmd) {
    //printf("shmd:%d\n", shmd);
    shmd = print_song_shmd(shmd, num);
    num++;
    // printf("next song in bucket...\n");
  }

  printf("\n");

  //detach shared memory
  int status = shmdt(newNode);
  if (status == -1) printf("error shmdting: %s\n", strerror(errno));
  //nvm if there is no next
  //printf("]");

  return num;
}

//returns artist associated with given index/bucket in artists table
char * get_artist(int place) {
  char * out;
  int status;
  struct song_node * first = (struct song_node * ) shmat(place, 0, 0);
  if (first == -1) printf("error shamtting: %s", strerror(errno));
  printf("\tbucket node: ");
  print_song(first);
  if (first == NULL) {
    printf("error shmating for shmd=%d\n", place);
    return out;

  } //else printf("success shmating to get artist!\n");

  // return first->artist;
  printf("\tartist: %s\n", first->artist);
  strcpy(out,first->artist);
  //printf("artist: %s\n", out);

  //detach shared memory
  status = shmdt(first);
  if (status==-1) printf("erroring shmdting. %s\n", strerror(errno));

  return out;
}

//iterates through list (each artist bucket)
//returns an updated num (the id of the song we are up to)
int findIdInList(int num, int id) {
  int status, shmd;
  //get first song node in bucket
  struct song_node * newNode = (struct song_node * ) shmat(shmd, 0, 0);
  if (newNode == NULL) {
    printf("error shmating for shmd=%d\n", shmd);
    return -1;
  }
  //if current node is null
  if (shmd == 0) return -1;
  //if it's not null:
  //loop which stops once there is no next node.
  while (shmd) {
    shmd = newNode->next;
    status = shmdt(newNode);
    if (status == -1) printf("error shmdting: %s", strerror(errno));
    num++;
    if (num == id) return num;
  }
  return num; //id never matched num
}

//once you know the id is found inthis list
//loop through list to find the path of the id
//parameters: i is the idx of the artists array, id is the target id, num is the current id we hve looped up to.
struct song_node * getNodeFromList(int id, int i, int num) {
  struct song_node * myNode = (struct song_node * )shmat(artists[i], 0, 0);
  int shmd;
  while (num < id) {
    shmd = myNode->next;
    shmdt(myNode);
    myNode = (struct song_node * )shmat(shmd, 0, 0);
    num ++;
  }
  //at this point myNode is the target node
  return myNode;
}

//returns song node based on its id.
//iterates through library same way as print_library().

char * getPath(int place) {
  char * out;
  int status;
  printf("Get path starting");
  struct song_node * first = shmat(place, 0, 0);
  if (first == NULL) {
    printf("error shmating for shmd=%d\n", place);
    return out;
  } //else printf("success shmating to get artist!\n");
out=first->path;
printf("Get path returning: %s\n",out);

//shmdt(first);
  //return out;
//  printf("[]%s %s]",first->path,first->song_name);
  return out;}

struct song_node * getNode(int id) {
  char * path;
  int i=0;
  int num=1;
  while (artists[i] && num < id) {
    num = findIdInList(num, id);
    //if shmd was invalid
    if (num == -1) {
      printf("Song not found.\n");
      return NULL;
    }
    if (num == id) {
      printf("ID found in bucket %d\n", i);
      return getNodeFromList(id, i, num);
    }
    i++;
  }
  return NULL;
}

//prints entire library based on artists array
int print_library() {
//printf("Here\n");
   int i=0;
  int num=1;
   int shmd;
   char * artist;
   struct song_node * cur;
  // printf("Here");
   shmd=shmget(KEY,TAB_SIZE,0);
   if (shmd<0) printf("Error shmgetting");
    int * artistshared=(int *)shmat(shmd,0,0);
  if (artistshared<0) printf("Error shmatting");
  // printf("Here");
   //printf("artistshared: %d",artistshared[0]);
   int * lookat=artistshared;
   //printf("%d",lookat[i]);
   while (lookat[i]){
     //printf("ID is: %d",lookat[i]);
     cur = (struct song_node *) shmat(lookat[i], 0, 0);
    printf("BUCKET: %s\n", cur->artist);
    shmdt(cur);
  //   // printf("shmd: %d\n", artists[i]);
    num = print_list(lookat[i], num);
    i++;
     printf("checking next bucket...%d\n",i);
  //   //i++;
//  i++;
   }
shmdt(artistshared);
return num;
}


//prompts user to enter data for a song, fills in this data to struct
void enter_song_data(int shmd, struct song_node * myNode) {
  myNode = (struct song_node * ) shmat(shmd, 0, 0);
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

  //get album
  printf("Enter album name: ");
  fgets(input, 100, stdin);
  sep = &input[0];
  strncpy(myNode->album_name, strsep(&sep, "\n"), 100);

  //get genre
  printf("Enter genre number:\n");
  printf("0: Blues\n1: Rock\n2: Country\n3: Dance\n4: Hip-hop\n5: Funk\n6: Jazz\n7: Pop\n");
  printf("8: Metal\n9: Oldies\n10: Rhythm and Blues\n11: Rap\n12: Classical\n13: Reggae\n14: Indie\n15: Other\n");
  fgets(input, 100, stdin);
  sep = &input[0];
  int g;
  sscanf(sep, "%d", &g);
  myNode->genre = g;

  print_song(myNode);

  int status = shmdt(myNode);
  if (status == -1) printf("error shmdting: %s", strerror(errno));
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
  int shmd2, status;
  struct song_node * newSong = (struct song_node * ) shmat(newSongshmd,0,0);
  print_song(newSong);

  struct song_node * curSong;
  int placed = 0;

  printf("ARTISTS:\n");
  while(artists[i]) {
    printf("shmd:%d\n", artists[i]);
    i++;
  }
  i=0;

  //loop through albums to see if album already added
  while (artists[i] != 0 && placed == 0) {
    //printf("shmd = %d. artist here: %s", artists[i], get_artist(i));
    shmd2 = artists[i];
    curSong = (struct song_node * )shmat(shmd2,0,0);
    if (curSong == NULL) printf("error shmating. %s\n", strerror(errno));
    //printf("\tchecking \n");
    //print_song(curSong);
    //found album!
    printf("comparing to shmd %d:\n", shmd2);
    printf("\t%s\n", curSong->artist);
    printf("\t%s\n", newSong->artist);
    if (strcmp(newSong->artist, curSong->artist) == 0) {
      printf("Artist matched! Placing at [%d]\n",i);
      //loop until end of songs in album to place new song
      while(curSong->next) {
        shmd2 = curSong->next;
        status = shmdt(curSong);
        if (status == -1) printf("0error shmdting: %s", strerror(errno));
        curSong = (struct song_node * ) shmat(shmd2, 0, 0);
      }
      curSong->next = newSongshmd;
      placed = 1;
    }
    i++;
  }
  //didn't find album in list, add to end
  if (placed == 0) {
    printf("Making new bucket. placing at [%d]\n",i);
    artists[i] = newSongshmd;
  }

  //detach song nodes
  status=shmdt(newSong);
  if (status == -1) printf("1error shmdting: %s", strerror(errno));

  //free(curSong);

}
char * get_title(int id){
  char * out;
  int status;
  struct song_node * first = shmat(id, 0, 0);
  if (first == NULL) {
    printf("error shmating for shmd=%d\n", id);
    return out;
  } //else printf("success shmating to get artist!\n");
strcpy(out,first->song_name);
shmdt(first);
printf("Get title returning: %s",out);
  return out;
}

int getNext(int id){
  int out;
  int status;
  struct song_node * first = shmat(id, 0, 0);
  if (first == NULL) {
    printf("error shmating for shmd=%d\n", id);
    return out;
  } //else printf("success shmating to get artist!\n");
out=first->next;
shmdt(first);
printf("Get next returning: %d",out);
  return out;
}

char * searchsongs(char * artist, char * title){
  int i;
  int shmd=shmget(KEY,TAB_SIZE,0);
  int * artistshared=shmat(shmd,0,0);
  while (artistshared[i]){
    struct song_node * newNode=shmat(artistshared[i],0,0);
    while (newNode!=NULL && strcpy(artist,get_artist(artistshared[i]))==0){
      if (strcpy(newNode->song_name,title)==0){
        return getPath(artistshared[i]);
      }
      newNode=shmat(newNode->next,0,0);
    }
  i++;
    }
    return "hi";
  }
