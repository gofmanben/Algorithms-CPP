// Filename: main.cpp
// Benjamin Gofman, January 2025

#include "linkedlist.h"
#include <iostream>
#include <fstream>

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
    
    // Build data structure from Shakespeare text
    ifstream textFile("shakespeare-cleaned.txt");
    if (!textFile) {
        cerr << "Error: Cannot open shakespeare-cleaned.txt\n";
        return 1;
    }
    
    LinkedList list;  // Main data structure
    string word;      // Current word being processed
    
    // Read all words from Shakespeare text and insert into data structure
    while (textFile >> word) {
        if (!word.empty()) {
            ListNode* node = list.findOrCreateNode(word.length());
            node->children.insertAndSort(word);
        }
    }
    textFile.close();

    // Print to console with limit (debug mode)
    if (argc == 4) { // debug keyword (any 4th argument such as "debug" or "print")
        ListNode* cur = list.getHead();
        while (cur) {
            WordNode* node = list.getHeadNode(cur);
            cout << "***** List (word length/size) " << cur->len << '/' <<  cur->children.getSize() << " *****\n";
            int count = 0;
            while (node) {
                cout << node->word << " : " << node->freq << "\n";
                node = node->next;
                if (count++ > 20) break; // limit for console
            }
            cout << endl;
            cur = cur->next;
        }
    }
    
    if (!infile || !outfile) {
        cerr << "Error: Cannot open input/output files\n";
        return 1;
    }
    
    int wordLength, rank;
    while (infile >> wordLength >> rank) {
        string result = "-";
        
        // Find the bucket for this word length
        ListNode* cur = list.getHead();
        while (cur && cur->len < wordLength) {
            cur = cur->next;
        }
        
        // If bucket exists and rank is valid, find the word
        if (cur && cur->len == wordLength && rank >= 0) {
            WordNode* wordNode = list.getHeadNode(cur);
            for (int i = 0; i < rank && wordNode; i++) {
                wordNode = wordNode->next;
            }
            if (wordNode) {
                result = wordNode->word;
            }
        }
        
        outfile << result << "\n";
    }

    infile.close(); outfile.close(); //close input and output streams
    return 0;
}