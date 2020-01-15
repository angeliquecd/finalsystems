struct song_node {
  char song_name[100];
  char artist[100];
  char album_name[100];
  char path[150];
  int genre;
  int next;
};
struct genre_index{
  int num;
  char name[];
}

struct song_node * newSong(char artisty[],char songy[],char albumy[],char pathy[],int genrey);
void print_list(int shmd);
void print_song(struct song_node * myNode);
void enter_song_data(int shmd) ;
struct song_node * populate_songs(int num);
int initSong(char pathp[],int i,int max);

//SONG LIBRARY STUFF--------------
int artists[100]; //stores shmids of songs starting each album
void initialize_table();
void add_song(int newSongshmd);
