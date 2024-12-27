#include <iostream>
#include <vector>
using namespace std;

void printMatrix(const vector<vector<double>> &matrix) {
  for (size_t i = 0; i < matrix.size(); i++) {
    for (size_t j = 0; j < matrix[i].size(); j++) {
      cout << matrix[i][j] << "\t";
    }
    cout << endl;
  }
}

void calculateInverse(vector<vector<double>> &matrix) {
  // Check if the matrix is square (nxn)
  size_t n = matrix.size();
  if (n != matrix[0].size()) {
    cout << "Matrix must be square (nxn) for inversion." << endl;
    return;
  }

  vector<vector<double>> augmentedMatrix(n, vector<double>(2 * n, 0.0));

  // Initialize the augmented matrix with [A | I]
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      augmentedMatrix[i][j] = matrix[i][j];
      augmentedMatrix[i][j + n] = (i == j) ? 1.0 : 0.0; // Identity matrix
    }
  }

  // Implement Gauss-Jordan elimination to find the inverse
  for (size_t i = 0; i < n; i++) {
    // Make the diagonal element 1
    double pivot = augmentedMatrix[i][i];
    for (size_t j = 0; j < 2 * n; j++) {
      augmentedMatrix[i][j] /= pivot;
    }
    // Eliminate other rows
    for (size_t k = 0; k < n; k++) {
      if (k != i) {
        double factor = augmentedMatrix[k][i];
        for (size_t j = 0; j < 2 * n; j++) {
          augmentedMatrix[k][j] -= factor * augmentedMatrix[i][j];
        }
      }
    }
  }

  // Extract the inverse matrix
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      matrix[i][j] = augmentedMatrix[i][j + n];
    }
  }
}

int main() {
  int x;
  cout << "Enter Size of Matrix (nxn): ";
  cin >> x;

  vector<vector<double>> a(x, vector<double>(x, 0.0));

  cout << "Enter Elements the of Matrix (" << x << "x" << x << "):" << endl;

  for (int i = 0; i < x; i++) {
    for (int j = 0; j < x; j++) {
      cin >> a[i][j];
    }
  }

  // Calculate the inverse
  calculateInverse(a);

  // Print the inverse matrix
  cout << "Inverse Matrix:" << endl;
  printMatrix(a);

  return 0;
}
