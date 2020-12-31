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

void save(vector<int> v) {
  ofstream file;
  file.open("examples/solution.csv");
  int i = 0;
  for (vector<int>::const_iterator it = v.begin();
       it < v.end(); it++) { 
    i++;
    file << *it << ","; 
    if (0 == i%9) {
      file << endl;
    }
  }
  file.close();
}

bool isUnique(vector<int> v) {
  sort(v.begin(), v.end());
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
    printf("%d", *i);
  }
  printf("\n");
}

// returns false if cell n doesn't fit
bool check(vector<int> grid, int n) {
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

int findZero(vector<int> v) {
  vector<int>::iterator it = find(v.begin(), v.end(), 0);
  if (it != v.end()) {
    return it - v.begin();
  } else {
    return -1;
  }
}

// return codes
// 0  no zero cells left
int solve(vector<vector<int>>& stack) {
  // get working game state
  vector<int> grid = stack.back();
  // find index of next zero cell to try numbers in
  int cell = findZero(grid);
  if (-1 == cell || cell > 80) {
    return 0;
  }
  // try numbers
  for (int i = 1; i < 11; i++) {
    grid[cell] = i;
    if (10 == i) {
      stack.pop_back();
      return 1;
    }
    // if number i works in the cell
    else if (check(grid, cell)) {
      stack.push_back(grid);
      if (0 == solve(stack)) {
        return 0;
      }
    }
  }
  return 1;
}

int main(int argc, char* argv[]) {
  // init memory for grid
  vector<int> grid;

  parseData(argv[1], grid);

  // fifo stack to hold game states
  vector<vector<int>> stack;
  stack.push_back(grid);
  solve(stack);
  save(stack.back());
  return 0;
}