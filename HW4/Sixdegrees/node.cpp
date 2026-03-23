// Filename: node.cpp
// 
// Benjamin Gofman, Mar 2026

#include "node.h"

// Creates a node and stores its type and name.
Node::Node(NodeType type, const string &name)
{
    this->type = type;
    this->name = name;
}

// Adds one neighboring node to this node's adjacency list.
void Node::add(Node *node)
{
    neighbors.push_back(node);
}

// Returns the node's name.
string Node::getName() const
{
    return name;
}

// Returns true when the node type matches the requested type.
bool Node::is(NodeType type) const
{
    return this->type == type;
}

// Returns the list of neighboring nodes.
const vector<Node *> &Node::getNeighbors() const
{
    return neighbors;
}
