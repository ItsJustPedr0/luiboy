// Peter Julius M. Estacio
// ENGG 27.01
// Homework: Investigation of a Computation for the Square Root
// main.cpp

#include <iostream>
#include <iomanip>

int main()
{
  double operand = 50; // number to be square rooted
  double estimate = operand/2; 
  // estimate starts at half the operand, updates iteratively
  double result;
  int limit = 10; // number of iterations

  for (int i = 0; i < limit; i++)
  {
    result = 0.5*(estimate + (operand/estimate));
    estimate = result;
    std::cout << std::fixed << std::setprecision(10) 
      << result << std::endl; // prints result to 10 places
  }
}
