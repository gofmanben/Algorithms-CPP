#ifndef BOARD_H
#define BOARD_H

#include <map>

// Board encapsulates the N-Queens solver logic.
// - board_size is the dimension N of the NxN chessboard.
// - solve(...) uses backtracking to find a valid placement (or report none).
class Board
{
    private:
        int board_size;

        // Checks if placing a queen at (row, col) conflicts with any earlier rows [0..row-1].
        bool isEmpty(int* rows, int row, int col);

        // Recursive backtracking:
        bool findSolution(int* rows, int row, std::map<int, int>& queens);

        // Attempts to place a queen at (row, col) and recursively solve the rest
        bool tryPlaceAndRecurse(int* rows, int row, int col, std::map<int,int>& queens);

    public:
        // Sets the board size N.
        void setSize(int size) { board_size = size; }

        // Attempts to solve the N-Queens problem with optional queens queens.
        bool solve(std::map<int, int>& queens, int* solution);
};

#endif
