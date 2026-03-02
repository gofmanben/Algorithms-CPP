#include <iostream>
#include <fstream>
#include <sstream>
#include "board.h"
#include "queens.h"

using namespace std;

/*
int isEmpty(int* rows,int row) {
    int r = 0;
    while (rows[row] != rows[r] && abs(rows[row] - rows[r]) != (row - r)) {
        r++;
    }
    return ((row == r) ? 1 : 0);
}

void solve(int* rows, int row, int board_size) {
    for (rows[row] = 0; rows[row] < board_size; rows[row]++) {
        if (isEmpty(rows, row)) {
            if (row == (board_size - 1)) {
                std::cout << "New Solution:\n";
                for (int i = 0; i < board_size; i++)
                    std::cout << (i + 1) << " x " << (rows[i] + 1) << std::endl;;
                std::cout << std::endl;
            }
            else {
                solve(rows, row + 1, board_size);
            }
        }
    }
}
*/

int main(int argc, char **argv)
{
    if (argc < 3) // must provide two arguments as input
    {
        cerr << "Usage: ./main <INPUT FILE> <OUTPUT FILE>" << endl;
        return 1; // non-zero return means error
    }
    ifstream infile(argv[1]);  // open input file
    ofstream outfile(argv[2]); // open output file

    Board board;
    string line;

    // Each line describes a separate test case:
    // First integer: board size N
    // Remaining integers: pairs (row, col) for preplaced queens, 1-indexed in file.
    while (getline(infile, line))
    {
        // Skip empty lines.
        if (line.empty())
            continue;

        stringstream ss(line);
        Queens queens;

        int value, board_size = 0;
        bool valid = true;

        // Parse integers from the current line.
        while (ss >> value)
        {
            if (board_size == 0) {
                // First number is the board size.
                cout << "\n--- Board size: " << value << " ---"<< endl;
                board_size = value;
                board.setSize(board_size);

                //int rows[value] = {};
                //solve(rows, 0, value);
            } else {
                // Remaining numbers come as (row, col) pairs (1-indexed in input).
                int row = value - 1;
                int col;

                // Try to read the matching column value.
                if (ss >> value) {
                    col = value - 1;
                } else {
                    // If a row is provided without a column, this line is malformed.
                    cerr << "Missing column value" << endl;
                    continue;
                }

                // Validate row/col are within bounds.
                if (row < 0 || col < 0 || row >= board_size || col >= board_size) {
                    cerr << "Invalid row or column value: " << line << endl;
                    continue;
                } else {
                    // Store preplaced queen.
                    if (!queens.add(row, col))
                        valid = false;
                }
            }
        }

        // Print preplaced queens (for console visibility).
        queens.print();

        if (!valid) {
            outfile << "No solution\n";
            cout << "No solution" << endl;
            continue;
        }

        // Allocate solution array: solution[r] will hold the column for row r.
        int* solution = new int[board_size];

        // Solve with the given preplaced queens.
        if (board.solve(queens.getQueens(), solution)) {
            cout << "Found solution:" << endl;

            // Output solution as pairs (row, col), 1-indexed, separated by spaces.
            for (int r = 0; r < board_size; r++) {
                cout << r + 1 << ' ' << solution[r] + 1 << ' ';
                outfile << r + 1 << ' ' << solution[r] + 1 << ' ';
            }

            cout << endl;
            outfile << '\n' << flush;
        } else {
            // If no solution exists, write "No solution" for this test case.
            outfile << "No solution\n" << flush;
            cout << "No solution" << endl;
        }

        // Clean up heap allocations and per-line state.
        delete[] solution;
        queens.clear();
    }

    infile.close();
    outfile.close(); // close input and output streams
    return 0;
}