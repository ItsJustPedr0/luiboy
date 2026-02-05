// Augusto Gabbriel M. Calilung
// Peter Julius M. Estacio
// Rafael Luis Mari R. Lambo
// ENGG 27.01 - M
// Project 1 - Fixed-Point Approach for Finding Roots of Polynomials
// fixedPoint.h

#ifndef fixedPoint
#define fixedPoint

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <limits>
#include <cmath>

using namespace std;

bool is_int(string s, int* value = 0);
bool is_floating_pt(string s, double* value = 0);

fstream readPolynomialFile();

void evaluateFixedPoint(double* equation, int equationIndex);

#endif