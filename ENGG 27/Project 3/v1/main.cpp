//Filename: main.cpp
//Assignment: Project 3: Gauss Elimination
//Name: Peter Estacio
//Grouped with Nino De Mesa and Joshnare Ong
//Section: ENGG 27.01 - M

#include "gaussFunction.h"

int main()
{
  cout << "=========================" << endl;
  cout << "Gauss Elimination Program" << endl;
  cout << "=========================" << endl;

  string continueString; 
  vector<vector<double>> gaussMatrix;

  while (true)
  {
    cout << "\nPlease input the name of your" 
      << " matrix file (defaults to 'matrix'): ";
    fstream matrixFile = readUserInput();
    gaussMatrix = readMatrixFile(matrixFile);
    if (!gaussMatrix.empty())
    {
      cout << endl << "Solution:" << endl;
      gaussElimination(gaussMatrix);
    }

    cout << "\nWould you like to choose another file?" << endl
      << "Enter any character to continue or enter 'N' to exit: ";
    getline(cin, continueString);

    if (continueString == "N")
    return 0;
  }
}