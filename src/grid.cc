#include "grid.h"

namespace sudoku_solver {

const char Grid::EMPTY = '.';
const int Grid::SIZE = 81;

bool Grid::BoxHasDigit(char n, int i) {
  static const int index_to_box_start[] = {
    0,  0,  0,  3,  3,  3,  6,  6,  6,
    0,  0,  0,  3,  3,  3,  6,  6,  6,
    0,  0,  0,  3,  3,  3,  6,  6,  6,

    27, 27, 27, 30, 30, 30, 33, 33, 33,
    27, 27, 27, 30, 30, 30, 33, 33, 33,
    27, 27, 27, 30, 30, 30, 33, 33, 33,

    54, 54, 54, 57, 57, 57, 60, 60, 60,
    54, 54, 54, 57, 57, 57, 60, 60, 60,
    54, 54, 54, 57, 57, 57, 60, 60, 60
  };

  int start = index_to_box_start[i],
    end = start + 21;

  for (int j = start; j < end; j += 9) {
    for (int k = 0; k < 3; ++k) {
      if (cells_[j + k] == n) {
        return true;
      }
    }
  }

  return false;
}

bool Grid::RowHasDigit(char n, int i) {
  int start = i - i % 9,
    end = start + 9;

  for (int j = start; j < end; ++j) {
    if (cells_[j] == n) {
      return true;
    }
  }

  return false;
}

bool Grid::ColumnHasDigit(char n, int i) {
  int start = i % 9,
    end = start + 73;

  for (int j = start; j < end; j += 9) {
    if (cells_[j] == n) {
      return true;
    }
  }

  return false;
}

vector<string> Grid::GenerateMoves() {
  vector<string> moves;

  for (int i = 0; i < SIZE; ++i) {
    string cell_options = "";

    if (EMPTY == cells_[i]) {
      for (char j = '1'; j <= '9'; ++j) {
        if (!BoxHasDigit(j, i) && !RowHasDigit(j, i) && !ColumnHasDigit(j, i)) {
          cell_options += j;
        }
      }
    }

    moves.push_back(cell_options);
  }

  return moves;
}

}  // namespace sudoku_solver
