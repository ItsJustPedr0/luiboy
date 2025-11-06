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
  cout << "\nPlease input the name of your matrix file (defaults to 'matrix'): ";
  
  string fileName;
  vector<vector<double>> gaussMatrix;
    
  gaussMatrix = readMatrixFile(readUserInput());
  
  cout << endl << "Solution:" << endl;
  gaussElimination(gaussMatrix);
}
