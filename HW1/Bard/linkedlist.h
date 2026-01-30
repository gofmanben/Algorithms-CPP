// Filename: linkedlist.h
// Benjamin Gofman, January 2025

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "linkedlist.h"
#include "wordlist.h"
#include <ostream>

// ListNode structure: represents a bucket for words of specific length
struct ListNode
{
    int len;                   // Word length for this bucket
    WordList children;         // List of words of this length
    ListNode *prev = nullptr;  // Previous node in bucket list
    ListNode *next = nullptr;  // Next node in bucket list

    // Constructor: initialize with word length
    ListNode(int wordLen) {
        len = wordLen;
    }
};

// LinkedList class: manages buckets of words sorted by word length
class LinkedList
{
private:
    ListNode *head = nullptr;  // First bucket in list
    ListNode *tail = nullptr;  // Last bucket in list

    // Private helper methods for list manipulation
    void insertBefore(ListNode *pos, ListNode *node);
    void pushFront(ListNode *node);
    void pushBack(ListNode *node);

public:
    ~LinkedList();                           // Destructor
    ListNode *getHead();                     // Get head node
    WordNode *getHeadNode(ListNode *head);   // Get head of word list in bucket
    ListNode *findOrCreateNode(int wordLen); // Find or create bucket for word length
};

#endif