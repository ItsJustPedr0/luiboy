// Peter Julius M. Estacio
// ENGG 27.01
// Project 1: Smallest and Largest Numbers
// main.cpp

#include <iostream>
#include <iomanip>
#include <cmath>

double computeLargestNumber()
{
  double result;
  double mantissa;
  double mantissaExponent = 1;
  double exponent = 1;
  
  while(std::isinf(exponent *2) != true) exponent *= 2;
  while(std::isinf((2 - (mantissaExponent / 2)) * exponent) != true)
    mantissaExponent /= 2;
  
  mantissa = 2 - mantissaExponent;
  return result = mantissa * exponent;
}

double computeSmallestNumber()
{
  double result = 1;
  while ((result/ 2) != 0) result /= 2;
  return result;
}

int main()
{
  double largestNumber = computeLargestNumber();
  
  std::cout << "The largest positive number stored in a double is: "
    << std::setprecision (std::numeric_limits<double>::digits10) 
    << largestNumber << std::endl;  

  std::cout 
    << "Difference between found largest number and numeric limit: "
    << (std::numeric_limits<double>::max() - largestNumber) 
    << std::endl;

  std::cout 
    << "Are they equal?: " << std::boolalpha
    << (std::numeric_limits<double>::max() == largestNumber) 
    << std::endl;

  double smallestNumber = computeSmallestNumber();
  std::cout << "\nThe smallest positive number stored in a double is: "
    << std::setprecision (std::numeric_limits<double>::digits10) 
    << smallestNumber << std::endl;

  std::cout 
    << "Difference between found smallest number and numeric limit: "
    << (smallestNumber - std::numeric_limits<double>::denorm_min()) 
    << std::endl;

  std::cout 
    << "Are they equal?: " << std::boolalpha
    << (smallestNumber == std::numeric_limits<double>::denorm_min()) 
    << std::endl;
}