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
void parseData(string fileName, int* grid) {
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

int main(int argc, char* argv[]) {
  // init memory for grid
  int* grid = (int*)malloc(81*sizeof(int));

  parseData(argv[1], grid);
  display(grid);
  return 0;
}