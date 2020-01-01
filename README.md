# finalsystems
Systems Level Programming Final Project
Angelique Charles-Davis, Lauren Pehlivanian, Claire Tempelman

A statement of the problem you are solving and/or a high level description of the project:
Our project will handle music files. It will access the user's files, search for music type/mp3 files, and organize playlists based on artist, album and genre. The user will be able to edit their library by deleting artists, albums or songs, by shuffling or by creating their own playlists that have are saved onto the computer. The user will also be able to play song files, one at a time.

A description as to how the project will be used (describe the user interface).

A description of your technical design. This should include:
-How you will be using the topics covered in class in the project.
Notes:
  -stored in a linked list (structs and malloc)
  -playing songs would require forking and exec
  -accessing files to create playlists. This would also require shared memory while the user browses the library and adds to the playlist file (similar to semaphone)
  -semaphores used to make sure only one song plays at a time?
  -displaying song info (length, artist, location in drive)

-How you are breaking down the project and who is responsible for which parts.
-What data structures you will be using and how.
-What algorithms and /or data structures you will be using, and how.

A timeline with expected completion dates of parts of the project.
