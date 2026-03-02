// Filename: bst.cpp
// 
// Contains the class BST that represents a binary search tree. This contains some basic operations, such as insert, delete, find, and printing in various traversal orders
// 
// Benjamin Gofman, Feb 2026

#include "bst.h"
#include <stack>

using namespace std;

// Default constructor sets head and tail to null
BST :: BST()
{
	root = NULL;
}

// Insert(string val): Inserts the string val into tree, at the head of the list. Note that there may be multiple copies of val in the list. Just calls the recursive function
// Input: string to insert into the BST
// Output: Void, just inserts new Node
void BST :: insert(const string& val)
{
    if (root == NULL) {
        root = new Node(val); // create a new Node with the value val
        return;
    }
    
    Node* cur = root;
    Node* parent = NULL;

    while(cur) {
        parent = cur;
        if (val == cur->key) return;
        if (val < cur->key) cur = cur->left;
        else cur = cur->right;
    }

    Node* node = new Node(val);
    node->parent = parent;
    if (val < parent->key) parent->left = node;
    else parent->right = node;
}

// Deletes every Node to prevent memory leaks.
// Input: None
// Output: Void, just deletes every Node of the list
void BST :: deleteBST()
{
    deleteBST(root);
}

// Deletes every Node in subtree rooted at startto prevent memory leaks.
// Input: Node* start
// Output: Void, just deletes every Node of the list
void BST :: deleteBST(Node* start)
{
    if(start == NULL) // tree is already empty
        return; 
    deleteBST(start->left); // delete left subtree
    deleteBST(start->right); // delete right subtree
    delete(start); // delete node itself
}

// Count nodes with keys between low and high (inclusive)
int BST :: rangeCount(const string& low, const string& high) {
    return rangeCount(root, low, high);
}

// Helper recursive function for rangeCount
int BST :: rangeCount(Node* node, const  string& low, const string& high) {
    if (node == NULL) {
        return 0;
    }
    
    int count = 0;
    stack<Node*> stk;
    stk.push(node);
    
    while (!stk.empty()) {
        Node* cur = stk.top();
        stk.pop();
        
        Node* left = cur->left;
        Node* right = cur->right;
        // Check if current node is in range
        if (cur->key < low) 
        {
            // everything in left subtree is <= cur->key < low, so ignore left
            left = NULL;  // prune left
        }
        else if (cur->key > high) 
        {
            // everything in right subtree is >= cur->key > high, so ignore right
            right = NULL; // prune right
        }
        else 
        {
            // cur->key is inside [low, high]
            count++;
        }
        if (left) stk.push(left);
        if (right) stk.push(right);
    }
    
    return count;
}