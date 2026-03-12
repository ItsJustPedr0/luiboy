// De Mesa, Nino Aloysius V.
// Estacio, Peter Julius M.
// Madariaga, Christian James S.
// ENGG 151.01 - A
// Project 2: Fourier Transform
// main.cpp

#include "dft.h"

int main(int argc, char *argv[])
{
  if (argc < 6)
  {
    cout << "Format must be: dft signal-file sampling-rate start-freq end-freq nSteps (logfile)" << endl;
    return 0;
  }

  string signalFile = argv[1];
  double samplingRate = stod(argv[2]);
  double startFreq = stod(argv[3]);
  double endFreq = stod(argv[4]);
  int nSteps = stoi(argv[5]);

  string logFile = "";
  ofstream logStream;

  if (argc >= 7)
  {
    logStream.open(argv[6]);

    if (!logStream)
    {
      cout << "ERROR: Cannot open log file." << endl;
    }
  }

  ostream *out = &cout;
  if (logStream.is_open())
    out = &logStream;

  int xDuration = 0;
  int xStartIndex = 0;
  double *xSignal = readSignalFile("x.signal", xStartIndex, xDuration);
  /*
    double samplingRate = 32;
    double startFreq = 4;
    double endFreq = 8;
    int nSteps = 8;
  */
  double *rectReal = 0;
  double *rectImag = 0;
  double *polarMag = 0;
  double *polarPhase = 0;

  convertFreqToRads(startFreq);
  convertFreqToRads(endFreq);

  computeDFT(xSignal, xDuration, samplingRate, startFreq, endFreq,
    nSteps, rectReal, rectImag, polarMag, polarPhase);

  cout << "\nRectangular Results" << endl;
  logStream << "\nRectangular Results" << endl;
  cout << "===================================" << endl;
  logStream << "===================================" << endl;
  cout << "Frequency (Hz) \t Real Part \t Imaginary Part" << endl;
  logStream << "Frequency (Hz) \t Real Part \t Imaginary Part" << endl;
  for (int i = 0; i < nSteps + 1; i++)
  {
    cout << fixed << setprecision(6);
    logStream << fixed << setprecision(6);
    double currentFreq = (startFreq + (i * ((endFreq - startFreq) / nSteps))) / 2 / M_PI;
    cout << currentFreq << " \t";
    logStream << currentFreq << "\t";
    cout << rectReal[i] << " \t" << rectImag[i] << endl;
    logStream << rectReal[i] << "\t" << rectImag[i] << endl;
  }

  cout << "\nPolar Results" << endl;
  logStream << "\nPolar Results" << endl;
  cout << "===================================" << endl;
  logStream << "===================================" << endl;
  cout << "Frequency (Hz) \t Magnitude \t Phase (Degrees)" << endl;
  logStream << "Frequency (Hz) \t Magnitude \t Phase (Degrees)" << endl;

  for (int i = 0; i < nSteps + 1; i++)
  {
    cout << fixed << setprecision(6);
    logStream << fixed << setprecision(6);
    double currentFreq = (startFreq + (i * ((endFreq - startFreq) / nSteps))) / 2 / M_PI;
    cout << currentFreq << " \t";
    logStream << currentFreq << "\t";
    cout << polarMag[i] << " \t" << polarPhase[i] << endl;
    logStream << polarMag[i] << "\t" << polarPhase[i] << endl;
  }
  if (logStream.is_open())
    logStream.close();
}
