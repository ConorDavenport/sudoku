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

    // if the current element is zero
    // increase the size of lookup by one int
    // record the index of the zero element 
    if (stoi(field) == 0) {
      zeroElements++;
      lookup[zeroElements - 1] = i;
    }
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
void solve(int* grid, int* lookup, int n, int l) {
  for (int i = 1; i < 10; i++) {
    grid[lookup[n]] = i;
    check(grid, lookup[n]);
  }
  if (n == l - 1)
    return;
  n++;
  solve(grid, lookup, n, l);
}

int main(int argc, char* argv[]) {
  // init memory for grid
  int* grid = (int*)malloc(81 * sizeof(int));

  //solve(grid, lookup, 0, lookupLength);

  // for (int i = 0; i < 81; i++) {
  //   if (i % 9 == 0) {
  //     printf("\n");
  //   }
  //   printf("%d", grid[i]);
  // }
  bool b = check(grid, 57);
  free(grid);
  free(lookup);
  return 0;
}