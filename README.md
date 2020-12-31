# sudoku
The aim of this project is to write a program that solves a game of
sudoku using recursion and backtracking.

## What is sudoku
Stolen from Wikipedia; In classic sudoku, the objective is to fill a
9×9 grid with digits so that each column, each row, and each of the
nine 3×3 subgrids that compose the grid (also called "boxes",
"blocks", or "regions") contain all of the digits from 1 to 9. The
puzzle setter provides a partially completed grid, which for a
well-posed puzzle has a single solution.

Example games can be found in `examples/`.

## How to run the solver
Pass one of the examples to the executable as a command line
argument. For example; `a.exe examples/1.csv`. The solution is saved
into `examples/solution.csv`.

## Solving a custom game
Transcribe your game into a csv file. Each value is separated by a
comma, and blank cells are represented by a zero.
