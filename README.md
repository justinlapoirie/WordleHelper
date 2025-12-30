  Wordle Helper program: Use command-argument inputs to exclude letters, indicate letters that
are in the word but at the wrong index, and letters that are in the word and at the correct index.
Test the program here using the unlimited wordle website: https://wordleunlimited.org/ 

To run the program, navigate to the directory the files are downloaded to, then type "make", followed by "./wordleHelper"
COMMANDS:
- c < letter > < pos >  (correct spot)
- w < letter > < pos >  (wrong spot but included)
- e < letters >         (exclude letters)
- r                     (restart)
- q                     (quit)

Potential Upcoming changes: 
- add print command to allow users to view potential words even when there are more than 100 possible choices
- allow users to provide multiple inputs in the same line (requires some algorithm restructuring)
- Basic prediction functionality that indicates more likely word choices out of given possibilities

Developed by Justin Lapoirie, 10/24/2025
