#include "board.h"
#include <cmath>
#include <iostream>

bool Board ::isEmpty(int* rows, int row, int col) {
    // Check all previously filled rows for:
    // 1) same column conflict, or
    // 2) diagonal conflict (difference in columns equals difference in rows)
    for (int r = 0; r < row; r++) {
        if (rows[r] == col || abs(rows[r] - col) == (row - r)) {
            return false;
        }
    }
    return true;
}

bool Board::tryPlaceAndRecurse(int* rows, int row, int col, std::map<int,int>& queens) {
    // Only proceed if the preplaced queen does not conflict with earlier rows.
    if (!isEmpty(rows, row, col)) return false;

    rows[row] = col;

    // Recurse to next row.
    if (findSolution(rows, row + 1, queens)) {
        std::cout << row + 1 << " x " << col + 1 << std::endl;
        return true;
    }

    rows[row] = -1;

    // If preplaced doesn't work, no alternative positions exist for this row.
    return false;
}

bool Board :: findSolution(int* rows, int row, std::map<int, int>& queens) {
    // Base case: all rows processed => valid placement found.
    if (row == board_size) {
        return true;
    }

    // If this row has a preplaced queen, only try that column.
    if (queens.count(row) > 0) {
        return tryPlaceAndRecurse(rows, row, queens[row], queens);
    }

    // Otherwise, try every column in this row.
    for (int col = 0; col < board_size; col++) {
        if (tryPlaceAndRecurse(rows, row, col, queens)) {
            return true;
        }
    }

    // No column worked for this row.
    return false;
}

bool Board :: solve(std::map<int, int>& queens, int* solution) {
    // rows[r] = column index for row r, or -1 if not assigned yet.
    int* rows = new int[board_size];

    // Initialize rows to -1 (no queen).
    for (int i = 0; i < board_size; i++) {
        rows[i] = -1;
    }

    // Load preplaced queens into rows[] and validate bounds.
    for (std::pair<const int, int>& pair : queens) {
        int row = pair.first;
        int col = pair.second;

        // Reject invalid preplacements immediately.
        if (row < 0 || row >= board_size || col < 0 || col >= board_size) {
            delete[] rows;
            return false;
        }

        rows[row] = col;
    }

    // Run backtracking from row 0.
    bool found = findSolution(rows, 0, queens);

    // If solved, copy the result into the provided solution array.
    if (found) {
        std::copy(rows, rows + board_size, solution);
    }

    delete[] rows;
    return found;
}
