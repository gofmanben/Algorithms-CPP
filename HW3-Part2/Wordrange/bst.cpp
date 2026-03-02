// Filename: bst.cpp
// 
// Contains the class BST that represents a binary search tree. This contains some basic operations, such as insert, delete, find, and printing in various traversal orders
// 
// Benjamin Gofman, Feb 2026

#include "bst.h"
#include <cstdlib>
#include <iostream>
#include <vector> 
#include <algorithm>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

// Default constructor sets head and tail to null
BST :: BST()
{
	root = NULL;
}

// Insert(string val): Inserts the string val into tree, at the head of the list. Note that there may be multiple copies of val in the list. Just calls the recursive function
// Input: string to insert into the AVL tree
// Output: Void, just inserts new Node
void BST :: insert(const string& val)
{
    // AVL implementation - use recursive AVL insert
    root = insertAVL(root, val);
    if (root != NULL) {
        root->parent = NULL; // Ensure root has no parent
    }
}

// ==================== AVL INSERT ====================

// insertAVL(Node* node, string key): Recursive AVL insertion
Node* BST :: insertAVL(Node* node, const string& key) {
    // REQUIREMENT: Check for duplicates - Each word should only appear once in the data structure.
    // 1. Perform standard BST insert
    if (node == NULL) {
        return new Node(key);
    }
    
    // Find position to insert (no duplicates allowed)
    if (key < node->key) {
        node->left = insertAVL(node->left, key);
        node->left->parent = node;
    } else if (key > node->key) {
        node->right = insertAVL(node->right, key);
        node->right->parent = node;
    } else {
        // Duplicate found - do not insert
        return node;
    }
    
    // 2. Update height and size of current node
    updateNode(node);

    // return node; // Return unbalanced tree

    // Perform rotations if unbalanced (4 cases)
    
    // 3. Get balance factor
    int balance = height(node->left) - height(node->right);
    
    // Left Left Case
    if (balance > 1 && key < node->left->key) {
        return rightRotate(node);
    }
    
    // Right Right Case
    if (balance < -1 && key > node->right->key) {
        return leftRotate(node);
    }
    
    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    
    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    
    return node; // Return balanced tree
}

// ==================== AVL HELPER FUNCTIONS ====================

// height(Node* node): Returns height of node (0 for NULL)
int BST :: height(Node* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

// getSize(Node* node): Returns size of subtree (0 for NULL)
int BST :: getSize(Node* node) {
    if (node == NULL) {
        return 0;
    }
    return node->size;
}

// updateNode(Node* node): Updates height and size of node
void BST :: updateNode(Node* node) {
    if (node == NULL) {
        return;
    }
    node->height = 1 + max(height(node->left), height(node->right));
    node->size = 1 + getSize(node->left) + getSize(node->right);
}

// ==================== AVL ROTATIONS ====================

// rightRotate(Node* y): Performs right rotation
Node* BST :: rightRotate(Node* y) {
    Node* x = y->left;
    Node* temp = x->right;
    
    // Perform rotation
    x->right = y;
    y->left = temp;
    
    // Update parents
    x->parent = y->parent;
    y->parent = x;
    if (temp != NULL) {
        temp->parent = y;
    }
    
    // Update heights and sizes
    updateNode(y);
    updateNode(x);
    
    return x;
}

// leftRotate(Node* x): Performs left rotation
Node* BST :: leftRotate(Node* x) {
    Node* y = x->right;
    Node* temp = y->left;
    
    // Perform rotation
    y->left = x;
    x->right = temp;
    
    // Update parents
    y->parent = x->parent;
    x->parent = y;
    if (temp != NULL) {
        temp->parent = x;
    }
    
    // Update heights and sizes
    updateNode(x);
    updateNode(y);
    
    return y;
}

// ==================== AVL RANGE QUERY ====================

// countLess(Node* node, string val, bool inclusive):
// If inclusive == false  → counts keys < val
// If inclusive == true   → counts keys <= val
int BST :: countLess(Node* node, const string& val, bool inclusive) {
    if (node == NULL) {
        return 0;
    }

    if ((inclusive && val < node->key) ||
        (!inclusive && val <= node->key)) {
        return countLess(node->left, val, inclusive);
    } else {
        return getSize(node->left) + 1 +
               countLess(node->right, val, inclusive);
    }
}

// Count nodes with keys between low and high (inclusive)
int BST :: rangeCount(const string& low, const string& high) {
    int countHigh = countLess(root, high, true);   // <= high
    int countLow  = countLess(root, low, false);   // < low
    return countHigh - countLow;
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
