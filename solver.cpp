#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

int coordToNum(int, int);

class Cell {
  private:
    // real value
    int rval = 0;
    // possible values
    vector<int> pvals = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  public:
    void setVal(int n);
    int getVal();
    vector<int>* getPVals();
};

void Cell::setVal(int n) {
  rval = n;
  pvals.resize(0);
}

int Cell::getVal() {
  return rval;
}

vector<int>* Cell::getPVals() {
  return &pvals;
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
    void pvalRow(int, int);
    void pvalCol(int, int);
    void pvalSquare(int, int);
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
      int nfield = stoi(field);
      if (nfield != 0) {
        grid[i][j].setVal(nfield);
      }
    }
  }
}

Cell* Sudoku::getData() {
  return* grid;
}

Cell* Sudoku::getCell(int row, int col) {
  int num = coordToNum(row, col);
  Cell* cell = grid[num];
  return cell;
}

void Sudoku::makeSquares() {

}

void Sudoku::calPvals(int row, int col) {
  Cell* thisCell = getCell(row, col);
  vector<int>* pval = thisCell->getPVals();
  pvalRow(row, col);
  pvalCol(row, col);
  pvalSquare(row, col);
}

// get the values present in thisCell's row and remove those from pval
void Sudoku::pvalRow(int row, int col) {
  Cell* c;
  int v;
  // iterate along the row
  for (int i = 0; i < 9; i++) {
    // get the cells in the row
    c = getCell(row, i);
    // get their value
    v = c->getVal();
  }
}

// get the values present in the cell's column and remove those from pval
void Sudoku::pvalCol(int row, int col) {

}

// get the values present in the cell's 3x3 square and remove those fro pval
void Sudoku::pvalSquare(int row, int col) {

}

int main(int argc, char* argv[]) {
  Sudoku s(argv[1]);
  s.calPvals(0, 0);
  Cell* c = s.getCell(0, 0);
  vector<int>* p = c->getPVals();
  p->push_back(9);
  Cell* c1 = s.getCell(0,0);
  vector<int>* p1 = c1->getPVals();
  
  return 0;
}

int coordToNum(int row, int col) {
  return (row * 9) + col;
}