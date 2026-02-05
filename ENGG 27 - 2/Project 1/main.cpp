// Augusto Gabbriel M. Calilung
// Peter Julius M. Estacio
// Rafael Luis Mari R. Lambo
// ENGG 27.01 - M
// Project 1 - Fixed-Point Approach for Finding Roots of Polynomials
// main.cpp

#include "fixedPoint.h"

int main()
{  
  fstream polynomialFile = readPolynomialFile();

  int equationIndex; // checks for eqn index accdg to file format
  if(!(polynomialFile >> equationIndex))
  {
    cout << "Invalid file, missing polynomial index" << endl;
  }
  else cout << "Polynomial of index " 
    << equationIndex << " read."<< endl;

  // initializes array of coefficients
  double equation[equationIndex+1]; 
  double coeff;

  // stores coefficients in equation array
  for (int i = 0; i < equationIndex + 1; i++)  
  {
    string s3;
    while(polynomialFile >> s3)
    {
      if(is_floating_pt(s3, &coeff))
      {
        equation[i] = coeff;
        break;
      }
    }    
  }

  //calls function to use fixed point approach to find roots
  evaluateFixedPoint(equation, equationIndex);
}