// Filename: linkedlist.cpp
// Benjamin Gofman, January 2025

#include "linkedlist.h"

// Destructor: clean up all ListNode objects in the list
LinkedList::~LinkedList() {
    ListNode* cur = head;
    while (cur) {
        ListNode* next = cur->next;
        delete cur;
        cur = next;
    }
}

// Return pointer to head node
ListNode* LinkedList::getHead() {
    return head;
}

// Get head WordNode from a ListNode's children list
WordNode* LinkedList::getHeadNode(ListNode* node) {
    return node ? node->children.getHead() : nullptr;
}

// Insert node at the front of the list
void LinkedList::pushFront(ListNode* node) {
    if (!node) return;
    
    node->next = head;
    node->prev = nullptr;
    
    if (head) head->prev = node;
    else tail = node;
    
    head = node;
}

// Insert node at the back of the list
void LinkedList::pushBack(ListNode* node) {
    if (!node) return;
    
    node->prev = tail;
    node->next = nullptr;
    
    if (tail) tail->next = node;
    else head = node;
    
    tail = node;
}

// Insert node before given position node
void LinkedList::insertBefore(ListNode* pos, ListNode* node) {
    if (!node) return;
    
    if (!pos || pos == head) {
        pushFront(node);
        return;
    }
    
    node->next = pos;
    node->prev = pos->prev;
    pos->prev->next = node;
    pos->prev = node;
}

// Find existing ListNode for word length or create a new one
ListNode* LinkedList::findOrCreateNode(int wordLen) {
    ListNode* cur = head;
    ListNode* prev = nullptr;
    
    // Find position where wordLen should be inserted
    while (cur && wordLen > cur->len) {
        prev = cur;
        cur = cur->next;
    }
    
    // Found exact bucket
    if (cur && cur->len == wordLen) {
        return cur;
    }
    
    // Create new bucket
    ListNode* node = new ListNode(wordLen);
    
    // Insert at appropriate position
    if (!prev) {
        pushFront(node);  // Insert at beginning
    } else if (!cur) {
        pushBack(node);   // Insert at end
    } else {
        insertBefore(cur, node);  // Insert in middle
    }
    
    return node;
}