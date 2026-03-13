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
      cout << "Error: Could not open the file named " << fileName << " Try again."<< endl;
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
  vector<double> testVector(size);

  for (int n = 0; n < size; n++) // for each unit vector
  {
    cout << "===========================================" << endl;
    cout << "n = " << n << endl;
    cout << "===========================================" << endl;

    for(int n_1 = 0; n_1 < size; n_1++)
    {
      if(n_1 == n) testVector[n_1] = 1;
      else testVector[n_1] = 0;
    }
    int l = 0;
    while(true)
    {
      double t1 = 0;
      double t2 = 0;

      for(int i = 0; i < size; i++) 
      {
        t1 = dotProduct(matrix[i], testVector, size);
        eigenVector[i] = t1;
        if (abs(t1) > abs(t2)) t2 = t1;
      }
      if (t2 == eigenValue) break;
      eigenValue = t2;
      
      //cout << "Eigenvector: ";
      for(int j = 0; j < size; j++) 
      {
        eigenVector[j] /= eigenValue;
        //cout << eigenVector[j] << "\t";
      }
      //cout << endl;
      cout << "For l = " << l << ", eigenvalue = " << eigenValue << endl;
      testVector = eigenVector;
      l++;
    }
  }
}