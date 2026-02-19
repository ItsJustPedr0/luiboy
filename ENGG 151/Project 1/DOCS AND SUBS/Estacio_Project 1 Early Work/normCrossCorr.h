// De Mesa, Nino Aloysius V.
// Estacio, Peter Julius M. 
// Madariaga, Christian James S.
// ENGG 151.01 - A
// Project 1: Normalized Crosscorrelation
// normCrossCorr.h

#ifndef normCrossCorr
#define normCrossCorr

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

bool is_int(string s, int* value = 0);
bool is_floating_pt(string s, double* value = 0);
double* readSignalFile(string fileName,int& startIndex,int& duration);
void computeCrossCorr
(
    double* xRawSignal, int xDuration, int xStartIndex,
    double* yRawSignal, int yDuration, int yStartIndex,
    double*& crossCorrData, int* crossCorrDuration, 
	int* crossStartIndex
);

#endif
