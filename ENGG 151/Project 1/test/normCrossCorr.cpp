// De Mesa, Nino Aloysius V.
// Estacio, Peter Julius M. 
// Madariaga, Christian James S.
// ENGG 151.01 - A
// Project 1: Normalized Crosscorrelation
// normCrossCorr.cpp

#include "normCrossCorr.h"

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

  double x_n;
  duration = 0;
  startIndex = 0;

  string s1, s2, s3, s4;
  getline(dataFile, s1);
  stringstream sStream(s1);
  sStream >> s2;

  if(is_int(s2, &startIndex) && (sStream >> x_n))
  {
    // cout << "Index read: " << startIndex << endl;
  }
  else
  {
    // cout << "Index read: 0" << endl;
    is_floating_pt(s2, &x_n);
  }
  signalVector.push_back(x_n);
  duration++;

  while (!dataFile.eof())
  {
    getline(dataFile, s3);
    stringstream sStream2(s3);
    if (sStream2 >> s4)
    {
      if(is_floating_pt(s4, &x_n))
      {
      signalVector.push_back(x_n);
      duration++;
      }
      else break;
    }
  }
  cout << "Signal file '" << fileName << "' with starting index "
    << startIndex << " and duration " << duration <<" read." << endl;

  double* signalArray = new double[duration];
  for (int i = 0; i <duration; i++) signalArray[i] = signalVector[i];

  return signalArray;
}

void computeCrossCorr(
    double* xRawSignal, int xDuration, int xStartIndex,
    double* yRawSignal, int yDuration, int yStartIndex,
    double* &crossCorrData, int* crossCorrDuration,
    int* crossStartIndex)
{
   double
    x_00 = 0.0,
    y_00 = 0.0,
    x_mean = 0.0,
    y_mean = 0.0,
    x_sum = 0.0,
    y_sum = 0.0;

  for (int i = 0; i < xDuration; i++) x_sum += xRawSignal[i];
  for (int i = 0; i < yDuration; i++) y_sum += yRawSignal[i];

  x_mean = x_sum / xDuration;
  y_mean = y_sum / yDuration;

  double xCenteredSignal[xDuration];
  for (int i = 0; i < xDuration; i++)
  {
    xCenteredSignal[i] = xRawSignal[i] - x_mean;
    x_00 += xCenteredSignal[i] * xCenteredSignal[i];
  }

  double yCenteredSignal[yDuration];
  for (int i = 0; i < yDuration; i++)
  {
    yCenteredSignal[i] = yRawSignal[i] - y_mean;
    y_00 += yCenteredSignal[i] * yCenteredSignal[i];
  }

  double denom = sqrt(x_00 * y_00);

  int relDiff = xStartIndex - yStartIndex;
  int durDiff = xDuration - yDuration + 1;

  *crossCorrDuration = xDuration + yDuration - 1;

  crossCorrData = new double[*crossCorrDuration];
  *crossStartIndex = xStartIndex - (yStartIndex + yDuration - 1);

  for(int l = *crossStartIndex; l < *crossStartIndex + *crossCorrDuration; l++)
  {
    double r_xy = 0.0;
    for(int n = 0; n < xDuration; n++)
    {
      int j = xStartIndex - yStartIndex + n - l;
      double y_val = 0;
      if(j >= 0 && j < yDuration) y_val = yCenteredSignal[j];
      r_xy += xCenteredSignal[n] * y_val;
    }
    crossCorrData[l - *crossStartIndex] = r_xy / denom;
    if(*crossCorrDuration < 20)
    {
      cout << "p_xy(" << l << ") = ";
      cout << crossCorrData[l - *crossStartIndex] << endl;
    }
  }
}
