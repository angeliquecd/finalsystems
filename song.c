struct song_node {
  char song_name[100];
  char artist[100];
  char album_name[100];
  char path[150];
  int genre;
  struct song_node *next;
};

struct song_node * newSong(char artisty[],char songy[],char albumy[],char pathy[],int genrey);
void print_list(struct song_node * myNode);
void print_song(struct song_node * myNode);
void enter_song_data(struct song_node * myNode) ;