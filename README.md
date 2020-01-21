# Music Player
Systems Level Programming Final Project
Angelique Charles-Davis (Pd. 5), Lauren Pehlivanian (Pd. 5), Claire Tempelman (Pd. 10)

Our project allows the user to create and navigate their own music library. The user can populate the library with their own songs, add new songs, browse the library and most importantly, play music.

Required libraries
-Sox
  apt-get install sox

Instructions
1. Compile the project by typing make , then run it by typing ./go . You will see a screen prompting you with the various actions you can take with the Library
3. To start, type POPULATE, in all-caps as shown, and fill in the music library with information about the built-in files. This is a one-time only action. Trying to play or browse without populating the library will result in an empty library.
4. You can then choose to browse the library, create a playlist, play music, exit the library or delete it entirely. Follow the prompts to complete each action
5. When prompted, always type your choice in all-caps as a single word
  e.g If asked: "Would you like to play a SONG, PLAYLIST, GENRE or ALBUM?"" Type "ALBUM" to play an album.
6. To pause a song, hit ctrl-z while the song is playing. To stop a song, hit ctrl-c while the song is playing.
7. The only way to change the information about a single song is to repopulate the entire library.
8. If the library is deleted, it must be repopulated afterwards.
9. Exiting the program will not delete the library

Other information:
1. Currently we are working on getting rid of a seg fault when the library is populated with more than 2 mp3 files. This has also made testing some of our code difficult.
