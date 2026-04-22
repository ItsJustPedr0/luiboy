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

void readSignalFile(string fileName, double*& inputSignal, double*& outputSignal, int& startIndex, int& duration)
{
  fstream dataFile(fileName);
  vector<double> signalVector;

  if(!dataFile.is_open())
  {
    cout << "ERROR: Could not open " << fileName << endl;
    return;
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

  double* tempInput = new double[duration+2];
  double* tempOutput = new double[duration+2];
  copy(inputSignal, inputSignal+3, tempInput);
  copy(outputSignal, outputSignal+2, tempOutput);
  for (int i = 0; i < duration; i++) 
  {
    tempInput[i+2] = signalVector[i];
    tempOutput[i+2] = 0;
  }
  delete[] inputSignal;
  inputSignal = tempInput;

  delete[] outputSignal;
  outputSignal = tempOutput;
  
  return;
}

void readSystemFile(string fileName, double*& bCoeff, double*& aCoeff, int& M_plus1, int& N)
{
  fstream dataFile(fileName);
  vector<double> bVector;
  vector<double> aVector;

  if(!dataFile.is_open())
  {
    cout << "ERROR: Could not open " << fileName << endl;
    return;
  }

  string firstLine = "";
  string secondLine = "";
  string currentLine = "";

  getline(dataFile, firstLine);
  stringstream ss1(firstLine);
  string token = "";
  if(ss1 >> token) is_int(token, &M_plus1);

  getline(dataFile, secondLine);
  stringstream ss2(secondLine);
  if(ss2 >> token) is_int(token, &N);

  double tempB;
  for(int b = 0; b < M_plus1; b++)
  {
    getline(dataFile, currentLine);
    stringstream ssb(currentLine);
    if(ssb >> token) if(is_floating_pt(token, &tempB));
    bVector.push_back(tempB);
  }

  double tempA;
  for(int a = 0; a < N+1; a++)
  {
    getline(dataFile, currentLine);
    stringstream ssa(currentLine);
    if(ssa >> token) if(is_floating_pt(token, &tempA));
    aVector.push_back(tempA);
  }

  bCoeff = new double[bVector.size()];
  for(int i = 0; i < bVector.size(); i++) bCoeff[i] = bVector[i];

  aCoeff = new double[aVector.size()];
  for(int j = 0; j < aVector.size(); j++) aCoeff[j] = aVector[j];

  return;
}

double computeLTIOutput(double*& x_n, double*& y_n, double*& bCoeff, double*& aCoeff, int M_plus1, int N)
{
  double outputValue = 0;
  for(int k = 0; k <= N - 1; k++)
  {
    outputValue -= y_n[N-k-1] * aCoeff[k];
    //cout << "a_" << k << ": " << outputValue << endl;
  }
  for(int k = 0; k <= M_plus1 - 1; k++) 
  {
    outputValue += x_n[M_plus1-k] * bCoeff[k];
    //cout << "b_" << k << ": " << outputValue << endl;
  }
  return outputValue;
}