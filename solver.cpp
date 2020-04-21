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
    int pvals[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  public:
    // set actual value of cell
    void setVal(int n);
    // get actual value of cell
    int getVal();
    // get possible values of cell
    int* getPVals();
    // remove n from possible values vector
    void remPVal(int* n);
};

void Cell::setVal(int n) {
  rval = n;
  if (n != 0)
    memset(pvals, 0, sizeof(pvals));
}

int Cell::getVal() {
  return rval;
}

int* Cell::getPVals() {
  return pvals;
}

void Cell::remPVal(int* n) {
  
}

class Sudoku {
  private:
    string fileName;
    Cell grid[9][9];
    Cell squares[9][3][3];
  public:
    Sudoku(string n);
    void parseData();
    Cell* getData();
    Cell* getCell(int, int);
    void makeSquares();
    void calPvals(int, int);
    void pvalRow(Cell*, int);
    void pvalCol(Cell*, int);
    void pvalSquare(Cell*, int, int);
    void printAll();
};

// get filename from command line arguments
Sudoku::Sudoku(string fname) {
  fileName = fname;
  parseData();
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
  
}

void Sudoku::calPvals(int row, int col) {
  Cell* thisCell = getCell(row, col);
  pvalRow(thisCell, row);
  pvalCol(thisCell, col);
  pvalSquare(thisCell, row, col);
}

// get the values present in thisCell's row and remove those from pval
void Sudoku::pvalRow(Cell* thisCell, int row) {
  int x;
  int* ptr;
  Cell* c;
  // get pvals of thisCell
  int* pval = thisCell->getPVals();

  // iterate through the cells on the same row as thisCell
  for (int i = 0; i < 9; i++) {
    // get the value of each cell
    c = getCell(row, i);
    x = c->getVal();
    // find the value of each cell in thisCell's possible values
    ptr = find(pval, pval+9, x);
    if (ptr != pval+9) {
      // value x found in pval
      // remove x from thisCell's possible values
      thisCell->remPVal(ptr);
    }
  }
}

// get the values present in the cell's column and remove those from pval
void Sudoku::pvalCol(Cell* thisCell, int col) {

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
      int* p = c->getPVals();
      for(int k = 0; k < 8; k++) {
        cout << p[k];
      }
      cout << endl;
    }
  }
}

int main(int argc, char* argv[]) {
  Sudoku s(argv[1]);
  s.calPvals(0,2);
  s.printAll();
}
