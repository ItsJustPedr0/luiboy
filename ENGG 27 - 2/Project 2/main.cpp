// Augusto Gabbriel M. Calilung
// Peter Julius M. Estacio
// Rafael Luis Mari R. Lambo
// ENGG 27.01 - M
// Project 2 - Power Method for Eigenvalues and Eigenvectors
// main.cpp

#include "powerMethod.h"

int main()
{
  string fileName = "";
  vector<vector<double>> matrix;
  int matrixSize = 0;

  cout << "Hello, welcome to find the Eigenvalue and Eigenvector-inator!" << endl;
  
  readMatrixFile(&fileName, matrix, &matrixSize);
  if (matrixSize == 0)
  {
    cout << "Empty matrix read. Invalid matrix file.";
    return 0;
  }

  double eigenValue = 0;
  vector<double> eigenVector(matrixSize);
  string Choice = "";
  
  
  calcPowerMethod(matrix, matrixSize, eigenVector, eigenValue);
}