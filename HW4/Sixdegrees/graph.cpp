// Filename: graph.cpp
// 
// Benjamin Gofman, Mar 2026

#include <queue>
#include <fstream>
#include <sstream>
#include <algorithm> // reverse

#include "graph.h"

using namespace std;

/*
 * Creates an empty graph.
 *
 * nextMovieOrder tracks the input order of movies in the dataset so we can
 * later choose the earliest shared movie between two actors.
 */
Graph::Graph()
{
    nextMovieOrder = 0;
}

/*
 * Frees every node created for the graph.
 *
 * Both movie nodes and actor nodes are stored in allNodes, so deleting that
 * list cleans up the entire graph.
 */
Graph::~Graph()
{
    for (Node *node : allNodes)
    {
        delete node;
    }
}

/*
 * Reads the movie dataset file and builds the graph.
 *
 * Expected line format:
 *   MovieName Actor1 Actor2 Actor3 ...
 *
 * The first token is the movie name. Every remaining token is an actor.
 * Each parsed line is passed to addMovie().
 */
void Graph::loadMovies(const string &filename)
{
    ifstream datasetFile(filename);
    string line;

    // Read the dataset one line at a time.
    while (getline(datasetFile, line))
    {
        // Ignore blank lines so parsing stays clean.
        if (line.empty())
        {
            continue;
        }

        istringstream iss(line);

        // First token is the movie title.
        string movie;
        iss >> movie;

        // Remaining tokens are actor names.
        vector<string> actors;
        string actor;
        while (iss >> actor)
        {
            actors.push_back(actor);
        }

        // Insert this movie and all actor neighbors into the graph.
        addMovie(movie, actors);
    }
}

/*
 * Adds a movie node and connects it to all actors in its cast.
 *
 * Graph shape:
 *   Actor <-> Movie <-> Actor
 *
 * If an actor does not already exist, a new actor node is created.
 * The movie node is always newly created for this dataset entry.
 *
 * @param movieName the movie title from the dataset
 * @param actorNames all actor names listed after the movie title
 */
void Graph::addMovie(const string &movieName, const vector<string> &actorNames)
{
    // Create the movie node and store it for later cleanup.
    Node *movieNode = new Node(MOVIE, movieName);
    allNodes.push_back(movieNode);

    // Record the movie's order in the input file.
    movieOrder[movieName] = nextMovieOrder++;

    // Connect this movie to every actor listed for it.
    for(const string &actorName : actorNames)
    {
        Node *actorNode = actors[actorName];

        // Create the actor node only the first time we see that actor.
        if (actorNode == NULL)
        {
            actorNode = new Node(ACTOR, actorName);
            actors[actorName] = actorNode;
            allNodes.push_back(actorNode);
        }

        // Build the bidirectional edges between actor and movie.
        actorNode->add(movieNode);
        movieNode->add(actorNode);
    }
}

/*
 * Returns the earliest movie shared by two actors.
 *
 * We search all movies connected to actor1 and check whether actor2 appears in
 * the same cast list. If multiple shared movies exist, we choose the one that
 * appeared first in the dataset.
 */
string Graph::earliestMovie(Node *actor1, Node *actor2) const
{
    string bestMovie = "";
    int bestRank = -1;

    const vector<Node *> &movies = actor1->getNeighbors();

    for (Node *movie : movies)
    {
        // Safety check: actor nodes should connect to movies, but keep this
        // guard in case the graph changes later.
        if (!movie->is(MOVIE))
        {
            continue;
        }

        const vector<Node *> &actors = movie->getNeighbors();
        bool shared = false;

        // Check whether actor2 is also connected to this movie.
        for (Node *actor : actors)
        {
            if (actor == actor2)
            {
                shared = true;
                break;
            }
        }

        if (!shared)
        {
            continue;
        }

        // Get the movie's order in the dataset so we can choose the earliest
        // shared movie if two actors appear together in multiple movies.
        int rank = movieOrder.at(movie->getName());

        // Keep the earliest movie by dataset order.
        if (bestMovie.empty() || rank < bestRank)
        {
            bestMovie = movie->getName();
            bestRank = rank;
        }
    }

    return bestMovie;
}

/*
 * Finds the shortest actor-to-actor path using breadth-first search (BFS).
 *
 * The BFS runs on the graph exactly as stored: actor nodes connect to movie
 * nodes, and movie nodes connect to actor nodes. After BFS reconstructs the
 * raw path, we keep only actor nodes in the final printed answer and label each
 * actor-to-actor step with their earliest shared movie.
 *
 * @param actorName1 starting actor
 * @param actorName2 ending actor
 * @return formatted path string, or "" if no path exists
 */
string Graph::shortestPath(const string &actorName1, const string &actorName2)
{
    Node *actor1 = actors[actorName1];
    Node *actor2 = actors[actorName2];

    // If either actor does not exist in the graph, no path can be formed.
    if (!actor1 || !actor2)
    {
        return "";
    }

    // Special case: same actor, so the path is just that name.
    if (actor1 == actor2)
    {
        return actorName1;
    }

    map<Node *, Node *> parent;
    map<Node *, bool> visited;
    queue<Node *> q;

    // Start BFS from actor1.
    q.push(actor1); // 1. Push starting actor
    visited[actor1] = true;
    parent[actor1] = NULL;

    while (!q.empty())
    {
        Node *cur = q.front(); // 2. Explore neighbors
        q.pop();

        // Explore all neighboring nodes reachable in one step.
        const vector<Node *> &neighbors = cur->getNeighbors();

        // Edge case / tie-break:
        // multiple shortest paths can exist with the same length. The expected
        // outputs are matched by exploring each node's adjacency list in reverse
        // insertion order, so the most recently added neighbors are considered
        // first during BFS.
        int size = neighbors.size();
        for (int i = size - 1; i >= 0; i--)
        {
            Node *next = neighbors[i];

            // Edge case: mark a node visited when it is ENQUEUED, not when it is
            // popped. Otherwise, the same node can be pushed multiple times and
            // its parent can be overwritten by a later equal-length path, which
            // changes valid existing outputs and can pick the wrong path.
            if (!visited[next])
            {
                q.push(next); // 3. Add unvisited neighbors
                visited[next] = true;
                parent[next] = cur;
            }
        }
    }

    // If actor2 was never reached, there is no connection.
    if (!visited[actor2])
    {
        return "";
    }

    // Reconstruct the full raw path from actor2 back to actor1.
    vector<Node *> rawPath;
    for (Node *cur = actor2; cur != NULL; cur = parent[cur])
    {
        rawPath.push_back(cur);
    }
    reverse(rawPath.begin(), rawPath.end()); // the path we reconstruct from the parent pointers is built backwards.

    // Keep only actor nodes for the printed output.
    vector<Node *> actorPath;
    for (Node* node : rawPath)
    {
        if (node->is(ACTOR))
        {
            actorPath.push_back(node);
        }
    }

    if (actorPath.empty())
    {
        return "";
    }

    // Start the answer with the first actor.
    string path = actorPath[0]->getName();

    // Add each next actor with the earliest movie shared by the pair.
    int size = actorPath.size();
    for (int i = 0; i < size - 1; i++)
    {
        Node *a = actorPath[i];
        Node *b = actorPath[i + 1];

        string movie = earliestMovie(a, b);
        if (movie.empty())
        {
            return "";
        }

        path += " -(" + movie + ")- " + b->getName();
    }

    return path;
}