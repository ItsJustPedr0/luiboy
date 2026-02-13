// Augusto Gabbriel M. Calilung
// Peter Julius M. Estacio
// Rafael Luis Mari R. Lambo
// ENGG 27.01 - M
// Project 1 - Fixed-Point Approach for Finding Roots of Polynomials
// main.cpp

#include "fixedPoint.h"

int main()
{  
  //initializes empty variables for equation index and array pointer
  int equationIndex = 0;
  double* equation = 0;
  
  //reads polynomial file and modifies above variables 
  readPolynomialFile(equation, &equationIndex);
  
  //calls function to use fixed point approach to find roots
  evaluateFixedPoint(equation, equationIndex);
}