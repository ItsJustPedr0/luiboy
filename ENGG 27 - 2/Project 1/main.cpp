// Peter Julius M. Estacio
// ENGG 27.01 - M
// Project 1 - Fixed-Point Approach for Finding Roots of Polynomials
// main.cpp

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

int main()
{  
  string fileName = "test";
  // cin >> fileName;

  fstream polynomialFile(fileName);
  vector<double> equation;
  double coeff;
  int i = -1;
  while (polynomialFile >> coeff)
  {
    vector<double>::iterator start = equation.begin();  
    equation.insert(start, coeff);
    i++;
  }
  cout << "=======================================" << endl;
  cout << "Initial Guess (g_0): ";
  double x, guess;
  cin >> guess;
  for (i; i > 0; i--)
  {
    cout << "=======================================" << endl;
    cout << "Showing estimates for i = " << i << ":"<< endl;
    x = guess;
    for(int j = 1; j < 50; j++)
    {
      double g_x = 0;
      for(int k = equation.size() - 1; k > -1; k--)
      {
        if(k != i) g_x += equation[k]*pow(x, k); 
      }
      g_x /= -equation[i]*pow(x, i-1); 
      cout << "x_" << j <<" = " << g_x << endl; 
      
      if (g_x - x == 0)
      {
        cout << "Converged." << endl;
        break;
      } 
      else if (isnan(g_x) == true || isinf(g_x) == true) 
      {
        cout << "Diverged." << endl;
        break;;
      }
      else x = g_x;
    }
  }
  cout << "=======================================" << endl;
}