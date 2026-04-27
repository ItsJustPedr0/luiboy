// Estacio, Peter Julius M.
// Grouped with De Mesa, Nino Aloysius V.
// and Madariaga, Christian James S.
// ENGG 151.01 - A
// Project 3: Linear Time-Invariant System Simulator
// main.cpp

#include "ltisim.h"

int main(int argc, char* argv[])
{
  int M_plus1 = 0;
  int N = 0;
  double* bCoeff = nullptr;
  double* aCoeff = nullptr;
  bool systemLoaded = false;
  double* stateX = nullptr;
  double* stateY = nullptr;

  string logFile = "ltisim-log.txt";
  if (argc >= 2)
  {
    logFile = argv[1];
  }

  {
    ofstream logTest(logFile, ios::app);
    if (!logTest)
    {
      cout << "WARNING: Could not open log file '"
           << logFile << "'. Logging disabled." << endl;
    }
  }

  string userInput;
  cout << "Type help for more information " << endl;

  while (true)
  {
    cout << ">";
    if (!getline(cin, userInput))
    {
      break;
    }
    if (userInput.empty())
    {
      continue;
    }

    stringstream ss(userInput);
    string command;
    ss >> command;

    if (command == "exit")
    {
      break;
    }

    else if (command == "help")
    {
      cout << "Available commands:" << endl;

      cout << "  system <filename>  : Load LTI system "
           << "coefficients from file." << endl;

      cout << "  signal <filename>  : Process a signal "
           << "file through the current system." << endl;

      cout << "  <number>           : Input a floating-"
           << "point sample into the system." << endl;

      cout << "  clear              : Reset simulation "
           << "history to 0.0." << endl;

      cout << "  cls                : Clear the screen."
           << endl;

      cout << "  exit               : Terminate the "
           << "application." << endl;
    }

    else if (command == "cls")
    {
      #ifdef _WIN32
        system("cls");
      #else
        system("clear");
      #endif
    }

    else if (command == "clear")
    {
      if (!systemLoaded)
      {
        cout << "ERROR: No LTI system has been "
             << "defined yet." << endl;
      }
      else
      {
        for (int i = 0; i < M_plus1; i++)
        {
          stateX[i] = 0.0;
        }
        for (int i = 0; i < N; i++)
        {
          stateY[i] = 0.0;
        }

        ofstream logStream(logFile, ios::app);
        if (logStream)
        {
          logStream << "clear" << endl;
        }
        cout << "Simulation restarted. "
             << "Initial conditions cleared." << endl;
      }
    }

    else if (command == "system")
    {
      string filename;
      if (ss >> filename)
      {
        int tempM, tempN;
        double *tempB = nullptr, *tempA = nullptr;

        readSystemFile(filename, tempB, tempA,
                       tempM, tempN);

        if (tempB != nullptr && tempA != nullptr)
        {
          delete[] bCoeff;
          delete[] aCoeff;
          bCoeff = tempB;
          aCoeff = tempA;
          M_plus1 = tempM;
          N = tempN;
          systemLoaded = true;

          delete[] stateX;
          delete[] stateY;
          stateX = new double[M_plus1]();
          stateY = new double[N]();

          ofstream logStream(logFile, ios::app);
          if (logStream)
          {
            logStream << "new system" << endl;
            logStream << M_plus1 << endl;
            logStream << N << endl;
            for (int i = 0; i < M_plus1; i++)
            {
              logStream << bCoeff[i] << endl;
            }
            for (int i = 0; i < N; i++)
            {
              logStream << aCoeff[i] << endl;
            }
            logStream << "ready" << endl;
          }
          cout << "System obtained from " << filename
               << ". recursive coefs: " << N
               << ", nonrecursive coefs: "
               << M_plus1 << endl;
        }
        else
        {
          cout << "ERROR: Could not obtain LTI system"
               << " from " << filename << endl;
        }
      }
    }

    else if (command == "signal")
    {
      if (!systemLoaded)
      {
        cout << "ERROR: No LTI system has been "
             << "defined yet." << endl;
        continue;
      }
      string filename;
      if (ss >> filename)
      {
        int readDuration = 0;
        int xStartIndex = 0;
        double* sigX = nullptr;
        double* sigY = nullptr;

        readSignalFile(filename, sigX, sigY,
                       xStartIndex, readDuration);

        if (sigX != nullptr)
        {
          ofstream logStream(logFile, ios::app);
          for (int i = 0; i < readDuration; i++)
          {
            double currentInput = sigX[i];

            double out = computeLTIOutput(
              currentInput, bCoeff, aCoeff,
              M_plus1, N, stateX, stateY);

            if (logStream)
            {
              logStream << currentInput
                        << " \t" << out << endl;
            }

            if (readDuration < 10)
            {
              cout << currentInput
                   << " \t" << out << endl;
            }
          }

          if (readDuration >= 10)
          {
            cout << "Simulated " << readDuration
                 << " samples." << endl;
          }
          delete[] sigX;
          delete[] sigY;
        }
      }
    }

    else
    {
      double inputVal;
      if (is_floating_pt(command, &inputVal))
      {
        if (!systemLoaded)
        {
          cout << "ERROR: No LTI system has been "
               << "defined yet." << endl;
        }
        else
        {
          double outputVal = computeLTIOutput(
            inputVal, bCoeff, aCoeff,
            M_plus1, N, stateX, stateY);

          cout << outputVal << endl;

          ofstream logStream(logFile, ios::app);
          if (logStream)
          {
            logStream << inputVal
                      << " \t" << outputVal << endl;
          }
        }
      }
      else
      {
        cout << "Invalid command. Type 'help' "
             << "for info." << endl;
      }
    }
  }

  delete[] bCoeff;
  delete[] aCoeff;
  delete[] stateX;
  delete[] stateY;

  return 0;
}
