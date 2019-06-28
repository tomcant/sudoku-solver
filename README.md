# Sudoku Solver

A solver for the classic Sudoku game written in C++. Uses a depth first brute force approach, nothing clever going on here...

## Compile and Run

This project was last tested and working against the `gcc` compiler version 7.4.0. To compile...
```
cd sudoku-solver-cpp
make build
```
An input puzzle file is required to run the solver. There are 3 test puzzles included in the `puzzles/` directory (easy, medium, hard)
```
./sudoku-solver puzzles/hard.sdk
```
![alt text](https://tomcant.s3-eu-west-1.amazonaws.com/resources/images/sudoku-solver/sudoku-hard-unsolved.png "Hard Sudoku puzzle, unsolved")
![alt text](https://tomcant.s3-eu-west-1.amazonaws.com/resources/images/sudoku-solver/sudoku-hard-solved.png "Hard Sudoku puzzle, solved")

## General Approach

This algorithm uses recursion to apply every combination of possible choices per cell either until the grid is full or until there are no more choices to explore, in which case the puzzle is unsolvable.

Roughly speaking, the following steps are taken:

1. Make as many forced moves as possible (i.e. where the number of possible choices for a given cell is 1). This should be enough to solve most _easy_ puzzles.
2. If the grid contains a cell with zero possible choices at this stage then mark this combination of choices as unsolvable from this point. This will bubble back up the recursive step.
3. Find the cell with the fewest possible choices and for each one, apply it to the grid and go back to step 1 (this is the recursive step).

## To Do

+ The `Solver::Solve()` method should return a completed `Grid` instance rather than output the grid when it's done. It doesn't make sense for the solver to be concerned with what it means to output a grid; it should only be concerned with finding the solution. Output should be taken care of by a separate module.
+ It would be nice if the input files were formatted like a Sudoku grid rather than as a string of digits on one line.
