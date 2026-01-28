// De Mesa, Nino Aloysius V.
// Estacio, Peter Julius M. 
// Madariaga, Christian James S.
// ENGG 151.01 - A
// Project 1: Normalized Crosscorrelation
// main.cpp

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<double> readSignalFile(string fileName)
{
  fstream xDataFile(fileName);
  vector<double> signal;
  double x_n;
  int i = -1;
  while (xDataFile >> x_n)
  {
    vector<double>::iterator start = signal.begin();  
    signal.push_back(x_n);
    i++;
  }
  return signal;
}

int main()
{
  vector<double> signalX = readSignalFile("xdata");
  vector<double> signalY = readSignalFile("ydata");

  int signalXSize = signalX.size();
  int signalYSize = signalY.size();

  double result;

  for(int i = 0; (i < signalXSize || i < signalYSize); i++)
  {
    double x_n, y_n;

    if(i >= signalXSize || i < 0) x_n = 0;
    else x_n = signalX[i];
    if(i >= signalYSize || i < 0) x_n = 0;
    else y_n = signalY[i];

    result += x_n * y_n;
  }

  cout << "r_xy(0) = " << result; 
}
