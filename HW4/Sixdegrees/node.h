// Filename: node.h
// 
// Benjamin Gofman, Mar 2026

#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

using namespace std;

// Node type identifier used to distinguish between movie nodes and actor nodes.
// The graph contains both types of nodes, so this enum allows the program to
// check what kind of node it is currently working with (for example when
// reconstructing the path we only keep ACTOR nodes).
enum NodeType
{
    MOVIE,
    ACTOR
};

class Node
{
private:
    NodeType type;
    string name;
    vector<Node *> neighbors;

public:
    // Creates a node with a type (MOVIE or ACTOR) and a name.
    Node(NodeType type, const string &name);

    // Adds a bidirectional graph connection to another node.
    void add(Node *node);

    // Returns the name stored in this node.
    string getName() const;

    // Returns true if this node matches the given type.
    bool is(NodeType type) const;

    // Returns all neighboring nodes connected to this node.
    const vector<Node *> &getNeighbors() const;
};

#endif
