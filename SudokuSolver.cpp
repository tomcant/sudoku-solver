#include <cstdlib>
#include "SudokuSolver.h"

void SudokuSolver::solve(SudokuGrid grid) {
  if (grid.isComplete()) {
    std::cout << grid;
    std::exit(0);
  }

  // Make as many forced moves as possible.
  bool forcedMoveAvailable;
  vector<string> moves;

  do {
    forcedMoveAvailable = false;
    moves = grid.generateMoves();

    for (size_t cell = 0; cell < 81; ++cell) {
      if (moves[cell].size() == 1) {
        forcedMoveAvailable = true;
        grid.setCell(cell, moves[cell][0]);
        break;
      }
    }
  } while(forcedMoveAvailable);

  // If there exists a cell with no possible moves then the sudoku is not
  // solvable from this point.
  for (size_t cell = 0; cell < 81; ++cell) {
    if (grid.isCellClear(cell) && moves[cell].size() == 0) {
      return;
    }
  }

  if (grid.isComplete()) {
    std::cout << grid;
    std::exit(0);
  }

  // Find the cell with the fewest possibilities.
  size_t min = 9,
    minCell = 0;

  for (size_t cell = 0; cell < 81; ++cell) {
    size_t size = moves[cell].size();

    if (size > 0 && size < min) {
      min = size;
      minCell = cell;
    }
  }

  // Search the sub-tree of possibilities.
  for (size_t i = 0; i < min; ++i){
    grid.setCell(minCell, moves[minCell][i]);
    solve(grid);
    grid.clearCell(minCell);
  }
}
