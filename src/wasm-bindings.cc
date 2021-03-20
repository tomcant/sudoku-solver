#include "solver.h"
#include <emscripten/bind.h>

using std::string;
using emscripten::class_;
using sudoku_solver::Grid;
using sudoku_solver::Solver;

EMSCRIPTEN_BINDINGS(grid) {
  class_<Grid>("Grid")
    .constructor<string>()
    .function("GetCells", &Grid::GetCells);
}

EMSCRIPTEN_BINDINGS(solver) {
  class_<Solver>("Solver")
    .class_function("Solve", &Solver::Solve);
}
