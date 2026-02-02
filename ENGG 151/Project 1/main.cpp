// De Mesa, Nino Aloysius V.
// Estacio, Peter Julius M. 
// Madariaga, Christian James S.
// ENGG 151.01 - A
// Project 1: Normalized Crosscorrelation
// main.cpp

#include "validIntOrFloat.h"

vector<double> readSignalFile(string fileName)
{
  fstream dataFile(fileName);
  vector<double> signalVector;
  double x_n;
  
  int i = 0;
  int startIndex = 0;
  
  string s1, s2;
  getline(dataFile, s1);
  stringstream sStream(s1);
  sStream >> s2;

  if(is_int(s2, &startIndex) && (sStream >> x_n))
  {
    //cout << "Index read: " << startIndex << endl;
  }
  else 
  {
    //cout << "Index read: 0" << endl;
    is_floating_pt(s2, &x_n);
  }  
  signalVector.push_back(x_n);
  i++;
  
  while (dataFile >> s2)
  {
    if (is_floating_pt(s2, &x_n))
    {
      signalVector.push_back(x_n);
      i++;
    }
  }
  return signalVector;
}

int main()
{
  vector<double> xVector = readSignalFile("xdata");
  vector<double> yVector = readSignalFile("ydata");

  int xDuration = xVector.size();
  int yDuration = yVector.size();

  double xRawSignal[xDuration];
  for (int i = 0; i < xDuration; i++) xRawSignal[i] = xVector[i];
  double yRawSignal[yDuration];
  for (int i = 0; i < yDuration; i++) yRawSignal[i] = yVector[i];
  

  for(int l = -xDuration; l < yDuration - 1; l++)
  {
    double result = 0;
    for(int i = 0; (i < xDuration || i < yDuration); i++)
    {
      double x_n, y_n;
      int index = i - l; 
      if(i >= xDuration || i < 0) x_n = 0;
      else x_n = xRawSignal[i];
      if(index >= yDuration || index < 0) x_n = 0;
      else y_n = yRawSignal[index];

      result += x_n * y_n;
    }

    cout << "r_xy(" << l << ") = " << result << endl; 
  }
  double p_xy = 0;  
}
