# finalsystems
Systems Level Programming Final Project\
Angelique Charles-Davis (Pd. 5), Lauren Pehlivanian (Pd. 5), Claire Tempelman (Pd. 10)\
Our project allows the user to create and navigate their own music library.
Required libraries\
-Sox\
  apt-get install sox\
Instructions\
1. Compile the project by typing make, then run it by typing ./go. You will see a screen prompting you with the various actions you can take with the Library.
2. To start, type POPULATE, in all-caps as shown, and fill in the music library with information about the built-in files. This is a one-time only action. Trying to play or browse without populating the library will result in an empty library.
3. You can then choose to browse the library, create a playlist, play music, exit the library or delete it entirely. Follow the prompts to complete each action
4. When prompted, always type your choice in all-caps as a single word. (e.g If asked: "Would you like to play a SONG, PLAYLIST, GENRE or ALBUM?"" Type "ALBUM" to play an album.)
5. The only way to change the information about a single song is to repopulate the entire library.
6. If the library is deleted, it must be repopulated afterwards.
7. Exiting the program will not delete the library. Make sure to delete the library first to delete the shared memory segments.

Other information

It should have the following information in the following order:
Project Name
Team Members and class period(s)
Broad description of project
List of any required libraries
Include apt-get instructions on how to install the libraries
Instructions on how to use your project
Other information you deem important (known bugs, work citation, etc.)
