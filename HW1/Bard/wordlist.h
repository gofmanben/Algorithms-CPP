// Filename: wordlist.h
// Benjamin Gofman, January 2025

#ifndef WORDLIST_H
#define WORDLIST_H

#include <string>
using namespace std;

// WordNode structure: represents a single word and its frequency
struct WordNode {
    int freq;                  // Frequency of the word
    string word;               // The word itself
    WordNode* prev = nullptr;  // Previous word in list
    WordNode* next = nullptr;  // Next word in list
    
    // Constructor: initialize with word, frequency starts at 1
    WordNode(string& w) {
        freq = 1;
        word = w;
    }
};

// WordList class: manages doubly-linked list of WordNodes sorted by frequency then alphabetically
class WordList {
private:
    int size = 0;             // Number of words in list
    WordNode* head = nullptr; // First word in list
    WordNode* tail = nullptr; // Last word in list
    
    // Private helper methods for list manipulation
    void pushFront(WordNode* node);
    void pushBack(WordNode* node);
    void insertBefore(WordNode* pos, WordNode* node);
    
public:
    ~WordList();                    // Destructor
    WordNode* getHead();            // Get head node
    void insertAndSort(string& word);  // Insert word maintaining sort order
    int getSize();                  // Get list size
};

#endif