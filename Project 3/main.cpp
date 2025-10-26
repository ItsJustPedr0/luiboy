//Filename: main.cpp
//Assignment: Project 3: Gauss Elimination
//Name: Peter Estacio
//Grouped with Nino De Mesa and Joshnare Ong
//Section: ENGG 27.01 - M

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

void readMatrixFile()
{
  fstream matrixFile("matrix");
  string m;
  int rowNumber;
  int colNumber;

  while (getline(matrixFile, m))
  {
    istringstream matrixRowStream(m);
    double matrixElement;
    while(matrixRowStream >> matrixElement)
    {
      cout << matrixElement << " ";
    }
    cout << endl;
    rowNumber++;
  }
}

void gaussElimination()
{
  int n;
  for (int k = 1; k < (n-1); k++)
  {
    int m = k;
    for (int j = k + 1; j < n; j++)
    {
      //insert code here
    }
  }
}

int main()
{
  readMatrixFile();

}
