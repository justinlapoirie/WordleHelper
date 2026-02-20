# WordleHelper

A command-line tool written in C++ that helps you solve Wordle puzzles. After each guess in Wordle, 
you feed the result into WordleHelper using simple commands, and it narrows down the list of possible 
words based on what you know about the answer.

You can test it alongside the unlimited Wordle variant at https://wordleunlimited.org/


## Getting Started

### Installation

Clone the repository and navigate into the project directory:

    git clone https://github.com/justinlapoirie/WordleHelper.git
    cd WordleHelper

Build the project using the provided Makefile:

    make

Run the program:

    ./wordlehelper


## Usage

After launching the program, enter commands one at a time to describe the feedback Wordle gave you 
for each letter. The program will filter the word list after each input and display the remaining 
possible words (up to 100 results).

### Commands

    c <letter> <pos>      Mark a letter as correct and in the right position (green).
                          Position is 1-indexed (1 through 5).

    w <letter> <pos>      Mark a letter as present in the word but in the wrong position (yellow).
                          Position is 1-indexed (1 through 5).

    e <letters>           Exclude one or more letters entirely from the word (gray).
                          Multiple letters can be passed together, e.g. "e abc"

    r                     Restart and reset all filters.

    q                     Quit the program.

### Example Session

    > e trs
    > c a 2
    > w l 4
    [Program displays filtered word list]


## Project Structure

    helper.cpp       Core program logic
    helper.h         Header file
    words.txt        Word list used for filtering
    Makefile         Build configuration


## Planned Features

- A print command to display possible words even when there are more than 100 candidates
- Support for multiple inputs on a single line
- Basic prediction scoring to surface more likely answers
- Improved handling of double-letter edge cases
- An undo command to revert accidental inputs


## Author

Developed by Justin Lapoirie, October 2025.
