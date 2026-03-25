// Augusto Gabbriel M. Calilung
// Peter Julius M. Estacio
// Rafael Luis Mari R. Lambo
// ENGG 27.01 - M
// Project 3 - Roots of Polynomials
// polyRootFinder.h

#ifndef powerMethod
#define powerMethod

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <limits>
#include <cmath>
#include <sstream>

using namespace std;

bool is_int(string s, int* value = 0);
bool is_floating_pt(string s, double* value = 0);
void readPolynomialFile(double*& equation, int* equationIndex);
void bairstowsMethod(double* eqn, int index);

#endif
