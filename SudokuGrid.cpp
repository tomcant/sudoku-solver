#include <fstream>
#include <cstdlib>
#include "SudokuGrid.h"

const char SudokuGrid::EMPTY = '0';
const int SudokuGrid::SIZE = 81;

void SudokuGrid::fromFile(const string filePath) {
  if (filePath.empty() || !filePath.data()) {
    throw "Invalid input file string.";
  }

  std::ifstream fileStream(filePath.c_str());

  if (!fileStream || !fileStream.is_open()) {
    throw "Input file could not be read.";
  }

  getline(fileStream, cells);

  if (cells.size() != SIZE) {
    throw "Input file content has incorrect length.";
  }

  for (size_t i = 0; i < SIZE; ++i) {
    if (!isdigit(cells[i])) {
      throw "Input file contains an invalid character.";
    }
  }
}

// Checks if the character `n' is in the box containing index `i'.
bool SudokuGrid::boxHasDigit(char n, int i) {
  static const int indexToBoxStart[] = {
    0, 0, 0,  3, 3, 3,  6, 6, 6,
    0, 0, 0,  3, 3, 3,  6, 6, 6,
    0, 0, 0,  3, 3, 3,  6, 6, 6,

    27,27,27, 30,30,30, 33,33,33,
    27,27,27, 30,30,30, 33,33,33,
    27,27,27, 30,30,30, 33,33,33,

    54,54,54, 57,57,57, 60,60,60,
    54,54,54, 57,57,57, 60,60,60,
    54,54,54, 57,57,57, 60,60,60
  };

  int
    start = indexToBoxStart[i],
    end = start + 21;

  for (int j = start; j < end; j += 9) {
    for (int k = 0; k < 3; ++k) {
      if (cells[j + k] == n) {
        return true;
      }
    }
  }

  return false;
}

// Checks if the character `n' is in the row containing index `i'.
bool SudokuGrid::rowHasDigit(char n, int i) {
  int start = i / 9 * 9,
    end = start + 9;

  for (int j = start; j < end; ++j) {
    if (cells[j] == n) {
      return true;
    }
  }

  return false;
}

// Checks if the character `n' is in the column containing index `i'.
bool SudokuGrid::columnHasDigit(char n, int i) {
  int start = i % 9,
    end = start + 73;

  for (int j = start; j < end; j += 9) {
    if (cells[j] == n) {
      return true;
    }
  }

  return false;
}

// Generates all possible cell values and stores them in a vector.
vector<string> SudokuGrid::generateMoves() {
  vector<string> moves;

  for (int i = 0; i < SIZE; ++i) {
    string cellOptions = "";

    if (EMPTY == cells[i]) {
      for (char j = '1'; j <= '9'; ++j) {
        if (!boxHasDigit(j, i) && !rowHasDigit(j, i) && !columnHasDigit(j, i)) {
          cellOptions += j;
        }
      }
    }

    moves.push_back(cellOptions);
  }

  return moves;
}

ostream& operator<<(ostream &stream, const SudokuGrid &grid) {
  static const int positions[] = {
    15, 16, 17,  19, 20, 21,  23, 24, 25,
    29, 30, 31,  33, 34, 35,  37, 38, 39,
    43, 44, 45,  47, 48, 49,  51, 52, 53,

    71, 72, 73,  75, 76, 77,  79, 80, 81,
    85, 86, 87,  89, 90, 91,  93, 94, 95,
    99, 100,101, 103,104,105, 107,108,109,

    127,128,129, 131,132,133, 135,136,137,
    141,142,143, 145,146,147, 149,150,151,
    155,156,157, 159,160,161, 163,164,165
  };

  char tmpl[] =
    "|-----------|\n"
    "|   |   |   |\n"
    "|   |   |   |\n"
    "|   |   |   |\n"
    "|-----------|\n"
    "|   |   |   |\n"
    "|   |   |   |\n"
    "|   |   |   |\n"
    "|-----------|\n"
    "|   |   |   |\n"
    "|   |   |   |\n"
    "|   |   |   |\n"
    "|-----------|"
  ;

  for (size_t cell = 0; cell < SudokuGrid::SIZE; ++cell) {
    if (!grid.isCellClear(cell)) {
      tmpl[positions[cell]] = grid.getCell(cell);
    }
  }

  return stream << tmpl;
}
