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
    bool flag = false;
    string fileName;
    Cell grid[9][9];
    Cell* squares[3][3][9];
  public:
    Sudoku(string n);
    bool isDone();
    void done();
    void parseData();
    Cell* getData();
    Cell* getCell(int, int);
    void makeSquares();
    void calPvals();
    bool calCellPvals(int, int);
    void pvalRow(Cell*, int);
    void pvalCol(Cell*, int);
    void pvalSquare(Cell*, int, int);
    void printAll();
    Cell** getSquare(int, int);
    void saveSolution();
};

// get filename from command line arguments
Sudoku::Sudoku(string fname) {
  fileName = fname;
  parseData();
  makeSquares();
}

bool Sudoku::isDone() {
  return flag;
}

void Sudoku::done() {
  flag = true;
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
  int unfinished = 0;
  bool f;
  // row
  for(int i = 0; i < 9; i++) {
    // column
    for(int j = 0; j < 9; j++) {
      f = calCellPvals(i, j);
      if (f == false) {
        unfinished++;
      }
    }
  }
  if (unfinished == 0) {
    done();
  }
}

bool Sudoku::calCellPvals(int row, int col) {
  Cell* thisCell = getCell(row, col);
  pvalRow(thisCell, row);
  pvalCol(thisCell, col);
  pvalSquare(thisCell, row, col);
  vector<int>* pvals = thisCell->getPVals();
  vector<int>& pvalsRef = *pvals;
  if (pvalsRef.size() == 1) {
    thisCell->setVal(pvalsRef[0]);
  }
  // if the value for this cell has been calculated
  if (thisCell->getVal() != 0) {
    return true;
  } else {
    return false;
  }
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
  Cell* c;
  int x;
  // array of Cell references to the cells in thisCell's square
  Cell** squareCells = getSquare(row, col);
  vector<int>* pval = thisCell->getPVals();
  // get thisCell's pval vector
  vector<int>& pvalRef = *pval;
  if (pvalRef.size() != 0) {
    // iterate through thisCell's square
    for (int i = 0; i < 9; i++) {
      // get the value of each cell
      c = squareCells[i];
      x = c->getVal();
      pvalRef.erase(remove(pvalRef.begin(), pvalRef.end(), x), pvalRef.end());
    }
  }
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

void Sudoku::saveSolution() {
  ofstream outfile ("examples/1_solution.csv");
  for (int i = 0; i < 9; i++) {
    outfile << getCell(i, 0)->getVal() << ",";
    outfile << getCell(i, 1)->getVal() << ",";
    outfile << getCell(i, 2)->getVal() << ",";
    outfile << getCell(i, 3)->getVal() << ",";
    outfile << getCell(i, 4)->getVal() << ",";
    outfile << getCell(i, 5)->getVal() << ",";
    outfile << getCell(i, 6)->getVal() << ",";
    outfile << getCell(i, 7)->getVal() << ",";
    outfile << getCell(i, 8)->getVal() << "," << endl;
  }
  outfile.close();
}

// get square of cell(x, y)
Cell** Sudoku::getSquare(int x, int y) {
  int squareRow = x / 3;
  int squareCol = y / 3;
  return squares[squareRow][squareCol];
}

int main(int argc, char* argv[]) {
  Sudoku s(argv[1]);
  while (!s.isDone()) {
    s.calPvals();
  }
  s.saveSolution();
}
