#include <string>
#include <vector>
#include "solver.h"

namespace sudoku_solver {

Grid Solver::Solve(Grid grid) {
  // Make as many forced moves as possible.
  bool forced_move_available;
  vector<string> moves;

  do {
    forced_move_available = false;
    moves = grid.GenerateMoves();

    for (size_t cell = 0; cell < Grid::SIZE; ++cell) {
      if (moves[cell].size() == 1) {
        forced_move_available = true;
        grid.SetCell(cell, moves[cell][0]);
        break;
      }
    }
  } while (forced_move_available);

  if (grid.IsComplete()) {
    return grid;
  }

  // Find the cell with the fewest possibilities.
  size_t min = 9,
    min_cell = 0;

  for (size_t cell = 0; cell < Grid::SIZE; ++cell) {
    if (!grid.IsCellClear(cell)) {
      continue;
    }

    size_t size = moves[cell].size();

    if (size == 0) {
      throw "unsolvable";
    }

    if (size < min) {
      min = size;
      min_cell = cell;
    }
  }

  // Search the sub-tree of possibilities.
  for (size_t i = 0; i < min; ++i) {
    grid.SetCell(min_cell, moves[min_cell][i]);

    try {
      return Solve(grid);
    } catch (char const *c) {
      grid.ClearCell(min_cell);
    }
  }

  throw "unsolvable";
}

}  // namespace sudoku_solver
