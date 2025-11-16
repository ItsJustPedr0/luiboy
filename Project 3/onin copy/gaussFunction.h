//Filename: gaussFunction.h
//Assignment: Project 3: Gauss Elimination
//Name: Peter Estacio
//Grouped with Nino De Mesa and Joshnare Ong
//Section: ENGG 27.01 - M

using namespace std;

#ifndef GAUSS_FUNCTION_H
#define GAUSS_FUNCTION_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

fstream readUserInput();
vector<vector<double>> readMatrixFile(fstream &matrixFile);
void gaussElimination(vector<vector<double>> A);

#endif
