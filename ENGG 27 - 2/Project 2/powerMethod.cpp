// Augusto Gabbriel M. Calilung
// Peter Julius M. Estacio
// Rafael Luis Mari R. Lambo
// ENGG 27.01 - M
// Project 2 - Power Method for Eigenvalues and Eigenvectors
// powerMethod.cpp

#include "powerMethod.h"

bool is_int(string s, int* value)
{
  string inputString = s;
  stringstream inputStream(inputString);
  int n = 0;
  if(inputStream >> n && inputStream.eof())
  {
    if (value != 0) *value = n;
    return true;
  }
  else
  {
    if (value != 0) *value = 0;
    return false;
  }
}

bool is_floating_pt(string s, double* value)
{
  string inputString = s;
  stringstream inputStream(inputString);
  double n = 0;
  if(inputStream >> n && inputStream.eof())
  {
    if (value != 0) *value = n;
    return true;
  }
  else
  {
    if (value != 0) *value = 0;
    return false;
  }
}

void readMatrixFile(string* fileName, vector<vector<double>>& matrix, int* size)
{ 
  ifstream inputFile;
  while(true)
  {
    cout << "Please input the name of a matrix file like 'testMatrix': ";
    cin >> *fileName;
    inputFile.open(*fileName);
    if (!inputFile.is_open())
    {
      cout << "Error: Could not open the file named " << *fileName << " Try again."<< endl;
    }
    else
    {
      cout << "Matrix file '" << *fileName <<"' opened successfully." << endl;
      break;
    }
  }

  string firstLine = "";
  int n = 0;

  if (getline(inputFile, firstLine))
  {
    vector<double> tempRow;
    stringstream ss(firstLine);
    string word = "";
    double temp = 0;
    while (ss >> word)
    {
      if (is_floating_pt(word, &temp)) 
      {
        tempRow.push_back(temp);
        n += 1;
      }
      else break;
    }
    matrix.push_back(tempRow);
    *size = n;
  }

  int rowCount = 0;
  if (*size > 0)
  {
    rowCount = 1;
    string extraLine;
    for(rowCount; rowCount < *size; rowCount++)
    {
      vector<double> tempRow;
      getline(inputFile, extraLine);
      stringstream ss(extraLine);
      string word = "";
      double temp = 0;
      for(int j = 0; j < *size; j++)
      {
        ss >> word;
        is_floating_pt(word, &temp);
        tempRow.push_back(temp);
      }
      matrix.push_back(tempRow);
    }
  }
  if (*size == 0)
  {
    cout << "Error: File is empty or invalid." << endl;
  }
  else if (*size == rowCount)
  {
    cout << "Success! Detected a square " << *size << "x" << rowCount << " matrix." << endl;
  }
  else
  {
    cout << "Error: Matrix is not square (Cols: " << *size << ", Rows: " << rowCount << ")." << endl;
    *size = 0;
  }
}

double dotProduct(vector<double> a, vector<double> b, int size)
{
  double result = 0;
  for(int i = 0; i < size; i++) result += a[i] * b[i];
  return result;
}

void calcPowerMethod(const vector<vector<double>> matrix, int size, vector<double>& eigenVector, double& eigenValue)
{
  bool showTrace = false;
  cout << "Display trace of intermediate estimates? (0 for no, 1 for yes): ";
  while(!(cin >> showTrace)) cout << "Invalid input. Try again: ";

  vector<double> testVector(size);

  for (int n = 0; n < size; n++) // for each unit vector
  {
    eigenValue = 0;
    cout << "===========================================" << endl;
    cout << "Test Unit Vector: [";
    for(int n_1 = 0; n_1 < size; n_1++) // initialize unit vector
    {
      if(n_1 == n) testVector[n_1] = 1;
      else testVector[n_1] = 0;

      if(n_1 == size - 1) cout << testVector[n_1] <<"] transpose" << endl;
      else cout << testVector[n_1] <<", ";
    }
    int l = 0;
    bool diverged = false;
    while(true)
    {
      // temp variables
      double t1 = 0;
      double t2 = 0;

      for(int i = 0; i < size; i++) 
      {
        t1 = dotProduct(matrix[i], testVector, size);
        eigenVector[i] = t1; 
        if (abs(t1) > abs(t2)) t2 = t1; // max value is stored in t2
      }
      if (t2 == eigenValue) break;
      else if (isnan(t2) || isinf(t2))
      {
        cout << "Diverged; estimate is inf or is NaN.";
        diverged = true;
      }
      eigenValue = t2; // eigenvalue is assigned as t2 once converged.
      
      for(int j = 0; j < size; j++) eigenVector[j] /= eigenValue; 
      testVector = eigenVector;
      
      if (showTrace == true)
      {
        cout << "-------------------------------------------" << endl;
        cout << "[" << l << "] ";
        cout << "\tEigenvalue = " << setprecision(6) << eigenValue << endl;
        cout << "\tEigenvector: ";
        for (int i = 0; i < eigenVector.size(); i++) cout << eigenVector[i] << "  |  ";
        cout << endl; 
      }
      l++;
    }
    if (diverged == true) break;
    cout << "-------------------------------------------" << endl;
    cout << "Eigenvalues and Eigenvector converged." << endl;
    cout << "-------------------------------------------" << endl;
    cout << setprecision(numeric_limits<double>::max_digits10);
    cout << "Eigenvalue: " << eigenValue << endl;
    cout << "Eigenvector: " << endl;
    for (int j = 0; j < eigenVector.size(); j++) cout << eigenVector[j] / eigenValue << endl;
  }
}