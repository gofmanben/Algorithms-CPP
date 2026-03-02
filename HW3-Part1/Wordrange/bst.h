// Filename: bst.h
// 
// Header file for the class BST that represents a binary search tree
// 
// Benjamin Gofman, Feb 2026

#ifndef BST_H
#define BST_H

#include <string>

using namespace std;

// node struct to hold data
class Node
{
public:
    string key;
    Node *left, *right, *parent;

    Node() : Node("") {} // default contractor delegates to the other constructor

    Node(const string& val) // constructor that sets key to val
    {
        key = val;
        left = right = parent = NULL; // setting everything to NULL
    }
};

class BST 
{
private:
    Node *root; // Stores root of tree
public:
    BST(); // Default constructor sets root to null
    void insert(const string&); // insert string into list 
    int rangeCount(const string&, const string&);  // Count nodes between two strings
    int rangeCount(Node* node, const string& low, const string& high); // Helper recursive function for rangeCount
    void deleteBST(); // deletes every node to prevent memory leaks, and frees memory
    void deleteBST(Node* start); // deletes every Node in subtree rooted at startto prevent memory leaks.
};

#endif