SRCS=src/main.cc src/solver.cc src/grid.cc
HDRS=src/solver.h src/grid.h

.PHONY: build
build: $(SRCS) $(HDRS)
	g++ -o sudoku-solver $(SRCS)

.PHONY: clean
clean:
	rm -f sudoku
