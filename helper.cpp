// =======================================================
// Your name: Justin Lapoirie
// Compiler:  g++
// File type: cpp file helper.cpp
// @brief Allows user to input functions with different letter combinations to help find solutions to Wordle
//=======================================================

#include "helper.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;

// Constructor, im
WordleHelper::WordleHelper(const string& filename) {
    loadWordsFromFile(filename);
}

void WordleHelper::loadWordsFromFile(const string& filename) {
    ifstream file(filename);
    string word;
    allWords.clear();
    words.clear();

    while (file >> word) {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        allWords.push_back(word);
    }

    words = allWords;
}

void WordleHelper::reset() {
    words = allWords;
    excluded.clear();
    included.clear();
    cout << "Word list and memory reset.\n";
    printStatus();
}

void WordleHelper::printWords() const {
    if (words.empty()) {
        cout << "No words remaining.\n";
        return;
    }

    if (words.size() <= 100) {
        const int cols = 5;      // number of columns per row
        const int width = 12;    // column width for formatting

        cout << left;
        for (size_t i = 0; i < words.size(); ++i) {
            cout << setw(width) << words[i];
            if ((i + 1) % cols == 0) cout << '\n';
        }
        if (words.size() % cols != 0) cout << '\n';
    } else {
        cout << "Remaining words: " << words.size() << "\n";
    }
}

void WordleHelper::printStatus() const {
    cout << "----------------------------------\n";
    cout << "Remaining words: " << words.size() << "\n";
    cout << "Excluded letters: ";
    for (char c : excluded) cout << c << " ";
    cout << "\nIncluded letters: ";
    for (char c : included) cout << c << " ";
    cout << "\n----------------------------------\n";
    printWords();
}

void WordleHelper::correct(const vector<pair<char, int>>& clues) {
    vector<string> filtered;

    for (const string& w : words) {
        bool match = true;
        for (auto [ch, pos] : clues) {
            if (pos < 0 || pos >= (int)w.size() || w[pos] != ch) {
                match = false;
                break;
            }
        }
        if (match) filtered.push_back(w);
    }

    words = move(filtered);
    printStatus();
}

void WordleHelper::exclude(const vector<char>& letters) {
    for (char c : letters) excluded.insert(c);

    vector<string> filtered;
    for (const string& w : words) {
        bool containsExcluded = false;
        for (char c : w) {
            if (excluded.count(c)) {
                containsExcluded = true;
                break;
            }
        }
        if (!containsExcluded) filtered.push_back(w);
    }

    words = move(filtered);
    printStatus();
}

void WordleHelper::wrongSpot(const vector<pair<char, int>>& clues) {
    // Add all letters from clues into the included set
    for (auto [ch, _] : clues) included.insert(ch);

    vector<string> filtered;

    for (const string& w : words) {
        bool valid = true;

        // Each clue: letter is in word but not at given pos
        for (auto [ch, pos] : clues) {
            if (pos < 0 || pos >= (int)w.size()) {
                valid = false;
                break;
            }
            // If the word has the letter in that wrong spot → reject
            if (w[pos] == ch) {
                valid = false;
                break;
            }
            // The word must contain the letter somewhere else
            if (w.find(ch) == string::npos) {
                valid = false;
                break;
            }
        }

        // Also ensure it doesn't violate excluded letters
        if (valid) {
            for (char c : w) {
                if (excluded.count(c)) {
                    valid = false;
                    break;
                }
            }
        }

        if (valid) filtered.push_back(w);
    }

    words = move(filtered);
    printStatus();
}

void WordleHelper::handleCommand(const string& input) {
    stringstream ss(input);
    string cmd;
    ss >> cmd;

    if (cmd == "exit" || cmd == "q") {
        cout << "Goodbye!\n";
        exit(0);
    }
    else if (cmd == "restart" || cmd == "r") {
        reset();
    }
    else if (cmd == "c" || cmd == "correct") {
        vector<pair<char, int>> clues;
        char ch; int pos;
        while (ss >> ch >> pos) clues.push_back({ch, pos - 1});
        correct(clues);
    }
    else if (cmd == "w" || cmd == "wrong") {
        vector<pair<char, int>> clues;
        char ch; int pos;
        while (ss >> ch >> pos) clues.push_back({ch, pos - 1});
        wrongSpot(clues);
    }
    else if (cmd == "e" || cmd == "exclude") {
        vector<char> letters;
        char ch;
        while (ss >> ch) letters.push_back(ch);
        exclude(letters);
    }
    else if (cmd == "p" || cmd == "print") {
        printStatus();
    }
    else {
        cout << "Unknown command. Use:\n";
        cout << "  c <letter> <pos> ...   (correct spot)\n";
        cout << "  w <letter> <pos> ...   (wrong spot but included)\n";
        cout << "  e <letters>            (exclude letters)\n";
        cout << "  r                      (restart)\n";
        cout << "  q                      (quit)\n";
    }
}

// ------------------ main ------------------
int main() {
    WordleHelper helper("words.txt");

    cout << "Wordle Helper Started!\n";
    cout << "Commands:\n";
    cout << "  c <letter> <pos> ...   correct letter/position\n";
    cout << "  w <letter> <pos> ...   in word but wrong position\n";
    cout << "  e <letters>            exclude letters\n";
    cout << "  r                      restart\n";
    cout << "  q                      quit\n";

    string input;
    while (true) {
        cout << "\n> ";
        getline(cin, input);
        helper.handleCommand(input);
    }

    return 0;
}
