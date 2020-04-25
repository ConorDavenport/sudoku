#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;

int coordToNum(int, int);

class Cell {
  private:
    // real value
    int rval = 0;
    // possible values
    vector<int> pvals{1, 2, 3, 4, 5, 6, 7, 8, 9};
  public:
    // set actual value of cell
    void setVal(int n);
    // get actual value of cell
    int getVal();
    // get possible values of cell
    vector<int>* getPVals();
};

void Cell::setVal(int n) {
  rval = n;
  if (n != 0)
    pvals.clear();
}

int Cell::getVal() {
  return rval;
}

vector<int>* Cell::getPVals() {
  vector<int>* ptr = &pvals;
  return ptr;
}

class Sudoku {
  private:
    string fileName;
    Cell grid[9][9];
    Cell* squares[3][3][9];
  public:
    Sudoku(string n);
    void parseData();
    Cell* getData();
    Cell* getCell(int, int);
    void makeSquares();
    void calPvals();
    void calCellPvals(int, int);
    void pvalRow(Cell*, int);
    void pvalCol(Cell*, int);
    void pvalSquare(Cell*, int, int);
    void printAll();
    Cell** getSquare(int, int);
};

// get filename from command line arguments
Sudoku::Sudoku(string fname) {
  fileName = fname;
  parseData();
  makeSquares();
}

// set the value of each Cell
void Sudoku::parseData() {
  ifstream file;
  file.open(fileName);
  string field;

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      getline(file, field, ',');
      grid[i][j].setVal(stoi(field));
    }
  }
  file.close();
}

Cell* Sudoku::getData() {
  return* grid;
}

Cell* Sudoku::getCell(int row, int col) {
  Cell* cell = &grid[row][col];
  return cell;
}

void Sudoku::makeSquares() {
  // iterate through squares
  for (int squareRow = 0; squareRow < 3; squareRow++) {
    for (int squareCol = 0; squareCol < 3; squareCol++) {
      // iterate through the cells in the square
      for (int cellRow = 0; cellRow < 3; cellRow++) {
        for (int cellCol = 0; cellCol < 3; cellCol++) {
          int cellCoordRow = cellRow + (squareRow * 3);
          int cellCoordCol = cellCol + (squareCol * 3);
          Cell* c = getCell(cellCoordRow, cellCoordCol);
          squares[squareRow][squareCol][(cellRow * 3) + cellCol] = c;
        }
      }
    }
  }
}

void Sudoku::calPvals() {
  // row
  for(int i = 0; i < 9; i++) {
    // column
    for(int j = 0; j < 9; j++) {
      calCellPvals(i, j);
    }
  }
}

void Sudoku::calCellPvals(int row, int col) {
  Cell* thisCell = getCell(row, col);
  pvalRow(thisCell, row);
  pvalCol(thisCell, col);
  pvalSquare(thisCell, row, col);
}

// get the values present in thisCell's row and remove those from pval
void Sudoku::pvalRow(Cell* thisCell, int row) {
  Cell* c;
  int x;
  vector<int>* pval = thisCell->getPVals();
  // get thisCell's pval vector
  vector<int>& pvalRef = *pval;
  if (pvalRef.size() != 0) {
    // iterate through thisCell's row
    for (int i = 0; i < 9; i++) {
      // get the value of each cell
      c = getCell(row, i);
      x = c->getVal();
      pvalRef.erase(remove(pvalRef.begin(), pvalRef.end(), x), pvalRef.end());
    }
  }
}

// get the values present in the cell's column and remove those from pval
void Sudoku::pvalCol(Cell* thisCell, int col) {
  Cell* c;
  int x;
  vector<int>* pval = thisCell->getPVals();
  // get thisCell's pval vector
  vector<int>& pvalRef = *pval;
  if (pvalRef.size() != 0) {
    // iterate through thisCell's row
    for (int i = 0; i < 9; i++) {
      // get the value of each cell
      c = getCell(i, col);
      x = c->getVal();
      pvalRef.erase(remove(pvalRef.begin(), pvalRef.end(), x), pvalRef.end());
    }
  }
}

// get the values present in the cell's 3x3 square and remove those fro pval
void Sudoku::pvalSquare(Cell* thisCell, int row, int col) {
  
}

void Sudoku::printAll() {
  cout << "coord\tv\tpvals\n";
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      Cell* c = getCell(i, j);
      cout << i << ", " << j << "\t" << c->getVal() << "\t";
      vector<int>* p = c->getPVals();
      vector<int>& pRef = *p; 
      for(int k = 0; k < pRef.size(); k++) {
        cout << pRef.at(k);
      }
      cout << endl;
    }
  }
}

// get square of cell(x, y)
Cell** Sudoku::getSquare(int x, int y) {
  int squareRow = x / 3;
  int squareCol = y / 3;
  return squares[squareRow][squareCol];
}

int main(int argc, char* argv[]) {
  Sudoku s(argv[1]);
}
