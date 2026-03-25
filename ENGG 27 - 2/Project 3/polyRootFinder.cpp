// Augusto Gabbriel M. Calilung
// Peter Julius M. Estacio
// Rafael Luis Mari R. Lambo
// ENGG 27.01 - M
// Project 3 - Roots of Polynomials
// polyRootFinder.cpp

#include "polyRootFinder.h"

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
  else cout << "Polynomial of degree " 
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

void bairstowsMethod(double* eqn, int index)
{
  int n = index - 1;
  double* p_x = eqn;


  while(n > 1)
  {
    double r_0 = - p_x[1] / p_x[2];
    double s_0 = - p_x[0] / p_x[2];
    double dr = 1;
    double ds = 1;

    //factor by synthetic division  
    while (abs(dr) > 1e-10 && abs(ds) > 1e-10) 
    {
      double b[n+2] = {p_x[n+1], r_0 * p_x[n+1] + p_x[n]};
      double c[n+1] = {b[0], r_0 * b[0] + b[1]};
      for(int i = 2; i < n+2; i++)
      {
        b[i] = r_0 * b[i-1] + s_0 * b[i-2] + p_x[n+1-i];
        c[i] = r_0 * c[i-1] + s_0 * c[i-2] + b[i];
      }
      dr = (b[n]*c[n-1]-b[n+1]*c[n-2])/(c[n]*c[n-2]-c[n-1]*c[n-1]);
      ds = (b[n+1]*c[n-1]-b[n]*c[n])/(c[n]*c[n-2]-c[n-1]*c[n-1]);
      r_0 += dr;
      s_0 += ds;
    }
    cout << "Converged. r = " << r_0 << " | s= " << s_0 << endl;
    double q_x[] = {1, -r_0, -s_0};

    //find roots of quadratic
    
    //deflate
    
  }
}

