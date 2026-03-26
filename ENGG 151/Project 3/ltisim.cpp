// Estacio, Peter Julius M.
// Grouped with De Mesa, Nino Aloysius V. 
// and Madariaga, Christian James S.
// ENGG 151.01 - A
// Project 3: Linear Time-Invariant System Simulator
// ltisim.cpp

#include "ltisim.h"

bool is_int(string s, int* value)
{
  string inputString = s;
  stringstream inputStream(inputString);
  int n = 0;
  if(inputStream >> n && inputStream.eof())
  {
    if (value != 0) *value = n;
    return true;
  }
  else
  {
    if (value != 0) *value = 0;
    return false;
  }
}

bool is_floating_pt(string s, double* value)
{
  string inputString = s;
  stringstream inputStream(inputString);
  double n = 0;
  if(inputStream >> n && inputStream.eof())
  {
    if (value != 0) *value = n;
    return true;
  }
  else
  {
    if (value != 0) *value = 0;
    return false;
  }
}

double* readSignalFile(string fileName,int& startIndex,int& duration)
{
  fstream dataFile(fileName);
  vector<double> signalVector;

  if(!dataFile.is_open())
  {
    cout << "ERROR: Could not open " << fileName << endl;
    return 0;
  }

  double x_n = 0.0;
  duration = 0;
  startIndex = 0;

  string s1, s2, s3, s4;

  if (getline(dataFile, s1))
  {
    stringstream sStream(s1);
    if (sStream >> s2)
    {
      string firstSignalString;
      if (is_int(s2, &startIndex) && (sStream >> firstSignalString))
      {
        if (is_floating_pt(firstSignalString, &x_n))
        {
          signalVector.push_back(x_n);
          duration++;
        }
      }
      else
      {
        if (is_floating_pt(s2, &x_n))
        {
          signalVector.push_back(x_n);
          duration++;
        }
      }
    }
  }

  while (getline(dataFile, s3))
  {
    stringstream sStream2(s3);
    if (sStream2 >> s4)
    {
      if(is_floating_pt(s4, &x_n))
      {
        signalVector.push_back(x_n);
        duration++;
      }
    }
  }

  cout << "Signal file '" << fileName << "' with starting index "
    << startIndex << " and duration " << duration <<" read." << endl;

  double* signalArray = new double[duration];
  for (int i = 0; i <duration; i++) signalArray[i] = signalVector[i];

  return signalArray;
}
