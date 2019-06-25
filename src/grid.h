#ifndef SRC_GRID_H_
#define SRC_GRID_H_

#include <iostream>
#include <string>
#include <vector>

using std::ostream;
using std::string;
using std::vector;

namespace sudoku_solver {

class Grid {
  string cells_;

 public:
  static const char EMPTY;
  static const int SIZE;

  Grid() {
    cells_ = string(SIZE, EMPTY);
  }

  Grid &SetCell(int cell, char value) {
    cells_[cell] = value;
    return *this;
  }

  Grid &ClearCell(int cell) {
    SetCell(cell, EMPTY);
    return *this;
  }

  char GetCell(int cell) const {
    return cells_[cell];
  }

  bool IsCellClear(int cell) const {
    return GetCell(cell) == EMPTY;
  }

  bool IsComplete() const {
    return cells_.find(EMPTY) == string::npos;
  }

  void FromFile(const string);
  vector<string> GenerateMoves();

  bool BoxHasDigit(char, int);
  bool RowHasDigit(char, int);
  bool ColumnHasDigit(char, int);
};

ostream& operator<<(ostream &stream, const Grid &grid);

}  // namespace sudoku_solver

#endif  // SRC_GRID_H_
