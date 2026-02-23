// De Mesa, Nino Aloysius V.
// Estacio, Peter Julius M. 
// Madariaga, Christian James S.
// ENGG 151.01 - A
// Project 2: Fourier Transform
// dft.h

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#ifndef DFT
#define DFT

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>
#include <cmath>
#include <numbers>

using namespace std;

bool is_int(string s, int* value = 0);
bool is_floating_pt(string s, double* value = 0);
double* readSignalFile(string fileName, int& startIndex, int& duration);
void convertFreqToRads(double& analogFreq);
void computeDFT(
  double* xSignal, int xDuration, double samplingFreq,
  double startFreq, double endFreq, int freqSteps,
  double*& rectReal, double*& rectImag, 
  double*& polarMag, double*& polarPhase);

#endif