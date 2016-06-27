#include "SudokuSolver.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: ./SudokuSolver FILEPATH" << std::endl;
    return 1;
  }

  SudokuGrid grid;

  try {
    grid.fromFile(argv[1]);
    std::cout << grid << std::endl;
  } catch (const char *error) {
    std::cerr << error;
    return 1;
  }

  SudokuSolver solver;
  solver.solve(grid);
}
