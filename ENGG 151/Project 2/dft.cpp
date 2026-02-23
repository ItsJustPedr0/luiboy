// De Mesa, Nino Aloysius V.
// Estacio, Peter Julius M. 
// Madariaga, Christian James S.
// ENGG 151.01 - A
// Project 2: Fourier Transform
// dft.cpp

#include "dft.h"

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

void convertFreqToRads(double& inputFreq)
{
  inputFreq = inputFreq * 2 * M_PI;
}

void computeDFT(
  double* xSignal, int xDuration, double samplingFreq,
  double startFreq, double endFreq, int freqSteps,
  double*& rectReal, double*& rectImag, 
  double*& polarMag, double*& polarPhase)
{
  rectReal = new double[freqSteps+1];
  rectImag = new double[freqSteps+1];
  polarMag = new double[freqSteps+1];
  polarPhase = new double[freqSteps+1];
 
  for(int i = 0; i < freqSteps + 1; i++)
  {
    rectReal[i] = 0;
    rectImag[i] = 0;
    polarMag[i] = 0;
    polarPhase[i] = 0;
    double currentFreq = startFreq + (i * ((endFreq - startFreq)/freqSteps));
    for(int k = 0; k < xDuration; k++)
    {
      double digitalFreq = currentFreq / samplingFreq;

      rectReal[i] += xSignal[k] * cos(digitalFreq * k);
      rectImag[i] -= xSignal[k] * sin(digitalFreq * k);
    }
    if(abs(rectReal[i]) < 1e-08) rectReal[i] = 0;

    polarMag[i] = hypot(rectReal[i], rectImag[i]);
    polarPhase[i] = atan2(rectImag[i], rectReal[i]) * 180 / M_PI;
  }
}