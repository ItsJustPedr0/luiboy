// De Mesa, Nino Aloysius V.
// Estacio, Peter Julius M. 
// Madariaga, Christian James S.
// ENGG 151.01 - A
// Project 1: Normalized Crosscorrelation
// main.cpp

#include "normCrossCorr.h"

int main(int argc, char* argv[])
{
  if(argc < 3)
  {
    cout << "Invalid argument count." << endl;
    return 0;
  }
  int xStartIndex, yStartIndex;
  int xDuration, yDuration;

  double* xRawSignal = readSignalFile(argv[1],xStartIndex,xDuration);
  double* yRawSignal = readSignalFile(argv[2],yStartIndex,yDuration);
  double* finalResult;
  int crossCorrDuration, crossStartIndex;
  string fileName = argv[3];

  computeCrossCorr(xRawSignal, xDuration, xStartIndex,
    yRawSignal, yDuration, yStartIndex, 
    finalResult, &crossCorrDuration, &crossStartIndex);

  ofstream outFile(fileName);
  if (!outFile.is_open())
  {
    cout << "Error: Could not open ";
    cout << fileName <<" for writing." << endl;
    return 0;
  }
  outFile << crossStartIndex << "\t";
  for (int i=crossStartIndex;i<crossStartIndex+crossCorrDuration;i++)
  {
    outFile << finalResult[i] << endl;
  }
  cout << "Exported crosscorrelation signal to " << fileName 
    <<" with start index " << crossStartIndex 
    << " and duration " << crossCorrDuration <<"." << endl;
  outFile.close();  
}
