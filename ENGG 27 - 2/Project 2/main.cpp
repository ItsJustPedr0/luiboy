// Augusto Gabbriel M. Calilung
// Peter Julius M. Estacio
// Rafael Luis Mari R. Lambo
// ENGG 27.01 - M
// Project 2 - Power Method for Eigenvalues and Eigenvectors
// main.cpp

#include "powerMethod.h"

int main()
{
  int testSize = 5;
  vector<vector<double>> testMatrix =
  {
    {-8.8, 0.5, 6.2, 1.3, -7.2},
    {9.6, 6.7, -1.0, -0.8, -6.4},
    {-4.3, 7.3, 2.2, -0.7, 3.1},
    {-9.4, -7.7, -0.2, -8.4, -4.4},
    {-7.7, 2.5, -3.0, -6.4, 4.2}
  };  
  
  double testEigenValue;
  vector<double> testEigenVector(testSize);
  calcPowerMethod(testMatrix, testSize, testEigenVector, testEigenValue);
}