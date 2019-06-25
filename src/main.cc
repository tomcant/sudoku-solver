#include "solver.h"

using std::cerr;
using std::cout;
using std::endl;

using sudoku_solver::Grid;
using sudoku_solver::Solver;

int main(int argc, char *argv[]) {
  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " /path/to/puzzle.sdk" << endl;
    return 1;
  }

  Grid grid;

  try {
    grid.FromFile(argv[1]);
    cout << grid << endl;
  } catch (const char *error) {
    cerr << error;
    return 1;
  }

  Solver solver;
  solver.Solve(grid);
}
