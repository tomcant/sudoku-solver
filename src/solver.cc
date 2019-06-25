#include <cstdlib>
#include <string>
#include <vector>
#include "solver.h"

namespace sudoku_solver {

void Solver::Solve(Grid grid) {
  if (grid.IsComplete()) {
    std::cout << grid;
    std::exit(0);
  }

  // Make as many forced moves as possible.
  bool forced_move_available;
  vector<string> moves;

  do {
    forced_move_available = false;
    moves = grid.GenerateMoves();

    for (size_t cell = 0; cell < 81; ++cell) {
      if (moves[cell].size() == 1) {
        forced_move_available = true;
        grid.SetCell(cell, moves[cell][0]);
        break;
      }
    }
  } while (forced_move_available);

  // If there exists a cell with no possible moves then the sudoku is not
  // solvable from this point.
  for (size_t cell = 0; cell < 81; ++cell) {
    if (grid.IsCellClear(cell) && moves[cell].size() == 0) {
      return;
    }
  }

  if (grid.IsComplete()) {
    std::cout << grid;
    std::exit(0);
  }

  // Find the cell with the fewest possibilities.
  size_t min = 9,
    min_cell = 0;

  for (size_t cell = 0; cell < 81; ++cell) {
    size_t size = moves[cell].size();

    if (size > 0 && size < min) {
      min = size;
      min_cell = cell;
    }
  }

  // Search the sub-tree of possibilities.
  for (size_t i = 0; i < min; ++i) {
    grid.SetCell(min_cell, moves[min_cell][i]);
    Solve(grid);
    grid.ClearCell(min_cell);
  }
}

}  // namespace sudoku_solver
