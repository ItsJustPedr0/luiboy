// Augusto Gabbriel M. Calilung
// Peter Julius M. Estacio
// Rafael Luis Lambo
// ENGG 27.01 - M
// Project 1 - Fixed-Point Approach for Finding Roots of Polynomials
// main.cpp

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <limits>
#include <cmath>

using namespace std;

int main()
{  
  string fileName; // takes user inut to select a polynomial file
  cout << "Enter filename: "; // if no input, defaults to 'test'
  if(!(cin >> fileName)) fileName = "test"; 
  
  fstream polynomialFile(fileName); 
  if(!polynomialFile.is_open()) //returns error if file fails to open
  {
    cout << "No file." << endl;
    return 0;
  }

  string s; // checks for the POLYNOMIAL token accdg to file format
  if(!(polynomialFile >> s) && s != "POLYNOMIAL")
  {
    cout << "Invalid file, missing header." << endl;
  }
  else cout << "Header is present." << endl;

  int equationIndex; // checks for eqn index accdg to file format
  if(!(polynomialFile >> equationIndex))
  {
    cout << "Invalid file, missing polynomial index" << endl;
  }
  else cout << "Read polynomial of index " << equationIndex << endl;

  // initializes array of coefficients
  double equation[equationIndex+1]; 
  double coeff;

  // stores coefficients in equation array
  for (int i = 0; i < equationIndex + 1; i++)  
  {
    polynomialFile >> coeff;
    equation[i] = coeff;
  }

  // takes user input for initial guess g_0
  cout << "=======================================" << endl;
  cout << "Initial Guess (g_0): ";
  double x, guess;
  cin >> guess;

  // loop for all non-constant coeffs
  for (int i = equationIndex; i > 0; i--) 
  {
    cout << "=======================================" << endl;
    cout << "Showing estimates for i = " << i << ":"<< endl;
    x = guess;

    // limited number of iterations to 100 for testing
    for(int j = 0; j < 100; j++)
    {
      // iterative algorithm for estimating the roots
      double g_x = 0;
      for(int k = equationIndex; k > -1; k--)
      {
        if(k != i) g_x += equation[k]*pow(x, k); 
      }
      g_x /= -equation[i]*pow(x, i-1); 

      // prints results per iteration on separate line
      cout << "x_" << setprecision(6) << j <<" = " << g_x << endl; 

      // sets maximum precision to display converging results
      const int max_precision = numeric_limits<double>::max_digits10;

      // checks for convergence via difference of last two results
      if (g_x - x == 0)
      {
        cout << "Converged. Final result: " 
          << setprecision(max_precision) << x << endl;
        break;
      } 

      //checks for divergence via nan or inf results
      else if (isnan(g_x) == true || isinf(g_x) == true) 
      {
        cout << "Diverged. Iterations stopped." << endl;
        break;;
      }

      // if neither, iterate
      else x = g_x;
    }
  }
  cout << "=======================================" << endl;
}