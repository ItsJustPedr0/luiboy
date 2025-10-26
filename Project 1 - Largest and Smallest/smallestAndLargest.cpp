// Peter Julius M. Estacio
// ENGG 27.01
// Project 1: Smallest and Largest Numbers
// smallestAndLargest.cpp

#include <iostream>
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