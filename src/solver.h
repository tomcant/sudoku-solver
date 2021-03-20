#ifndef SRC_SOLVER_H_
#define SRC_SOLVER_H_

#include "grid.h"

namespace sudoku_solver {

class Solver {
 public:
  static Grid Solve(Grid);
};

struct Unsolvable : public std::runtime_error {
  Unsolvable() : std::runtime_error("Grid is not solvable") {}
};

}  // namespace sudoku_solver

#endif  // SRC_SOLVER_H_
