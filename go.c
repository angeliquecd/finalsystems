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
#include <signal.h>
// #include "songLibrary.c"
#include "song.c"
#define KEY2 1232
#define KEY 10001
#define TAB_SIZE sizeof(int)*100
#define SEG_SIZE sizeof(struct song_node)
pid_t cpid;
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
          i++;
    }
    cur = readdir(dir);
  }
  shmget(KEY,TAB_SIZE, IPC_CREAT | 0644);
  return i;
}

static void handle_sig(int signo){
  printf("Signal is: %d\n",signo);
  if (signo==SIGINT){
    printf("Stopping player.\n");
    exit(0);
  }
  //kill(cpid, 9);}
  /*
  if (signo==SIGSTOP){
    printf("Pausing player.\n");
    //kill(cpid, SIGSTOP);
  }
  if (signo==SIGCONT){
    printf("Resuming player.\n");
    //kill(cpid, SIGCONT);
  }
  */
}

int main(int argc, char *argsv[]){
  int shmd, q;
  int library_created = 1;
  //see if artists[0] has shmd in it to see if library was created.
  shmd = shmget(KEY, TAB_SIZE, 0);
  // int * arts = (int *) shmat(shmd, 0, 0);
  // if (arts[0]) library_created = 1;
  // shmdt(arts);

  int i=0;
  char s[100];
  char * sep;
  struct song_node *data;
i=initmem();
  printf("\nWelcome to the music center! How would you like to proceed?\n\n");
    while (strcmp(s,"EXIT")!=0){
  printf("Type POPULATE to populate the library\n");//temporary button
  printf("Type PLAY to play music\n");
  printf("Type CREATE to create a new playlist\n");
  printf("Type BROWSE to browse the library\n");
      //type artist, song title, album
  printf("Type DELETE to delete the library. Then exit and restart.\n");
  printf("Type EXIT to exit the program\n");
  printf("\nEnter your selection: ");

  fgets(s,100,stdin);
  sep = &s[0];
  strsep(&sep,"\n");
  //printf("You chose: %s\n",strsep(&sep,"\n"));
if (strcmp(s,"PLAY")==0){
  int f, status;
  char play[100] ="play ";
  char ** command=malloc(200);
  command[0]="play";
  char songs[100]="songs/";
  int a =0;
  int id, num; //num songs in libnrary
  int shmd=shmget(KEY,TAB_SIZE,0);
  int * artistshared;
artistshared=shmat(shmd,0,0);
  printf("\nWould you like to play a SONG, ARTIST or PLAYLIST?\n");
  //i think we can take out the possibility of songs w the same name as the album and artists w the same name as the song
  fgets(s,100,stdin);
  sep = &s[0];
  strsep(&sep,"\n");
  printf("You chose: [%s]\n",s);
if (strcmp(s,"SONG")==0){
  char fpath[100];
  char * dirname = "songs/";
  num = print_library();
  printf("Enter the song ID to play: ");
  fgets(s,100,stdin);
  //GET ID AS int
  sep = &s[0];
  sep = strsep(&sep,"\n");
  //printf("You entered: %s\n", input);
  //convert string input to int id:
  id = atoi(sep);
  if (id > num || id < 1) {
    printf("Please enter a valid ID.\n\n");
  } else {
  //printf("\tid: %d\n", id);
  struct song_node * song = getNthNode(id);
  //fpath = song->path;
  sep = &song->path[0];
  sep = strsep(&sep, "\n");

  //add songs/ to path
  strcat(fpath, dirname);
  strcat(fpath, sep);

  command[1] = fpath;
 printf("\n\nCURRRENTLY PLAYING: %s\n",command[1]);
   cpid=fork();
   if (cpid){//parent
  //   printf("%d in sigint",cpid);
     signal(SIGINT,handle_sig);
     wait (&status);
   }
   else
   { // printf("%d not in sigint",cpid);
     execvp("play",command);
   }
   shmdt(song);
}}
if (strcmp(s,"PLAYLIST")==0){
  printf("Your playlists:\n");
  print_playlists();
  printf("Enter the playlist name: ");
  //char * fpath = malloc(100); //file path for song (songs/ + name)
  char * fpaths[100]; //array of all paths in playlist file
  int i=0;
  for (i=0;i<100;i++) {
    fpaths[i] = NULL;
  }
  char fpath[100];
  char * dirname = "songs/";
  fgets(s,100,stdin);
  sep = &s[0];
  strsep(&sep,"\n");
  int fd = open(strcat(s, ".txt"), O_RDONLY);
  if (!fd) printf("error opening %s: %s", s, strerror(errno));
//  printf("opening: %s\n", s);
  char * buff = malloc(1000);
  int status = read(fd, buff, 1000);
//  printf("all files: %s\n", buff);
  //separate all files by \n, store in fpaths
  i=0;
  char * token;
  char * path;
  printf("Songs in playlist '%s':\n", s);
  while (buff) {
    token = strsep(&buff, "\n");
  //  printf("Token: %s",token);
    //if token is a path name (sometimes spacing is weird)
    if (strlen(token) > 0) {
      fpaths[i] = token;
      printf("\t[%d]: %s\n", i, token);
      i++;
    }
  }
  if (i==0) printf("No songs found.\n");
  i=0;
  //printf("done. \n");
  while (fpaths[i]){
    // status = read(fd,buff,100);
    //get path of current song
    strcat(fpath, dirname);
    strcat(fpath, fpaths[i]);
    command[1]=fpath;
    printf("\n\nCURRENTLY PLAYING: %s\n", fpath);
    cpid=fork();
    if (cpid){//parent
      //printf("%d in sigint",cpid);
      signal(SIGINT,handle_sig);
      wait (&status);
    }
    else
    {  //printf("%d not in sigint",cpid);
      execvp("play",command);
    }
    //reset dirname and fpath
    dirname = "songs/";
    memset(fpath, 0, 100);
    //get next line
    i++;
  }
  if (status == -1) printf("error reading from %s: %s", s, strerror(errno));
  //free(buff);
}
if (strcmp(s,"ARTIST")==0){
  num = print_library();
  printf("Enter the artist name: ");
  fgets(s,100,stdin);
  sep = &s[0];
  strsep(&sep,"\n");
  a=0;
  //printf("%d",artistshared[a]);
while(artistshared[a]){
//   //  printf("%s vs. ",s);
//   printf("%s\n",get_artist(artistshared[a]));
 if (strcmp(s,get_artist(artistshared[a]))==0){
   shmd=artistshared[a];
  while(shmd){
    strncpy(songs,"songs/",100);
       char * path=getPath(shmd);
//printf("path: %s",path);
  strcat(songs,path);
  //printf("songs: %s",songs);
    command[1]=songs;
    //printf("%s",command[1]);
      //printf("In here");
      cpid = fork();
      if (cpid){
        signal(SIGINT,handle_sig);
        wait (&status);
        shmd=getNext(shmd);
      }

      else{
        execvp("play",command);
    }
  }
printf("%d",shmd);
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
  // clear_library();

  initialize_table();
  populate_songs(i);
  library_created = 1;
  // int c=0;
  // printf("artist array shmds: ");
  // while (artists[c]){
  //   printf("%d,  ", artists[c]);
  //   c++;
  // }
  printf("\n");
  //prints library
  //this is where you can search for, delete songs
  //add songs?
}
if (strcmp(s,"BROWSE")==0){
  if (library_created == 1) {
    printf("Song library: \n");
    // struct song_node * test = shmat(artists[0], 0, 0);
    // printf("TEST: %s\n", test->artist);
    // printf("next: %d/n", test->next);
    // test = shmat(test->next, 0, 0);
    // printf("TEST2: %s \n", test->artist);
    // shmdt(test);
    print_library();
  } else {
    printf("You must first populate your library.\n");
  }

}
if (strcmp(s,"CREATE")==0){
  if (library_created == 1) {
    int num; //represents number of songs in library
    int id; //song id user chooses to add to playlist
    int status;
    char * path;
    char * input = malloc(10); //user input used throughout.
    char * done = malloc(10); //is user done creating playlist ("y" / "n")
    struct song_node * song;
    //done = "n";
    //makes a lil shell where you can write to playlists
    //i think we agreed that playlists are text files w a list of song addresses
    printf("Welcome to the playlist maker! Enter the title of your new playlist: ");
    //get name of playlist
    char name[100];
    char * sep;
    fgets(name,100,stdin);
    sep = &name[0];
    strsep(&sep,"\n");
    //printf("\tYour playlist: %s\n", name);

    //create file for playlist
    int fd = open(strcat(name, ".txt"), O_CREAT | O_RDWR, O_APPEND | O_RDWR);
    if (fd < 0) printf("errno %d error: %s\n", errno, strerror(errno));

    printf("Playlist '%s' started!\n", name);
    //continuous loop for user to add songs until they say stop
    while (strcmp(done, "y") != 0) {
      num = print_library(); // num represents total songs
      printf("Total # songs: %d\n", num);
      printf("Enter the ID of a song to add: ");
      if (fgets(input,10,stdin) == NULL) printf("error getting input: %s", strerror(errno));
      // printf("You entered: %s\n", input);
      input = strsep(&input,"\n");
      //printf("You entered: %s\n", input);
      //convert string input to int id:
      id = atoi(input);

      //user entered non-number
      if (id == 0) {
        printf("Please enter a number!\n");
      }
      //id is not valid
      else if (id > num || id <= 0) {
        printf("Please enter an ID that is in range!\n");
      }
      //input is a valid id
      else {
        // sprintf(input, "%d", id);
        // status = write(fd, input, sizeof(input));
        song = getNthNode(id); // <- doesn't work but eventually will be code to get the path based on id
        path = song->path;
        printf("\tAdding: ");
        print_song(song);

        //strcat(path,"\n");
        status = write(fd, path, strlen(path));
        if (status == 0) printf("errno %d error: %s\n", errno, strerror(errno));
      }
      printf("Are you done building the playlist? y/n ");
      fgets(done,100,stdin);
      done = strsep(&done,"\n");
      //printf("your input: %s\n", done);
    }
  } else {
    printf("You must first create the library.\n");
  }

}
 if (strcmp(s,"DELETE")==0){
  int a;
 for ( a=0;a<i;a++){
   shmd=shmget(KEY2+a,SEG_SIZE,0);
   q=shmctl(shmd,IPC_RMID,0);
 }
shmd=shmget(KEY,TAB_SIZE,0);
 printf("%d",shmd);
 q=shmctl(shmd,IPC_RMID,0);
//
//   del_library(i);
//   library_created = 0;
// clear_library();
printf("Library deleted.\n");
}

}
  shmdt(data);
  printf("\nExiting the program.\n");
  exit(0);
}
