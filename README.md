# Sudoku Solver

A solver for the classic Sudoku game written in C++. Uses a brute force approach, nothing clever going on here.

## Compile and Run

This project was last tested and working against the `gcc` compiler version 7.4.0. To compile...
```shell
cd sudoku-solver
make build
```
An input puzzle file is required to run the solver. There are 4 test puzzles included in the `puzzles/` directory (easy, medium, hard and unsolvable)
```shell
./sudoku-solver puzzles/hard.sdk # Or just `make solve/hard`
```
![alt text](https://tomcant.s3-eu-west-1.amazonaws.com/resources/images/sudoku-solver/sudoku-hard-unsolved.png "Hard Sudoku puzzle, unsolved")
![alt text](https://tomcant.s3-eu-west-1.amazonaws.com/resources/images/sudoku-solver/sudoku-hard-solved.png "Hard Sudoku puzzle, solved")

## General Approach

This algorithm uses [Depth-first search](https://en.wikipedia.org/wiki/Depth-first_search) to apply every combination of possible choices per cell either until the grid is full or until there are no more choices to explore, in which case the puzzle is unsolvable.

Roughly speaking, the following steps are taken:

1. Make as many forced moves as possible (i.e. where the number of choices for a given cell is one). This will be enough to solve most _easy_ puzzles.
2. Check for completeness or unsolvability:
   - If the grid now contains no empty cells then we are done and the grid is returned.
   - If the grid now contains an empty cell with no choices then mark this combination as unsolvable.
3. Find the cell with the fewest choices and apply each of them in turn, attempting to solve each new puzzle this produces (recurse back to step 1).

## To Do

+ Format input files like a Sudoku grid rather than as a string of digits on one line.
