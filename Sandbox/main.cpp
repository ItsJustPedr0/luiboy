#include "linkedList.hpp"
#include <iostream>

using namespace std;

int main()
{
  
  LinkedList int1;
  int1.addToHead(1);
  int1.addToTail(2);
  int1.addToTail(3);
  int1.addToTail(4);
  cout << int1.displayInfo();
}