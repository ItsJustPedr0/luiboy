// Augusto Gabbriel M. Calilung
// Peter Julius M. Estacio
// Rafael Luis Mari R. Lambo
// ENGG 27.01 - M
// Project 1 - Fixed-Point Approach for Finding Roots of Polynomials
// fixedPoint.cpp

#include "fixedPoint.h"

bool is_int(string s, int* value)
{
  string inputString = s;
  stringstream inputStream(inputString);
  int n = 0;
  if(inputStream >> n && inputStream.eof())
  {
    if (value != 0) *value = n;
    return true;
  }
  else
  {
    if (value != 0) *value = 0;
    return false;
  }
}

bool is_floating_pt(string s, double* value)
{
  string inputString = s;
  stringstream inputStream(inputString);
  double n = 0;
  if(inputStream >> n && inputStream.eof())
  {
    if (value != 0) *value = n;
    return true;
  }
  else
  {
    if (value != 0) *value = 0;
    return false;
  }
}

void readPolynomialFile(double*& equation, int *equationIndex)
{
  // takes user input to select a polynomial file
  // if no input, defaults to 'test'
  string fileName, s1, s2; 
  fstream polynomialFile;
  cout << "Enter filename (defaults to 'test'): "; 
  while(!polynomialFile.is_open())
  {
    getline(cin, fileName);
    if (fileName.empty()) fileName = "test";
    polynomialFile.open(fileName);
    if (polynomialFile.is_open()) break;
    cout << "No valid file found. Try again: ";
  }

  getline(polynomialFile, s1);
  stringstream firstLine(s1);
  // checks for the POLYNOMIAL token accdg to file format
  if(!(firstLine >> s2) && s2 != "POLYNOMIAL")
  {
    cout << "Invalid file, missing POLYNOMIAL token." << endl;
  }
  else cout << "POLYNOMIAL file is valid." << endl;

  // checks for eqn index accdg to file format
  if(!(polynomialFile >> *equationIndex))
  {
    cout << "Invalid file, missing polynomial index" << endl;
  }
  else cout << "Polynomial of index " 
    << *equationIndex << " read."<< endl;

  // initializes array of coefficients
  equation = new double[*equationIndex+1]; 
  double coeff;

  // stores coefficients in equation array
  for (int i = 0; i < *equationIndex + 1; i++)  
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
}

void evaluateFixedPoint(double* equation, int equationIndex)
{
    // takes user input for initial guess g_0
  cout << "=======================================" << endl;
  cout << "Initial Guess (g_0): ";
  double x, guess;
  string userInput;
  while(cin >> userInput)
  {
    if (is_floating_pt(userInput, &guess) && guess != 0) break;
    else cout << "Invalid guess. Try again: ";
  }

  // loop for all non-constant coeffs
  for (int i = equationIndex; i > 0; i--) 
  {
    cout << "=======================================" << endl;
    cout << "Showing estimates for degree = " << i << ":"<< endl;
    x = guess;
    double g_x = 0;
    bool diverged = false;
    int j = 0;
    // limited number of iterations to 100 for testing
    while(!diverged)
    {
      // prints results per iteration on separate line
      cout << "x_" << setprecision(6) << j <<" = " << x << endl; 
      // iterative algorithm for estimating the roots
      double g_x = 0;
      for(int k = equationIndex; k > -1; k--)
      {
        if(k != i) g_x += equation[k]*pow(x, k); 
      }
      g_x /= -equation[i]*pow(x, i-1); 

      // sets maximum precision to display converging results
      const int max_precision = numeric_limits<double>::max_digits10;

      // checks for convergence via difference of last two results
      if (g_x - x == 0)
      {
        cout << "Converged. Final result: " 
          << setprecision(max_precision) << x << endl;
        break;
      } 
      // if not, iterate
      else x = g_x;
      diverged = (isnan(g_x) == true || isinf(g_x));
      j++;
    }
    if(diverged) cout << "Diverged. Iterations stopped." << endl;
  }
  cout << "=======================================" << endl;
}