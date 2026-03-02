// Filename: main.cpp
//
// This is the main wrapper for the BST class.
// 
// After running make, the usage is:
//     ./main <INPUT_FILE> <OUTPUT_FILE>
// 
//Benjamin Gofman, Feb 2026

#include <iostream>
#include "bst.h"
#include <fstream>
#include <sstream>
#include <cstring>
using namespace std;


int main(int argc, char** argv)
{
    if (argc < 3) // must provide two arguments as input
    {
        throw std::invalid_argument("Usage: ./hello <INPUT FILE> <OUTPUT FILE>"); // throw error
    }

    ifstream input; // stream for input file
    ofstream output; // stream for output file

    input.open(argv[1]); // open input file
    output.open(argv[2]); // open output file

    string valstr, valstr2, op; // for using with strtok, strtol

    BST myBST; // initializing the linked list
  
    while(input >> op) // get next line of input, store as repeat
    {
        input >> valstr;
        if(op == "i") // insert into list
        {
            // cout << "Insert " << valstr << endl;
            myBST.insert(valstr);
        }
        else if(op == "r")
        {
            input >> valstr2;
            // cout << "Range " << valstr << " " << valstr2 << endl;
            output << myBST.rangeCount(valstr, valstr2) << "\n";
        }
     }
     myBST.deleteBST(); // delete the tree from memory

     input.close();
     output.close();
}
