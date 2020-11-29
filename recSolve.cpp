#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;

void parseData(string fileName, int* grid) {
  ifstream file;
  file.open(fileName);
  string field;

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      getline(file, field, ',');
      
    }
  }
  file.close();
}

void display(int (&grid)[9][9]) {
  cout << "hello";
}

int main(int argc, char* argv[]) {
  int grid[9][9] = {{0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0}};
  display(grid);
  return 0;
}