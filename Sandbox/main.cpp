#include <iostream>

using namespace std;

int main()
{
  double x_n;
  x_n = -2;
  for (int i = 0; i < 50; i++)
  {
    cout << "Iteration " << i << ": " << x_n << endl;
    x_n = (-5-(4/x_n));
  }
}