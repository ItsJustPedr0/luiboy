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
  
  string fileName;
  char continueChar;
  vector<vector<double>> gaussMatrix;
  
  while(!(continueChar == 'n'))
  {
    cout << "\nPlease input the name of your matrix file (defaults to 'matrix'): ";
    gaussMatrix = readMatrixFile(readUserInput());
    
    if(gaussMatrix.empty() == false){
      cout << endl << "Solution:" << endl;
      gaussElimination(gaussMatrix);
    }
    
    cout << "\nWould you like to choose another file?" << endl
        << "Enter any character to continue or enter 'n' to exit: ";
    cin.get(continueChar);
  }
}
