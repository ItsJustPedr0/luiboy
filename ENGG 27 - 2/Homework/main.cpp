// Estacio, Peter Julius M. 
// ENGG 151.01 - A
// Project 1: Normalized Crosscorrelation
// main.cpp

#include "validIntOrFloat.h"

int main()
{
  string testS[5] = {"abc", "123", "4.", "5.6a", "7.8e-2"};
  int testI;
  double testD;

  for(int i = 0; i < 5; i++)
  {
    cout << "Test string: " << testS[i] << endl;

    bool Iresult = is_int(testS[i], &testI);
    cout << "Is int?: " << boolalpha << Iresult;
    if (&testI != 0) cout << " | Value stored: " << testI << endl;
    else cout << endl;


    bool Dresult = is_floating_pt(testS[i], &testD);
    cout << "Is double?: " << boolalpha << Dresult;
    if (&testD != 0) cout << " | Value stored: " << testD << endl;
    else cout << endl;
    cout << endl;
  }
}