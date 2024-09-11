#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <sstream>
#include <chrono>

using namespace std;

vector<vector<int>> A, B, R;

// Function to perform matrix multiplication
void matrix_multiplication(int p, int m, int n)
{
    R.resize(m, vector<int>(n, 0)); // Resize R to m x n and initialize with 0
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < p; k++)
            {
                R[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main()
{
    string line;
    int p = 0, m = 0, n = 0;

    // Read first line with dimensions
    if (getline(cin, line)) {
        istringstream iss(line);
        iss >> p >> m >> n;
    }

    // Read matrix A
    A.resize(m, vector<int>(p));
    for (int i = 0; i < m; i++)
    {
        getline(cin, line);
        istringstream iss(line);
        for (int j = 0; j < p; j++)
        {
            iss >> A[i][j];
        }
    }

    // Read empty line
    getline(cin, line); // This assumes there's an empty line

    // Read matrix B
    B.resize(p, vector<int>(n));
    for (int i = 0; i < p; i++)
    {
        getline(cin, line);
        istringstream iss(line);
        for (int j = 0; j < n; j++)
        {
            iss >> B[i][j];
        }
    }
    auto start = chrono::high_resolution_clock::now();
    matrix_multiplication(p, m, n);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Tiempo en segundos: "<< duration.count() << endl;
    
    
    // Print the result matrix R
    /*
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", R[i][j]);
        }
        printf("\n");
    }*/
    
    return 0;
}
