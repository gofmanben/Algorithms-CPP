// Filename: graph.h
// 
// Benjamin Gofman, Mar 2026

#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <map>

#include "node.h"

using namespace std;

class Graph
{
private:
    map<string, Node *> actors;
    vector<Node *> allNodes;

    // Stores the order each movie appeared in cleaned_movielist.txt.
    map<string, int> movieOrder;
    int nextMovieOrder;

    // Returns the earliest shared movie between two actors.
    string earliestMovie(Node *actor1, Node *actor2) const;

public:
    // Creates an empty graph.
    Graph();

    // Frees all dynamically allocated nodes in the graph.
    ~Graph();

    // Reads the movie file and builds the graph from it.
    void loadMovies(const string &filename);

    // Adds one movie and all of its actors to the graph.
    void addMovie(const string &movieName, const vector<string> &actorNames);

    // Returns the shortest path string between two actors.
    string shortestPath(const string &actorName1, const string &actorName2);
};

#endif
