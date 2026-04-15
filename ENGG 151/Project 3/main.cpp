// Estacio, Peter Julius M.
// Grouped with De Mesa, Nino Aloysius V. 
// and Madariaga, Christian James S.
// ENGG 151.01 - A
// Project 3: Linear Time-Invariant System Simulator
// main.cpp

#include "ltisim.h"

int main(int argc, char* argv[])
{
  int M_plus1 = 0;
  int N = 0;
  double* bCoeff = 0;
  double* aCoeff = 0;
  readSystemFile("lab5.system", bCoeff, aCoeff, M_plus1,N);

  cout << "System coefficients:" << endl;
  for(int i = 0; i < M_plus1; i++) cout << "b(" << i << "): " << bCoeff[i] << endl;
  for(int i = 0; i < N + 1; i++) cout << "a(" << i << "): " << aCoeff[i] << endl;

  int xDuration = 0;
  int xStartIndex = 0;
  double* xSignal = 0;
  double* ySignal = 0;
  readSignalFile("test.txt", xSignal, ySignal, xStartIndex, xDuration);

  cout << "Signal values:" << endl;
  for(int i = 0; i < xDuration; i++)
  { 
    cout << "x(" << i << "): " << xSignal[i] << endl;
    cout << "y(" << i << "): " << ySignal[i] << endl;
  }

/*   if(argc < 2)
  {
    cout << "Invalid input." << endl;
    return 1;
  }

  string userinput = argv[1];
  string logFile = "ltisim-log.txt";
  ofstream logStream;

  if(argc >= 7)
  {
    logFile = argv[2];
  }
  cout << "Log file used: " << logFile << endl;
  logStream.open(logFile, ios::app);
  if(!logStream)
  {
    cout << "ERROR: Cannot open log file." << endl;
  }

  if(logStream.is_open()) logStream.close(); */
}
