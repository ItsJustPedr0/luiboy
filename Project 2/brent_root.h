//Filename: brent_root.h
//Assignment: Project 2: Hybrid Root-Finding Approach
//Name: Peter Estacio
//Grouped with Nino De Mesa and Joshnare Ong
//Section: ENGG 27.01 - M
//Description: Header file for the Hybrid Root-Finding Approach (Brent�s Method)

#ifndef BRENT_ROOT_H
#define BRENT_ROOT_H

#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

using namespace std;

// Result struct
struct RootResult
{
  double root = numeric_limits<double>::quiet_NaN();
  double froot = numeric_limits<double>::quiet_NaN();
  int iterations = 0;
  bool converged = false;
};

// Function Declarations
int sigfigs_agreement(double x_new, double x_old);
void print_trace_line(const string& method, double x, double fx, int sig_agree);
RootResult brent_root_find(function<double(double)> f,
  double a, double b,
  double xtol = 1e-12,
  double ftol = 1e-12,
  int max_iter = 200,
  bool trace = false);

#endif
