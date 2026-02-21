#include <iostream>
#include "queens.h"

void Queens :: print() {
    // Print each stored (row, col) pair using 1-based indexing for readability.
    for (const std::pair<const int, int>& p : queens) {
        std::cout << "Row: " << p.first + 1 << ", Col: " << p.second + 1 << std::endl;
    }
}

void Queens :: clear() {
	// Clear all stored placements.
	queens.clear();
}

bool Queens :: add(int row, int col) {
    if (queens.count(row) > 0) {
        // already a queen in this row -> invalid test case
        return false;
    }
    // Insert or overwrite the queen at the given row.
    queens[row] = col;
    return true;
}

std::map<int,int>& Queens :: getQueens() {
    // Return reference so caller can pass to solver (and potentially modify).
    return queens;
}