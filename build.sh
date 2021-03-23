#!/bin/bash

emcc --bind -o public/sudoku-solver.js src/wasm-bindings.cc src/solver.cc src/grid.cc -s DISABLE_EXCEPTION_CATCHING=0 -O3
