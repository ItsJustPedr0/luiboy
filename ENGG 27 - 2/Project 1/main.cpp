#include <iostream>
#include <fstream>
#include <vector>

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
  while (i > -1)
  {
    cout << equation[i];
    if (i > 0) cout << "x^" << i << " + ";
    i--;
  }
}