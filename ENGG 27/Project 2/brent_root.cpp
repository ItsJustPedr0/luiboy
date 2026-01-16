// Filename: brent_root.cpp
// Assignment: Project 2: Hybrid Root-Finding Approach
// Name: Peter Estacio
// Grouped with Nino De Mesa and Joshnare Ong
// Section: ENGG 27.01 - M
// Description: Implementation file for Brent's Hybrid Root-Finding Method

#include "brent_root.h"

//Significant Figures Agreement
int sigfigs_agreement(double x_new, double x_old)
{
  if (x_new == x_old)
    return numeric_limits<double>::digits10; // full precision

  double scale = max(fabs(x_new), 1.0);
  double d = fabs(x_new - x_old) / scale;
  if (d == 0.0) return numeric_limits<double>::digits10;
  double s = -log10(d);
  int k = static_cast<int>(floor(s));
  return k; // may be <= 0
}

//Trace Printer
void print_trace_line(const string& method, double x, double fx, int sig_agree)
{
  ostringstream oss;

  if (sig_agree > 0)
  {
    ostringstream fmt;
    fmt.setf(ios::fmtflags(0), ios::floatfield);
    fmt << scientific << setprecision(sig_agree) << x;
    oss << "(" << method << ") " << fmt.str();
  }
  else
  {
    oss << "(" << method << ") " << scientific
        << setprecision(15) << x;
  }

  oss << ", f(" << scientific << setprecision(5) << x
      << ") = " << scientific << setprecision(5) << fx;

  cout << oss.str() << endl;
}

//Brent's Root-Finding Implementation
RootResult brent_root_find(function<double(double)> f,
  double a, double b,
  double xtol,
  double ftol,
  int max_iter,
  bool trace)
{
   RootResult R;

  if (!(xtol > 0)) xtol = 1e-12;
  if (!(ftol > 0)) ftol = 1e-12;
  if (max_iter <= 0) max_iter = 200;
  if (a == b) return R;
  if (a > b) swap(a, b);

  double fa = f(a);
  double fb = f(b);
  if (!isfinite(fa) || !isfinite(fb)) return R;
  if (fa * fb > 0.0) return R; // root not bracketed

  if (fabs(fa) < fabs(fb))
  {
    swap(a, b);
    swap(fa, fb);
  }

  double c = a;
  double fc = fa;
  double s = b;
  double fs = fb;
  double prev_b = b;
  bool mflag = true;
  double d = 0.0;

  for (int iter = 1; iter <= max_iter; ++iter)
  {
    R.iterations = iter;

    if (fabs(fb) <= ftol)
    {
      R.converged = true;
      R.root = b;
      R.froot = fb;
      return R;
    }

    if (fabs(b - a) <= xtol)
    {
      R.converged = true;
      R.root = b;
      R.froot = fb;
      return R;
    }

    double s_candidate = b;
    bool used_interp = false;
    string method_used = "bisection method";

    if (fa != fc && fb != fc)
    {
      s_candidate =
        (a * fb * fc) / ((fa - fb) * (fa - fc)) +
        (b * fa * fc) / ((fb - fa) * (fb - fc)) +
        (c * fa * fb) / ((fc - fa) * (fc - fb));
      used_interp = true;
      method_used = "inverse quadratic interpolation";
    }
    else
    {
      double denom = fb - fa;
      if (fabs(denom) > 1e-30)
      {
        s_candidate = b - fb * (b - a) / denom;
        used_interp = true;
        method_used = "secant method";
      }
    }
    bool cond1 = (s_candidate < (3.0 * a + b) / 4.0) || (s_candidate > b);
    bool cond2 = (mflag && (fabs(s_candidate - b) >= fabs(b - c) / 2.0));
    bool cond3 = (!mflag && (fabs(s_candidate - b) >= fabs(c - d) / 2.0));
    bool cond4 = (mflag && (fabs(b - c) < xtol));
    bool cond5 = (!mflag && (fabs(c - d) < xtol));
    bool cond6 = !used_interp;

    if (cond1 || cond2 || cond3 || cond4 || cond5 || cond6)
    {
      s = 0.5 * (a + b);
      method_used = "bisection method";
      mflag = true;
    }
    else
    {
      s = s_candidate;
      mflag = false;
    }

    fs = f(s);
    if (!isfinite(fs))
    {
      s = 0.5 * (a + b);
      fs = f(s);
      method_used = "bisection method";
      mflag = true;
    }

    if (trace)
    {
      int agree = sigfigs_agreement(s, prev_b);
      if (s == prev_b)
      {
        cout << "(" << method_used << ") "
             << scientific << setprecision(numeric_limits<double>::digits10) << s
             << ", f(" << scientific << setprecision(7) << s
             << ") = " << scientific << setprecision(7) << fs << endl;
      }
      else
      {
        print_trace_line(method_used, s, fs, agree);
      }
    }

    d = c;
    c = b;
    fc = fb;

    if (fa * fs < 0.0)
    {
      b = s;
      fb = fs;
    }
    else
    {
      a = s;
      fa = fs;
    }

    if (fabs(fa) < fabs(fb))
    {
      swap(a, b);
      swap(fa, fb);
    }

    prev_b = b;
  }

  R.root = b;
  R.froot = fb;
  R.converged = false;
  return R;
}

