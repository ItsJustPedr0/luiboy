// De Mesa, Nino Aloysius V.
// Estacio, Peter Julius M.
// Madariaga, Christian James S.
// ENGG 151.01 - A
// Project 2: Fourier Transform
// main.cpp

#include "dft.h"

int main(int argc, char* argv[])
{
  if(argc < 6)
  {
    cout << "Format must be: ./dft signal-file sampling-rate start-freq end-freq nSteps (logfile)" << endl;
    return 1;
  }

  string signalFile = argv[1];
  double samplingRate = stod(argv[2]);
  double startFreq = stod(argv[3]);
  double endFreq = stod(argv[4]);
  int nSteps = stoi(argv[5]);

  string logFile = "dftlog.txt";
  ofstream logStream;

  if(argc >= 7)
  {
    logFile = argv[6];
  }
  cout << "Log file used: " << logFile << endl;
  logStream.open(logFile, ios::app);
  if(!logStream)
  {
    cout << "ERROR: Cannot open log file." << endl;
  }

  ostream* out = &cout;
  if(logStream.is_open()) out = &logStream;

  int xDuration = 0;
  int xStartIndex = 0;
  double* xSignal = readSignalFile(signalFile, xStartIndex, xDuration);
  double* rectReal = 0;
  double* rectImag = 0;
  double* polarMag = 0;
  double* polarPhase = 0;


  convertFreqToRads(startFreq);
  convertFreqToRads(endFreq);

  computeDFT(xSignal, xDuration, samplingRate, startFreq, endFreq,
    nSteps, rectReal, rectImag, polarMag, polarPhase);


  logStream << "\nRectangular Results" << endl;
  logStream << "===================================" << endl;
  logStream << "Frequency (Hz) \t Real Part \t Imaginary Part" << endl;
  if(nSteps < 10)
  {
    cout << "\nRectangular Results" << endl;
    cout << "===================================" << endl;
    cout << "Frequency (Hz) \t Real Part \t Imaginary Part" << endl;
  }

  for(int i = 0; i < nSteps + 1; i++)
  {

    logStream << fixed << setprecision(6);
    double currentFreq = (startFreq + (i * ((endFreq - startFreq)/nSteps)))/2/M_PI;
    logStream << currentFreq << "\t";
    logStream<< rectReal[i] << "\t" << rectImag[i] << endl;
    if(nSteps < 10)
    {
      cout << fixed << setprecision(6);
      cout << currentFreq << " \t";
      cout << rectReal[i] << " \t" << rectImag[i] << endl;
    }
  }

  logStream << "\nPolar Results" << endl;
  logStream << "===================================" << endl;
  logStream << "Frequency (Hz) \t Magnitude \t Phase (Degrees)" << endl;
  if(nSteps < 10)
  {
    cout << "\nPolar Results" << endl;
    cout << "===================================" << endl;
    cout << "Frequency (Hz) \t Magnitude \t Phase (Degrees)" << endl;
  }


  for(int i = 0; i < nSteps + 1; i++)
  {

    logStream << fixed << setprecision(6);
    double currentFreq = (startFreq + (i * ((endFreq - startFreq)/nSteps)))/2/M_PI;
    logStream << currentFreq << "\t";
    logStream<< polarMag[i] << "\t" << polarPhase[i] << endl;

    if(nSteps < 10)
    {
    cout << fixed << setprecision(6);
    cout << currentFreq << " \t";
    cout << polarMag[i] << " \t" << polarPhase[i] << endl;
    }
  }
  if(logStream.is_open()) logStream.close();
}
