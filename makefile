SRCS=main.cpp SudokuSolver.cpp SudokuGrid.cpp
HDRS=SudokuSolver.h SudokuGrid.h

sudoku: $(SRCS) $(HDRS)
	g++ -o sudoku $(SRCS)

clean:
	rm -f sudoku
