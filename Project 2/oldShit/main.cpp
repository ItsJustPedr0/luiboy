//Filename: main.cpp
//Assignment: Project 2: Hybrid Root-Finding Approach
//Name: Peter Estacio
//Grouped with Niño De Mesa and Osh Ong
//Section: ENGG 27.01 - M
//Description: Main program file for testing the Hybrid Root-Finding Approach

#include "brent_root.h"
#include <vector>

using namespace std;

// ---------- Utility: significant-figures agreement between successive estimates ----------
int sigfigs_agreement(double x_new, double x_old)
{
    if (x_new == x_old)
    {
        return numeric_limits<double>::digits10; // show full available precision
    }

    double scale = max(fabs(x_new), 1.0);
    double d = fabs(x_new - x_old) / scale;
    if (d == 0.0) return numeric_limits<double>::digits10;
    double s = -log10(d);
    int k = static_cast<int>(floor(s));
    return k; // may be <= 0
}

// ---------- Trace printer ----------
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

    oss << ", f(" << scientific << setprecision(6) << x
        << ") = " << scientific << setprecision(6) << fx;

    cout << oss.str() << endl;
}

// ---------- Hybrid root finder (Brent's method) ----------
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
    if (a > b) swap(a, b);

    double fa = f(a), fb = f(b);
    if (!isfinite(fa) || !isfinite(fb)) return R;
    if (fa * fb > 0.0) return R;

    if (fabs(fa) < fabs(fb))
    {
        swap(a, b);
        swap(fa, fb);
    }

    double c = a, fc = fa;
    bool mflag = true;
    double s = b, d = 0.0;
    double prev_x = b;

    for (int iter = 1; iter <= max_iter; ++iter)
    {
        R.iterations = iter;
        string method_used = "bisection method";
        bool used_interpolation = false;
        double s_candidate = s;

        if (fa != fc && fb != fc)
        {
            s_candidate =
                (a * fb * fc) / ((fa - fb) * (fa - fc)) +
                (b * fa * fc) / ((fb - fa) * (fb - fc)) +
                (c * fa * fb) / ((fc - fa) * (fc - fb));
            method_used = "inverse quadratic interpolation";
            used_interpolation = true;
        }
        else
        {
            double denom = (fb - fa);
            if (fabs(denom) > 1e-30)
            {
                s_candidate = b - fb * (b - a) / denom;
                method_used = "secant method";
                used_interpolation = true;
            }
        }

        double cond1 = ((s_candidate < (3 * a + b) / 4.0) || (s_candidate > b));
        double cond2 = (mflag && (fabs(s_candidate - b) >= fabs(b - c) / 2.0));
        double cond3 = (!mflag && (fabs(s_candidate - b) >= fabs(c - d) / 2.0));
        double cond4 = (mflag && (fabs(b - c) < xtol));
        double cond5 = (!mflag && (fabs(c - d) < xtol));
        double cond6 = (!used_interpolation);

        if (cond1 || cond2 || cond3 || cond4 || cond5 || cond6)
        {
            s = (a + b) / 2.0;
            method_used = "bisection method";
            mflag = true;
        }
        else
        {
            s = s_candidate;
            mflag = false;
        }

        double fs = f(s);
        if (!isfinite(fs))
        {
            s = (a + b) / 2.0;
            fs = f(s);
            method_used = "bisection method";
            mflag = true;
        }

        if (trace)
        {
            int agree = sigfigs_agreement(s, prev_x);
            if (s == prev_x)
            {
                cout << "(" << method_used << ") "
                     << scientific << setprecision(numeric_limits<double>::digits10) << s
                     << ", f(" << scientific << setprecision(6) << s
                     << ") = " << scientific << setprecision(6) << fs
                     << endl;
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

        if (fabs(fb) < ftol)
        {
            R.converged = true;
            R.root = b;
            R.froot = fb;
            return R;
        }
        if (fabs(b - prev_x) < xtol)
        {
            R.converged = true;
            R.root = b;
            R.froot = fb;
            return R;
        }
        prev_x = b;
    }

    R.root = b;
    R.froot = fb;
    R.converged = false;
    return R;
}

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
