#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <sstream>
#include <chrono>

using namespace std;

vector<vector<int>> A, B, R;

// Function to transpose matrix B
vector<vector<int>> transpose(const vector<vector<int>>& matrix, int rows, int cols) {
    vector<vector<int>> transposed(cols, vector<int>(rows));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            transposed[j][i] = matrix[i][j];
        }
    }
    return transposed;
}

// Function to perform matrix multiplication using the transposed matrix B
void matrix_multiplication(int p, int m, int n) {
    R.resize(m, vector<int>(n, 0)); // Resize R to m x n and initialize with 0
    
    // Transpose matrix B
    vector<vector<int>> B_transposed = transpose(B, p, n);
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < p; k++) {
                R[i][j] += A[i][k] * B_transposed[j][k]; // Use the transposed B
            }
        }
    }
}

int main() {
    string line;
    int p = 0, m = 0, n = 0;

    // Read first line with dimensions
    if (getline(cin, line)) {
        istringstream iss(line);
        iss >> p >> m >> n;
    }

    // Read matrix A
    A.resize(m, vector<int>(p));
    for (int i = 0; i < m; i++) {
        getline(cin, line);
        istringstream iss(line);
        for (int j = 0; j < p; j++) {
            iss >> A[i][j];
        }
    }

    // Read empty line
    getline(cin, line); // This assumes there's an empty line

    // Read matrix B
    B.resize(p, vector<int>(n));
    for (int i = 0; i < p; i++) {
        getline(cin, line);
        istringstream iss(line);
        for (int j = 0; j < n; j++) {
            iss >> B[i][j];
        }
    }

    auto start = chrono::high_resolution_clock::now();
    matrix_multiplication(p, m, n);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Tiempo en segundos: " << duration.count() << endl;

    // Write the result matrix R to the output (optional)
    /*
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", R[i][j]);
        }
        printf("\n");
    }*/

    return 0;
}
