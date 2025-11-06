// Filename: main.cpp
// Assignment: Project 2: Hybrid Root-Finding Approach
// Name: Peter Estacio
// Grouped with Nino De Mesa and Joshnare Ong
// Section: ENGG 27.01 - M
// Description: Main program file for testing the Hybrid Root-Finding Approach

#include "brent_root.cpp"
#include <vector>
#include <limits>

using namespace std;

// ---------- Safe numeric input helpers ----------
template <typename T>
bool read_number(const string& prompt, T& out)
{
  cout << prompt;
  if (!(cin >> out))
  {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return false;
  }
  return true;
}

bool ask_yes_no(const string& prompt)
{
  while (true)
  {
    cout << prompt << " (y/n): ";
    string s;
    if (!(cin >> s))
    {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      continue;
    }
    if (s == "y" || s == "Y") return true;
    if (s == "n" || s == "N") return false;
    cout << "Please answer y or n." << endl;
  }
}

// ---------- Demo CLI ----------
int main()
{
  struct FnItem
  {
    string name;
    function<double(double)> f;
  };
  vector<FnItem> funcs = {
    {"f(x) = x^3 - x - 2", [](double x){ return x*x*x - x - 2.0; }},
    {"f(x) = cos(x) - x", [](double x){ return cos(x) - x; }},
    {"f(x) = e^(-x) - x", [](double x){ return exp(-x) - x; }},
    {"f(x) = x*sin(x) - 1", [](double x){ return x*sin(x) - 1.0; }},
    {"f(x) = (x-1)*(x-1)*(x-1)", [](double x){ return (x-1)*(x-1)*(x-1); }}
  };

  while (true)
  {
    cout << endl << "=== Hybrid Root Finder (Brent) ===" << endl;
    for (size_t i = 0; i < funcs.size(); ++i)
    {
      cout << "  " << (i + 1) << ") " << funcs[i].name << endl;
    }
    cout << "  0) Exit" << endl;

    int choice = -1;
    if (!read_number("Choose a function [0-" + to_string(funcs.size()) + "]: ", choice)
        || choice < 0 || choice > static_cast<int>(funcs.size()))
    {
      cout << "Invalid choice." << endl;
      if (ask_yes_no("Would you like to choose again?"))
        continue;
      else
        return 0;
    }

    if (choice == 0) return 0;

    auto f = funcs[static_cast<size_t>(choice - 1)].f;
    cout << "You chose: " << funcs[static_cast<size_t>(choice - 1)].name << endl;

    double a = 0.0, b = 0.0;
    if (!read_number("Enter a (left endpoint): ", a))
    {
      cout << "Input error for a." << endl;
      if (ask_yes_no("Would you like to choose again?"))
        continue;
      else
        return 0;
    }
    if (!read_number("Enter b (right endpoint): ", b))
    {
      cout << "Input error for b." << endl;
      if (ask_yes_no("Would you like to choose again?"))
        continue;
      else
        return 0;
    }
    if (a == b)
    {
      cout << "a and b must be different." << endl;
      if (ask_yes_no("Would you like to choose again?"))
        continue;
      else
        return 0;
    }

    if (a > b) swap(a, b);
    double fa = f(a), fb = f(b);
    if (!isfinite(fa) || !isfinite(fb) || fa * fb > 0.0)
    {
      cout << "The interval [" << a << ", " << b << "] does NOT bracket a root "
           << "(f(a) and f(b) must have opposite signs)." << endl;
      if (ask_yes_no("Would you like to choose again?"))
        continue;
      else
        return 0;
    }

    bool trace = ask_yes_no("Enable step-by-step TRACE output?");
    double xtol = 1e-12, ftol = 1e-12;
    int max_iter = 200;

    cout << endl << "Solving with Brent's method..." << endl;
    RootResult R = brent_root_find(f, a, b, xtol, ftol, max_iter, trace);

    cout << endl << "=== Result ===" << endl;
    cout << "Converged: " << (R.converged ? "yes" : "no") << endl;
    cout << "Root     : " << scientific
         << setprecision(numeric_limits<double>::digits10) << R.root << endl;
    cout << "f(root)  : " << scientific << setprecision(6) << R.froot << endl;
    cout << "Iterations: " << R.iterations << endl;

    if (!ask_yes_no("Would you like to choose again?")) break;
  }

  return 0;
}
