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
void parseData(string fileName, vector<int>& grid) {
  ifstream file;
  file.open(fileName);
  string field;

  for (int i = 0; i < 81; i++) {
    getline(file, field, ','); // read char from example
    grid.push_back(stoi(field));  // string to int
  }
  file.close();
}

bool isUnique(vector<int> v) {
  vector<int>::iterator it = unique(v.begin(), v.end());
  if(it == v.end()) {
    return true;
  } else {
    return false;
  }
}

void printVec(vector<int> v) {
  for (vector<int>::const_iterator i = v.begin(); 
       i != v.end(); ++i) {
    printf("%d ", *i);
  }
  printf("\n");
}

// right now only prints the row, col, and 3x3 of cell n
bool check(vector<int>& grid, int n) {
  vector<int> square, row, col;
  // check row
  int rowStartIndex = n - n%9;
  for(int i = rowStartIndex; i < rowStartIndex + 9; i++) {
    if(grid[i] != 0)
      row.push_back(grid[i]);
  }

  if(!isUnique(row)) {
    return false;
  }

  // check col
  for (int i = (0 + n%9); i < 81; i += 9) {
    if(grid[i] != 0)
      col.push_back(grid[i]);
  }

  if(!isUnique(col)) {
    return false;
  }

  // check square
//    ━━━━━━━━ X ━━━━━━━━                                                                        
//       0     1     2
// ┃  ┏━━━━━┳━━━━━┳━━━━━┓                              
// ┃  ┃     ┃     ┃     ┃                              
// ┃ 0┃     ┃     ┃     ┃                              
// ┃  ┃     ┃     ┃     ┃                              
// ┃  ┣━━━━━╋━━━━━╋━━━━━┫                              
//    ┃     ┃     ┃     ┃                              
// Y 1┃     ┃     ┃     ┃                              
//    ┃     ┃     ┃     ┃                              
// ┃  ┣━━━━━╋━━━━━╋━━━━━┫                              
// ┃  ┃     ┃     ┃     ┃                              
// ┃ 2┃     ┃     ┃     ┃                              
// ┃  ┃     ┃     ┃     ┃                              
// ┃  ┗━━━━━┻━━━━━┻━━━━━┛                              
               
  int squareX = (n%9)/3;
  int squareY = (n/9)/3;
  // get upper left cell of the square
  int squareStart = (3*squareX) + (27*squareY);

  for(int j = 0; j < 3; j++) {
    for(int i = squareStart + (9*j); i < (squareStart + (9*j)) + 3; i++) {
      if(grid[i] != 0)
        square.push_back(grid[i]);
    }
  }

  if(!isUnique(square)) {
    return false;
  }

  return true;
}

int stack_push(vector<int> grid, vector<int> stack) {
  
}

int stack_pop(vector<int> stack) {

}

// n is the current cell index
void solve(vector<int>& grid, int& n, vector<int>& stack) {

}

int main(int argc, char* argv[]) {
  // init memory for grid
  vector<int> grid;

  parseData(argv[1], grid);

  int n = 0;
  vector<int> stack;
  solve(grid, n, stack);

  return 0;
}