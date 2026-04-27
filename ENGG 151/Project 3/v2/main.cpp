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
  double* bCoeff = 0;
  double* aCoeff = 0;
  bool systemLoaded = false;
  double* manualX = new double[5000]();
  double* manualY = new double[5000]();
  int manualIdx = 0;

  string logFile = "ltisim-log.txt";
  if (argc >= 2) logFile = argv[1];

  string userInput;
   cout << "Type help for more information " << endl;
  while (true)
  {
    cout << ">";
    if (!getline(cin, userInput)) break;
    if (userInput.empty()) continue;

    stringstream ss(userInput);
    string command;
    ss >> command;

    if (command == "exit")
    {
      return 0;
    }
    else if (command == "help")
    {
      cout << "Available commands:" << endl;
      cout << "  system <filename>  : Load LTI system coefficients from file." << endl;
      cout << "  signal <filename>  : Process a signal file through the current system." << endl;
      cout << "  <number>           : Input a floating-point sample into the system." << endl;
      cout << "  clear              : Reset simulation history to 0.0." << endl;
      cout << "  cls                : Clear the screen." << endl;
      cout << "  exit               : Terminate the application." << endl;
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
      if (!systemLoaded) {
        cout << "ERROR: No LTI system has been defined yet." << endl;
      } else {
        for (int i = 0; i < 5000; i++) {
          manualX[i] = 0.0;
          manualY[i] = 0.0;
        }
        manualIdx = 0;
        ofstream logStream(logFile, ios::app);
        if (logStream) logStream << "clear" << endl;
        cout << "Simulation restarted. Initial conditions cleared." << endl;
      }
    }
    else if (command == "system")
    {
      string filename;
      if (ss >> filename) {
        int tempM, tempN;
        double *tempB = 0, *tempA = 0;

        // Attempt to read the system file using your ltisim function
        readSystemFile(filename, tempB, tempA, tempM, tempN);

        if (tempB != 0 && tempA != 0) {
          // Success: clean up old system and replace
          delete[] bCoeff;
          delete[] aCoeff;
          bCoeff = tempB;
          aCoeff = tempA;
          M_plus1 = tempM;
          N = tempN;
          systemLoaded = true;

          // Clear history memory for new system
          for (int i = 0; i < 5000; i++) { manualX[i] = 0.0; manualY[i] = 0.0; }
          manualIdx = 0;

          // Logging per specification
          ofstream logStream(logFile, ios::app);
          if (logStream) {
            logStream << "new system" << endl;
            logStream << M_plus1 << endl;
            logStream << N << endl;
            for (int i = 0; i < M_plus1; i++) logStream << bCoeff[i] << endl;
            for (int i = 0; i <= N; i++) logStream << aCoeff[i] << endl;
            logStream << "ready" << endl;
          }
          cout << "LTI system successfully obtained from file." << endl;
        } else {
          cout << "ERROR: Could not obtain LTI system from " << filename << endl;
        }
      }
    }
    else if (command == "signal")
    {
      if (!systemLoaded) {
        cout << "ERROR: No LTI system has been defined yet." << endl;
        continue;
      }
      string filename;
      if (ss >> filename) {
        int readDuration = 0;
        int xStartIndex = 0;
        // Temporary signal buffers required by your readSignalFile implementation
        double* sigX = new double[3]{0,0,0};
        double* sigY = new double[2]{0,0};

        readSignalFile(filename, sigX, sigY, xStartIndex, readDuration);

        ofstream logStream(logFile, ios::app);
        for (int i = 0; i < readDuration; i++) {
          double* xPref = sigX + i;
          double* yPref = sigY + i;
          double out = computeLTIOutput(xPref, yPref, bCoeff, aCoeff, M_plus1, N);
          sigY[i+2] = out; // Store output in the buffer for history

          if (logStream) logStream << sigX[i+2] << " \t" << out << endl;

          if (readDuration < 10) {
            cout << "x: " << sigX[i+2] << " \t y: " << out << endl;
          }
        }
        if (readDuration >= 10) {
          cout << "Simulated " << readDuration << " samples." << endl;
        }
        delete[] sigX;
        delete[] sigY;
      }
    }
    else
    {
      // Check if input is a numeric value
      double inputVal;
      if (is_floating_pt(command, &inputVal)) {
        if (!systemLoaded) {
          cout << "ERROR: No LTI system has been defined yet." << endl;
        } else {
          // Add input to manual buffer (offset by 2 as per readSignalFile logic)
          manualX[manualIdx + 2] = inputVal;
          double* xPref = manualX + manualIdx;
          double* yPref = manualY + manualIdx;

          double outputVal = computeLTIOutput(xPref, yPref, bCoeff, aCoeff, M_plus1, N);
          manualY[manualIdx + 2] = outputVal;

          cout << outputVal << endl;

          ofstream logStream(logFile, ios::app);
          if (logStream) logStream << inputVal << " \t" << outputVal << endl;

          manualIdx++;
          // Basic check to prevent buffer overflow in long manual sessions
          if (manualIdx > 4990) manualIdx = 0;
        }
      } else {
        cout << "Invalid command. Type 'help' for info." << endl;
      }
    }
  }
  delete[] bCoeff;
  delete[] aCoeff;
  delete[] manualX;
  delete[] manualY;
}
