// De Mesa, Nino Aloysius V.
// Estacio, Peter Julius M. 
// Madariaga, Christian James S.
// ENGG 151.01 - A
// Project 2: Fourier Transform
// main.cpp

#include "dft.h"

int main()
{
  int xDuration = 0; 
  int xStartIndex = 0;
  double* xSignal = readSignalFile("x.signal", xStartIndex, xDuration);
  
  double samplingRate = 32;
  double startFreq = 4;
  double endFreq = 8;
  int nSteps = 8;
  
  double* rectReal = 0;
  double* rectImag = 0;
  double* polarMag = 0;
  double* polarPhase = 0;

  convertFreqToRads(startFreq);
  convertFreqToRads(endFreq);

  computeDFT(xSignal, xDuration, samplingRate, startFreq, endFreq,
    nSteps, rectReal, rectImag, polarMag, polarPhase);
  
  cout << "\nRectangular Results" << endl;
  cout << "===================================" << endl;
  cout << "Frequency (Hz) \t Real Part \t Imaginary Part" << endl;
  for(int i = 0; i < nSteps + 1; i++)
  {
    cout << fixed << setprecision(6);
    double currentFreq = (startFreq + (i * ((endFreq - startFreq)/nSteps)))/2/M_PI;
    cout << currentFreq << " \t";
    cout << rectReal[i] << " \t" << rectImag[i] << endl;
  }

  cout << "\nPolar Results" << endl;
  cout << "===================================" << endl;
  cout << "Frequency (Hz) \t Magnitude \t Phase (Degrees)" << endl;
  for(int i = 0; i < nSteps + 1; i++)
  {
    cout << fixed << setprecision(6);
    double currentFreq = (startFreq + (i * ((endFreq - startFreq)/nSteps)))/2/M_PI;
    cout << currentFreq << " \t";
    cout << polarMag[i] << " \t" << polarPhase[i] << endl;
  }
}