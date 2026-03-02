#ifndef QUEENS_H
#define QUEENS_H

#include <map>

// Queens is a simple container for preplaced queen positions.
// Stores queens as (row -> column), 0-indexed.
class Queens{
	private:
		std::map <int,int> queens;

	public:
		// Print current preplaced queens to stdout (1-indexed for display).
		void print();

		// Remove all stored queens.
		void clear();

		// Add/overwrite a queen placement at (row, col).
		bool add(int row, int col);

		// Access the underlying map of (row -> col).
		std::map<int,int>& getQueens();
};

#endif
