// Filename: wordlist.cpp
// Benjamin Gofman, January 2025

#include "wordlist.h"
#include <iostream>

// Comparison function: determines if WordNode a should come before WordNode b
bool comesBefore(WordNode* a, WordNode* b) {
    if (a->freq != b->freq) return a->freq > b->freq;
    return a->word < b->word;
}

// Destructor: clean up all WordNode objects in the list
WordList::~WordList() {
    WordNode* cur = head;
    while (cur) {
        WordNode* next = cur->next;
        delete cur;
        cur = next;
    }
}

// Return pointer to head node
WordNode* WordList::getHead() {
    return head;
}

// Return number of words in this list
int WordList::getSize() {
    return size;
}

// Insert node at the front of the list
void WordList::pushFront(WordNode* node) {
    if (!node) return;
    
    node->next = head;
    node->prev = nullptr;
    
    if (head) head->prev = node;
    else tail = node;
    
    head = node;
}

// Insert node at the back of the list
void WordList::pushBack(WordNode* node) {
    if (!node) return;
    
    node->prev = tail;
    node->next = nullptr;

    if (tail) tail->next = node;
    else head = node;
    
    tail = node;
}

// Insert node before given position node
void WordList::insertBefore(WordNode* pos, WordNode* node) {
    if (!pos) {
        pushBack(node);
        return;
    }
    
    if (pos == head) {
        pushFront(node);
        return;
    }
    
    node->next = pos;
    node->prev = pos->prev;
    pos->prev->next = node;
    pos->prev = node;
}

// Insert word into list, maintaining sorted order by frequency then alphabetically
void WordList::insertAndSort(string& word) {
    // Check if word already exists
    WordNode* cur = head;
    while (cur) {
        // Found existing word - increment its frequency
        if (cur->word == word) {
            cur->freq++;  // Increase frequency count for this word
            
            // Bubble up if needed (maintain sorted order)
            // Move node forward in list while its frequency is higher than previous node
            // or same frequency but alphabetically earlier
            while (cur->prev && comesBefore(cur, cur->prev)) {
                WordNode* prev = cur->prev;  // Node that cur should come before

                // Step 1: Remove cur from its current position
                // Link prev node to next node (bypassing cur)
                if (cur->prev) cur->prev->next = cur->next;
                else head = cur->next;  // Special case: cur was at head
                
                // Link next node to prev node (bypassing cur)
                if (cur->next) cur->next->prev = cur->prev;
                else tail = cur->prev;  // Special case: cur was at tail
                
                // Step 2: Detach cur completely (prev and next pointers to null)
                cur->prev = cur->next = nullptr;
                
                // Step 3: Insert cur before its previous neighbor
                // This moves cur one position forward in the sorted list
                insertBefore(prev, cur);
            }
            return;
        }
        cur = cur->next;
    }
    
    // Word doesn't exist - create new node
    WordNode* newNode = new WordNode(word);
    size++;
    
    // Find correct position for new node
    // Traverse list until we find where newNode should be placed
    cur = head;
    while (cur && !comesBefore(newNode, cur)) {
        cur = cur->next;  // Keep moving forward if current node should come before newNode
    }

    // If we reached the end of list (cur is nullptr), newNode belongs at the end
    if (!cur) pushBack(newNode);
    // Otherwise, insert newNode before the node that should come after it
    else insertBefore(cur, newNode);
}