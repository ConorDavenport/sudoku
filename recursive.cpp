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
int parseData(string fileName, int* grid, int* lookup) {
  int zeroElements = 0;
  ifstream file;
  file.open(fileName);
  string field;

  for (int i = 0; i < 81; i++) {
    getline(file, field, ','); // read char from example
    grid[i] = stoi(field);  // string to int

    // if the current element is zero
    // increase the size of lookup by one int
    // record the index of the zero element 
    if (stoi(field) == 0) {
      zeroElements++;
      lookup[zeroElements - 1] = i;
    }
  }
  file.close();
  return zeroElements;
}

void display(int* grid) {
  for (int i = 0; i < 81; i++) {
    if ((i % 9) == 0)
      cout << "\n";
    cout << grid[i];
  }
}

void check(int* grid) {
  
}

void solve(int* grid, int n) {
  if (n == 81) {
    return;
  }

  if (grid[n] == 0)
    cout << n << endl;
  n++;
  solve(grid, n);
}

int main(int argc, char* argv[]) {
  // init memory for grid
  int* grid = (int*)malloc(81 * sizeof(int));
  // lookup table to keep track of which
  // cells in the grid are zero at the start
  // of the game
  int* lookup = (int*)malloc(81 * sizeof(int));

  int lookupLength = parseData(argv[1], grid, lookup);
  
  for (int i = 0; i < lookupLength; i++) {
    printf("%d\n", lookup[i]);
  }

  free(grid);
  free(lookup);
  return 0;
}