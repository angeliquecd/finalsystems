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
#include "songLibrary.h"
#define KEY 10001
#define KEY2 1232
#define SEG_SIZE sizeof(struct song_node)

void initialize_table() {
  int i=0;
  for (int i=0;i<100;i++) {
    artists[i] = NULL;
  }
}

void add_song(int newSongshmd) {
  int i=0;
  int shmd2;
  struct song_node * newSong = shmat(newSongshmd,0,0);
  struct song_node * curSong;
  int placed = 0;

  //loop through albums to see if album already added
  while (artists[i] && placed == 0) {
    shmd2 = shmget(artists[i], SEG_SIZE, 0);
    curSong = shmat(shmd2,0,0);
    //found album!
    if (strcmp(newSong->artist, curSong->artist)) {
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
    artists[i] = newSongshmd;
  }
}
