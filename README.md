# finalsystems
Systems Level Programming Final Project\
Angelique Charles-Davis, Lauren Pehlivanian, Claire Tempelman

A statement of the problem you are solving and/or a high level description of the project:\
Our project will handle music files. It will access the user's files, search for music type/mp3 files, and organize playlists based on artist, album and genre. The user will be able to edit their library by deleting artists, albums or songs, by shuffling or by creating their own playlists that  are saved onto the computer. The user will also be able to play song files, one at a time. We're also going to try to implement features such as pausing a song or skipping a song on the playlist.

A description as to how the project will be used (describe the user interface).\
The interface will be text based, asking for a directory of songs, and then asking for an artist, album, or genre to make a playlist for. The user can then input when to pause or skip a song. 

A description of your technical design. This should include:
How you will be using the topics covered in class in the project.
  - stored in a linked list (structs and malloc)
  - playing songs would require forking and exec, as well as seeking etc
  - the user will access files to create playlists. This would also require shared memory while the user browses the library and adds to the playlist file at the same time (similar to semaphone)
  - semaphores used to make sure only one song plays at a time
  - displaying song info (length, artist, location in drive) will require finding out info about the file

How you are breaking down the project and who is responsible for which parts.
1. Constructing a linked list based on actual mp3 files (reworking myTunes) - Claire
2. Seeking mp3 files in a given directory - Angelique
3. Figuring out how to get data like artist and album from an mp3 file - Lauren
4. Creating playlists from a user input using shared memory - Claire
5. Implementing a semaphore so only one song will play at a time - Angelique
6. Figuring out pausing or skipping a song on a playlist - Lauren
Depending on how long each step takes we will probably collaborate on some steps.

What data structures you will be using and how.
  - structs as in the myTunes Project

What algorithms and /or data structures you will be using, and how.
  - we will be looking for a library that can be used to play audio from a file (last year I found a comparable library in Java to play a constructed song)

A timeline with expected completion dates of parts of the project.\
Step 1 should not be too difficult, only a couple days after project approval.\
Same for step 2.\
Step 3 requires some research, depending on how easy it is to get that information it should take about 3 days.\
Step 4 is the most difficult step, probably 5 days.\
Step 5, depending on how step 4 is accomplished, should be fine, 2 days.\
Step 6 is extra depending on how much time we left after we complete the previous steps.
