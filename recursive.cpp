#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

// get sudoku example game
// load game into grid
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
      printf("\n");
    printf("%d", grid[i]);
  }
  printf("\n");
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
    printf("%d\n", grid[i]);
  }
  // check square
//   ━━━━━━━━ X ━━━━━━━━                                                                        
// ┃ ┏━━━━━┳━━━━━┳━━━━━┓                              
// ┃ ┃     ┃     ┃     ┃                              
// ┃ ┃     ┃     ┃     ┃                              
// ┃ ┃     ┃     ┃     ┃                              
// ┃ ┣━━━━━╋━━━━━╋━━━━━┫                              
//   ┃     ┃     ┃     ┃                              
// Y ┃     ┃     ┃     ┃                              
//   ┃     ┃     ┃     ┃                              
// ┃ ┣━━━━━╋━━━━━╋━━━━━┫                              
// ┃ ┃     ┃     ┃     ┃                              
// ┃ ┃     ┃     ┃     ┃                              
// ┃ ┃     ┃     ┃     ┃                              
// ┃ ┗━━━━━┻━━━━━┻━━━━━┛                              
               
  int squareX = (n%9)/3;
  int squareY = (n/9)/3;

  int squareStart = (3*squareX) + (27*squareY);
  vector<int> square;
  for(int i = 0; i < 3; i++) {
    for(int j = squareStart + (9*i); j < (squareStart + (9*i)) + 3; j++) {
      square.push_back(grid[j]);
    }
  }
  for (vector<int>::const_iterator i = square.begin(); 
       i != square.end(); ++i) {
    printf("%d", *i);
  }
  return false;
}

// n is the current lookup index
void solve(int* grid) {

}

int main(int argc, char* argv[]) {
  // init memory for grid
  int* grid = (int*)malloc(81 * sizeof(int));

  parseData(argv[1], grid);

  solve(grid);

  display(grid);

  check(grid, 64);

  free(grid);
  return 0;
}