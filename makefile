SRCS=main.cpp SudokuSolver.cpp SudokuGrid.cpp
HDRS=SudokuSolver.h SudokuGrid.h

.PHONY: build
build: $(SRCS) $(HDRS)
	g++ -o sudoku $(SRCS)

.PHONY: clean
clean:
	rm -f sudoku
