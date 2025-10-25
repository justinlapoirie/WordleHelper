// =======================================================
// Your name: Justin Lapoirie
// Compiler:  g++
// File type: header file helper.h
// @brief Defines functions needed for helper.cpp
//=======================================================

#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <vector>
#include <unordered_set>

class WordleHelper {
private:
    std::vector<std::string> allWords;     // Original word list (for restart)
    std::vector<std::string> words;        // Active filtered word list
    std::unordered_set<char> excluded;     // Letters not in the word
    std::unordered_set<char> included;     // Letters known to be in the word

    void loadWordsFromFile(const std::string& filename);
    void printWords() const;

public:
    WordleHelper(const std::string& filename);

    void reset();  // restart the helper
    void correct(const std::vector<std::pair<char, int>>& clues);
    void exclude(const std::vector<char>& letters);
    void wrongSpot(const std::vector<std::pair<char, int>>& clues); // replaces include
    void printStatus() const;

    void handleCommand(const std::string& input);
};

#endif
