#ifndef _SUDOKU_GRID_H_
#define _SUDOKU_GRID_H_

#include <iostream>
#include <string>
#include <vector>

using std::ostream;
using std::string;
using std::vector;

class SudokuGrid {
  string cells;

public:
  static const char EMPTY;
  static const int SIZE;

  SudokuGrid() {
    cells = string(SIZE, EMPTY);
  }

  SudokuGrid &setCell(int cell, char value) {
    cells[cell] = value;
    return *this;
  }

  SudokuGrid &clearCell(int cell) {
    setCell(cell, EMPTY);
    return *this;
  }

  char getCell(int cell) const {
    return cells[cell];
  }

  bool isCellClear(int cell) const {
    return getCell(cell) == EMPTY;
  }

  bool isComplete() const {
    return cells.find(EMPTY) == string::npos;
  }

  void fromFile(const string);
  vector<string> generateMoves();

  bool boxHasDigit(char, int);
  bool rowHasDigit(char, int);
  bool columnHasDigit(char, int);
};

ostream& operator<<(ostream &stream, const SudokuGrid &grid);

#endif
