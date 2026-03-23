// Filename: main.cpp
// 
// Benjamin Gofman, Mar 2026

#include <iostream>
#include <fstream>
#include <sstream>

#include "graph.h"

using namespace std;

// Main program entry point
int main(int argc, char **argv)
{
    if (argc < 3) // must provide two arguments as infile
    {
        cerr << "Usage: ./main <input_file> <output_file>" << endl;
        return 1; // non-zero return means error
    }
    
    ifstream infile(argv[1]);  // open input file
    ofstream outfile(argv[2]); // open output file

    // Create the graph and load all movie/actor data into it.
    Graph g;
    g.loadMovies("cleaned_movielist.txt");

    string line;

    // Read each actor-pair query from the input file.
    while (getline(infile, line))
    {
        // Ignore blank lines.
        if (line.empty())
        {
            continue;
        }

        istringstream iss(line);
        string actor1, actor2;
        iss >> actor1 >> actor2;

        // Find the shortest path between the two actors.
        string result = g.shortestPath(actor1, actor2);

        // Print either the path or a message if no valid path exists.
        if (result.empty())
        {
            outfile << "Not present\n";
        }
        else
        {
            outfile << result << '\n';
        }
    }

    infile.close(); outfile.close(); //close input and output streams
    return 0;
}
