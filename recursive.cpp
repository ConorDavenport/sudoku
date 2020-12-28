#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

// get sudoku example game
// load game into grid
void parseData(string fileName, int* grid, int* lookup) {
  ifstream file;
  file.open(fileName);
  string field;

  for (int i = 0; i < 81; i++) {
    getline(file, field, ','); // read char from example
    grid[i] = stoi(field);  // string to int
  }
  file.close();
}

void display(int* grid) {
  for (int i = 0; i < 81; i++) {
    if ((i % 9) == 0)
      cout << "\n";
    cout << grid[i];
  }
}

bool check(int* grid, int n) {
  // check row
  int rowStartIndex = n - n%9;
  for(int i = rowStartIndex; i < rowStartIndex + 9; i++) {
    printf("%d", grid[i]);
  }
  printf("\n");
  // check col
  for (int i = (0 + n%9); i < 81; i += 9) {
    printf("%d", grid[i]);
  }
  // check square
  
  return false;
}

// n is the current lookup index
void solve(int* grid) {
  
}

int main(int argc, char* argv[]) {
  // init memory for grid
  int* grid = (int*)malloc(81 * sizeof(int));

  solve(grid);

  bool b = check(grid, 57);
  free(grid);
  return 0;
}