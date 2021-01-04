#include <fstream>
#include "grid.h"

namespace sudoku_solver {

const char Grid::EMPTY = '.';
const int Grid::SIZE = 81;

Grid Grid::FromFile(const string &filepath) {
  if (filepath.empty() || !filepath.data()) {
    throw "Invalid input file string.";
  }

  std::ifstream filestream(filepath.c_str());

  if (!filestream || !filestream.is_open()) {
    throw "Input file could not be read.";
  }

  string cells, chunk;

  while (filestream >> chunk) {
    cells += chunk;
  }

  if (cells.size() != SIZE) {
    throw "Input file content has incorrect length.";
  }

  for (size_t i = 0; i < SIZE; ++i) {
    if (!isdigit(cells[i]) && EMPTY != cells[i]) {
      throw "Input file contains an invalid character.";
    }
  }

  return Grid(cells);
}

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

ostream& operator<<(ostream &stream, const Grid &grid) {
  static const int positions[] = {
    15,  16,  17,   19,  20,  21,   23,  24,  25,
    29,  30,  31,   33,  34,  35,   37,  38,  39,
    43,  44,  45,   47,  48,  49,   51,  52,  53,

    71,  72,  73,   75,  76,  77,   79,  80,  81,
    85,  86,  87,   89,  90,  91,   93,  94,  95,
    99,  100, 101,  103, 104, 105,  107, 108, 109,

    127, 128, 129,  131, 132, 133,  135, 136, 137,
    141, 142, 143,  145, 146, 147,  149, 150, 151,
    155, 156, 157,  159, 160, 161,  163, 164, 165
  };

  char grid_template[] =
    "|-----------|\n"
    "|...|...|...|\n"
    "|...|...|...|\n"
    "|...|...|...|\n"
    "|-----------|\n"
    "|...|...|...|\n"
    "|...|...|...|\n"
    "|...|...|...|\n"
    "|-----------|\n"
    "|...|...|...|\n"
    "|...|...|...|\n"
    "|...|...|...|\n"
    "|-----------|";

  for (size_t cell = 0; cell < Grid::SIZE; ++cell) {
    if (!grid.IsCellClear(cell)) {
      grid_template[positions[cell]] = grid.GetCell(cell);
    }
  }

  return stream << grid_template;
}

}  // namespace sudoku_solver
