#include "solver.h"
#include <emscripten/bind.h>

using std::string;
using std::exception;
using emscripten::class_;
using emscripten::function;
using sudoku_solver::Grid;
using sudoku_solver::Solver;

EMSCRIPTEN_BINDINGS(Grid) {
  class_<Grid>("Grid")
    .function("GetCells", &Grid::GetCells)
    .function("ToString", &Grid::ToString)
    .class_function("FromString", &Grid::FromString);
}

EMSCRIPTEN_BINDINGS(Solver) {
  class_<Solver>("Solver")
    .class_function("Solve", &Solver::Solve);
}

string getExceptionMessage(intptr_t ptr) {
  return string(reinterpret_cast<exception *>(ptr)->what());
}

EMSCRIPTEN_BINDINGS(getExceptionMessage) {
  function("getExceptionMessage", &getExceptionMessage);
}
