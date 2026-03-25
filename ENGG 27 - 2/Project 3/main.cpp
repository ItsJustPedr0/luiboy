// Augusto Gabbriel M. Calilung
// Peter Julius M. Estacio
// Rafael Luis Mari R. Lambo
// ENGG 27.01 - M
// Project 3 - Roots of Polynomials
// main.cpp

#include "polyRootFinder.h"

int main()
{  
  //initializes empty variables for equation index and array pointer
  int equationIndex = 0;
  double* equation = 0;
  
  //reads polynomial file and modifies above variables 
  readPolynomialFile(equation, &equationIndex);
  bairstowsMethod(equation, equationIndex);
}