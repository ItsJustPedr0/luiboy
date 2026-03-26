// Estacio, Peter Julius M.
// Grouped with De Mesa, Nino Aloysius V. 
// and Madariaga, Christian James S.
// ENGG 151.01 - A
// Project 3: Linear Time-Invariant System Simulator
// ltisim.h

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINE
#endif

#ifndef LTISIM
#define LTISIM

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

bool is_int(string s, int* value = 0);
bool is_floating_pt(string s, double* value = 0);
double* readSignalFile(string fileName, int& startIndex, int& duration);


#endif
