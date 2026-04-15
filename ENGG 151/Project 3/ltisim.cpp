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

  inputSignal = new double[duration];
  outputSignal = new double[duration];
  for (int i = 0; i < duration; i++) 
  {
    inputSignal[i] = signalVector[i];
    outputSignal[i] = 0;
  }
  return;
}

void readSystemFile(string fileName, double*& bCoeff, double*& aCoeff, int& M_plus1, int& N)
{
  fstream dataFile(fileName);
  vector<double> bVector;
  vector<double> aVector = {0};

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

/* double computeLTIOutput(double* inputValue, double*& bCoeff, double*& aCoeff, int M_plus1, int N, int n)
{

} */