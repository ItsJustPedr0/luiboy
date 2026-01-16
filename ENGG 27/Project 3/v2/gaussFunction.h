#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

fstream readUserInput()
{
  string fileName;
  fstream matrixFile;
  while(true)
  {
    getline(cin, fileName);
    if (fileName.empty())
    {
      matrixFile.open("matrix");
      cout << "\nAugmented Matrix read from 'matrix': " << endl; 
      break;
    }
    matrixFile.open(fileName);
    if(!matrixFile.is_open() && !fileName.empty())
    {
      cout << "Error opening " << fileName << ". Please try again (defaults to 'matrix'): ";
    }
    else
    {
      cout << "Augmented Matrix read from '" << fileName << "': " << endl; 
      break;
    }
  }
  return matrixFile;
}

vector<vector<double>> readMatrixFile(fstream matrixFile)
{
  string m;
  int rowNumber = 0;
  int colNumber = 0;

  vector<vector<double>> gaussMatrix;

  while(!matrixFile.eof())
  {
    getline(matrixFile, m);
    istringstream matrixRowStream(m);
    double matrixElement;

    if (colNumber == 0)
    {
      vector<double> currentRow;
      while(matrixRowStream >> matrixElement)
      {
        currentRow.push_back(matrixElement);
        colNumber++;
        cout << matrixElement << " | ";
      }
      gaussMatrix.push_back(currentRow);
      cout << endl;
    }
    else if (rowNumber == colNumber - 1) break;
    else 
    {
      vector<double> currentRow;
      int i = 0;
      for(i; i < colNumber; i++)
      {
        if(!(matrixRowStream >> matrixElement)) break;
        currentRow.push_back(matrixElement);
        cout << matrixElement << " | ";
      }
      if (i < colNumber && i != colNumber - 1) 
      {
        cout << "\nInvalid matrix: lacking coefficients." << endl;
        gaussMatrix.clear();
        return gaussMatrix;
      }
      gaussMatrix.push_back(currentRow);
      cout << endl;
    }
    rowNumber++;
  }
  if (rowNumber < colNumber - 1)
  {
    cout << "Invalid matrix: lacking equations for no. of unknowns." << endl;
    gaussMatrix.clear();
  }
  return gaussMatrix;
}

void gaussElimination(vector<vector<double>> A)
{


  int n = A.capacity() - 1;
  vector<double> x(A.capacity()); 

  for (int k = 0; k < n; k++)
  {
    int m = k;
    for (int j = k + 1; j < n + 1; j++)
    {
      if (abs(A[m][k]) < abs(A[j][k])) m = j;
    }
    if (A[m][k] == 0)
    {
      cout << "No unique solution exists." << endl;
      return;
    }
    else //exchange row k and m 
    {
      vector<double> temp = A[k];
      A[k] = A[m];
      A[m] = temp;
    }
    if (A[n][n] == 0)
    {
      cout << "No unique solution exists." << endl;
      return;
    }
    else
    {
      for(int j = k + 1; j < n + 1; j++)
      {
        double test1 = A[j][k];
        double test2 = A[k][k];
        double m_jk = (A[j][k] / A[k][k]);
        for (int p = k + 1; p < n + 2; p++)
        {
          A[j][p] = A[j][p] - (m_jk * A[k][p]);
        }
      }
    }
  }

  x[n] = (A[n][n+1] / A[n][n]);

  for (int i = (n - 1); i > -1; i--)
  {
    double sum = 0;
    for(int j = i + 1; j < n + 1; j++) sum += A[i][j] * x[j];
    x[i] = (1/A[i][i]) * (A[i][n+1] - sum);
  }
  for (int l = 0; l < x.capacity(); l++) cout << x[l] << endl;
}
