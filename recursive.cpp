#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

// get sudoku example game
// load game into grid, 1d vector
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

// save vector v to file examples/solution.csv
void save(vector<int> v) {
  ofstream file;
  file.open("examples/solution.csv");
  int i = 0;
  // iterate through v, write elements to file
  // insert new line after every ninth element
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

// return true if v contains no duplicates
bool isUnique(vector<int> v) {
  sort(v.begin(), v.end());
  vector<int>::iterator it = unique(v.begin(), v.end());
  if(it == v.end()) {
    return true;
  } else {
    return false;
  }
}

// print vector v to console
void printVec(vector<int> v) {
  for (vector<int>::const_iterator i = v.begin(); 
       i != v.end(); ++i) {
    printf("%d", *i);
  }
  printf("\n");
}

// returns false if the value in cell n doesn't fit
// the game solution
// check() is called when a new value has been put
// into cell n
// params
// grid   vector containing game board
// n      index of element to be checked
bool check(vector<int> grid, int n) {
  // init vectors that will contain the non zero
  // elements from the game board. These correspond
  // to cell n's row, column, and 3x3 square
  vector<int> square, row, col;
  // check row
  // grid is a 1d vector, find the index of
  // the first element of cell n's row
  int rowStartIndex = n - n%9;
  // iterate through row and fill vector row with all
  // non zero elements
  for(int i = rowStartIndex; i < rowStartIndex + 9; i++) {
    if(grid[i] != 0)
      row.push_back(grid[i]);
  }

  // check if the row contains duplicates
  // the value that has been put into cell n will be
  // valid if there are no duplicates
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

// find the next zero filled element in vector v
int findZero(vector<int> v) {
  vector<int>::iterator it = find(v.begin(), v.end(), 0);
  if (it != v.end()) {
    return it - v.begin();
  } else {
    return -1;
  }
}

// solve game
// params
// stack    lifo stack of game states
int solve(vector<vector<int>>& stack) {
  // get working game state
  vector<int> grid = stack.back();
  // find index of next zero filed cell to try numbers in
  int cell = findZero(grid);
  // if there are no zero filled cells or if
  // the function has gotten to the end of the grid
  // return 0
  if (-1 == cell || cell > 80) {
    return 0;
  }
  // try numbers
  for (int i = 1; i < 11; i++) {
    // input number i into the current zero filled cell
    grid[cell] = i;
    // the end of the loop is reached when no number
    // from 1 to 9 works in the current cell
    if (10 == i) {
      // pop the current working state off the stack
      // and return to the previous zero filled cell
      stack.pop_back();
      return 1;
    }
    // if number i works in the cell
    else if (check(grid, cell)) {
      // push the found solution for current cell
      // to the stack
      stack.push_back(grid);
      // call solve() for the next zero filled cell
      // if it returns zero, ie. it has reached the
      // end of the game, break recursion by returning
      // zero all the way up
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

  // load data from file into grid
  parseData(argv[1], grid);

  // lifo stack to hold game states
  vector<vector<int>> stack;

  // load starting game state into stack
  stack.push_back(grid);

  // solve game
  solve(stack);

  // perform final checks on solution
  for (int i = 0; i < grid.size(); i++) {
    if (!check(grid, i)) {
      printf("unsolved");
      return 1;
    }
  }

  // save solution to examples/solution.csv
  save(stack.back());
  return 0;
}