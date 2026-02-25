// Augusto Gabbriel M. Calilung
// Peter Julius M. Estacio
// Rafael Luis Mari R. Lambo
// ENGG 27.01 - M
// Project 2 - Power Method for Eigenvalues and Eigenvectors
// powerMethod.h

#ifndef powerMethod
#define powerMethod

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <limits>
#include <cmath>

using namespace std;

bool is_int(string s, int* value = 0);
bool is_floating_pt(string s, double* value = 0);
void readMatrixFile(string fileName, double*& matrix);
void calcPowerMethod(double* matrix, double*& eigenVector, double*& eigenValue);

#endif
