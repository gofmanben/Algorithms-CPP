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
    int height;    // AVL: Height of node
    int size;      // AVL: Size of subtree (for O(log n) range queries)

    Node() : Node("") {} // default constructor delegates to the other constructor

    Node(const string& val) // constructor that sets key to val
    {
        key = val;
        left = right = parent = NULL; // setting everything to NULL
        height = 1;  // AVL: Leaf node has height 1
        size = 1;    // AVL: Single node has size 1
    }
};

class BST 
{
private:
    Node *root; // Stores root of tree
    
    // AVL Helper Functions
    int height(Node* node);
    int getSize(Node* node);
    int countLess(Node* node, const string& val, bool inclusive);
    void updateNode(Node* node);
    
    // AVL Rotations
    Node* rightRotate(Node* y);
    Node* leftRotate(Node* x);
    
    // AVL Insert
    Node* insertAVL(Node* node, const string& key);
public:
    BST(); // Default constructor sets root to null
    void insert(const string&); // insert string into list 
    int rangeCount(const string&, const string&);  // Count nodes between two strings
    void deleteBST(); // deletes every node to prevent memory leaks, and frees memory
    void deleteBST(Node* start); // deletes every Node in subtree rooted at startto prevent memory leaks.
};

#endif