struct song_node {
  char song_name[100];
  char artist[100];
  char album_name[100];
  char path[150];
  int genre;
  int next;
};
char * GENRE_INDEX[] = {"Blues", "Rock", "Country", "Dance", "Hip-hop", "Funk", "Jazz", "Pop", "Metal", "Oldies", "Rhythm and Blues", "Rap", "Classical", "Reggae", "Indie", "Other"};

struct song_node * newSong(char artisty[],char songy[],char albumy[],char pathy[],int genrey);

//PRINTING FUNCTIONS
int print_list(int shmd, int num);
void print_song(struct song_node * myNode);
int print_song_shmd(int shmd, int num);
void print_library();

char * get_artist(int i);
void enter_song_data(int shmd, struct song_node * in) ;
struct song_node * populate_songs(int num);
int initSong(char pathp[],int i,int max);

//SONG LIBRARY STUFF--------------
int artists[100]; //stores shmids of songs starting each album
void initialize_table();
void add_song(int newSongshmd);
