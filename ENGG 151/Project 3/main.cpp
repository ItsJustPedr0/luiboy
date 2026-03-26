// Estacio, Peter Julius M.
// Grouped with De Mesa, Nino Aloysius V. 
// and Madariaga, Christian James S.
// ENGG 151.01 - A
// Project 3: Linear Time-Invariant System Simulator
// main.cpp

#include "ltisim.h"

int main(int argc, char* argv[])
{
  if(argc < 2)
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

  if(logStream.is_open()) logStream.close();
}
