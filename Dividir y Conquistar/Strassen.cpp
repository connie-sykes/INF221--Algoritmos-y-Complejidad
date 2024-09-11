#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <chrono>

int leafsize;

using namespace std;

void strassen(vector< vector<int> > &A,
              vector< vector<int> > &B,
              vector< vector<int> > &C, unsigned int tam);
unsigned int nextPowerOfTwo(int n);
void strassenR(vector< vector<int> > &A,
              vector< vector<int> > &B,
              vector< vector<int> > &C,
              int tam);
void sum(vector< vector<int> > &A,
         vector< vector<int> > &B,
         vector< vector<int> > &C, int tam);
void subtract(vector< vector<int> > &A,
              vector< vector<int> > &B,
              vector< vector<int> > &C, int tam);

void ikjalgorithm(vector< vector<int> > A,
                                   vector< vector<int> > B,
                                   vector< vector<int> > &C, int n) {
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            for (int j = 0; j < n; j++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void strassenR(vector< vector<int> > &A,
              vector< vector<int> > &B,
              vector< vector<int> > &C, int tam) {
    if (tam <= leafsize) {
        ikjalgorithm(A, B, C, tam);
        return;
    }

    int newTam = tam / 2;
    vector<int> inner(newTam);
    vector< vector<int> >
        a11(newTam, inner), a12(newTam, inner), a21(newTam, inner), a22(newTam, inner),
        b11(newTam, inner), b12(newTam, inner), b21(newTam, inner), b22(newTam, inner),
        c11(newTam, inner), c12(newTam, inner), c21(newTam, inner), c22(newTam, inner),
        p1(newTam, inner), p2(newTam, inner), p3(newTam, inner), p4(newTam, inner),
        p5(newTam, inner), p6(newTam, inner), p7(newTam, inner),
        aResult(newTam, inner), bResult(newTam, inner);

    for (int i = 0; i < newTam; i++) {
        for (int j = 0; j < newTam; j++) {
            a11[i][j] = A[i][j];
            a12[i][j] = A[i][j + newTam];
            a21[i][j] = A[i + newTam][j];
            a22[i][j] = A[i + newTam][j + newTam];

            b11[i][j] = B[i][j];
            b12[i][j] = B[i][j + newTam];
            b21[i][j] = B[i + newTam][j];
            b22[i][j] = B[i + newTam][j + newTam];
        }
    }

    sum(a11, a22, aResult, newTam); 
    sum(b11, b22, bResult, newTam); 
    strassenR(aResult, bResult, p1, newTam);

    sum(a21, a22, aResult, newTam); 
    strassenR(aResult, b11, p2, newTam);

    subtract(b12, b22, bResult, newTam); 
    strassenR(a11, bResult, p3, newTam);

    subtract(b21, b11, bResult, newTam); 
    strassenR(a22, bResult, p4, newTam);

    sum(a11, a12, aResult, newTam); 
    strassenR(aResult, b22, p5, newTam);

    subtract(a21, a11, aResult, newTam); 
    sum(b11, b12, bResult, newTam); 
    strassenR(aResult, bResult, p6, newTam);

    subtract(a12, a22, aResult, newTam); 
    sum(b21, b22, bResult, newTam); 
    strassenR(aResult, bResult, p7, newTam);

    sum(p3, p5, c12, newTam); 
    sum(p2, p4, c21, newTam);

    sum(p1, p4, aResult, newTam); 
    sum(aResult, p7, bResult, newTam); 
    subtract(bResult, p5, c11, newTam);

    sum(p1, p3, aResult, newTam); 
    sum(aResult, p6, bResult, newTam); 
    subtract(bResult, p2, c22, newTam);

    for (int i = 0; i < newTam; i++) {
        for (int j = 0; j < newTam; j++) {
            C[i][j] = c11[i][j];
            C[i][j + newTam] = c12[i][j];
            C[i + newTam][j] = c21[i][j];
            C[i + newTam][j + newTam] = c22[i][j];
        }
    }
}

unsigned int nextPowerOfTwo(int n) {
    return pow(2, int(ceil(log2(n))));
}

void strassen(vector< vector<int> > &A,
              vector< vector<int> > &B,
              vector< vector<int> > &C, unsigned int n) {
    unsigned int m = nextPowerOfTwo(n);
    vector<int> inner(m);
    vector< vector<int> > APrep(m, inner), BPrep(m, inner), CPrep(m, inner);

    for(unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < n; j++) {
            APrep[i][j] = A[i][j];
            BPrep[i][j] = B[i][j];
        }
    }

    strassenR(APrep, BPrep, CPrep, m);
    for(unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < n; j++) {
            C[i][j] = CPrep[i][j];
        }
    }
}

void sum(vector< vector<int> > &A,
         vector< vector<int> > &B,
         vector< vector<int> > &C, int tam) {
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void subtract(vector< vector<int> > &A,
              vector< vector<int> > &B,
              vector< vector<int> > &C, int tam) {
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

void readMatrices(vector< vector<int> > &A, vector< vector<int> > &B, int &n) {
    string line;
    int a;

    // Read matrix A
    for (n = 0; getline(cin, line) && !line.empty(); n++) {
        istringstream iss(line);
        vector<int> row;
        while (iss >> a) {
            row.push_back(a);
        }
        A.push_back(row);
    }

    // Read matrix B
    while (getline(cin, line)) {
        istringstream iss(line);
        vector<int> row;
        while (iss >> a) {
            row.push_back(a);
        }
        B.push_back(row);
    }
}

void writeResults(const vector< vector<int> > &C, int n, const string &filename) {
    string outputFilename = "Strassen sorted " + filename;
    ofstream outFile(outputFilename);
    if (!outFile) {
        cerr << "Error opening output file: " << outputFilename << endl;
        return;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j != 0) {
                outFile << "\t";
            }
            outFile << C[i][j];
        }
        outFile << endl;
    }
    outFile.close();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Uso: " << argv[0] << " nombre < archivo" << endl;
        return 1;
    }

    string filename = argv[1]; // Obtener el nombre del archivo desde los argumentos
    leafsize = 1;

    // Inicializar las matrices
    vector< vector<int> > A, B, C; // No inicializar con tamaño fijo

    // Leer las matrices desde stdin
    int n;
    readMatrices(A, B, n);

    // Asegurarse de que A y B son cuadradas y del mismo tamaño
    if (A.size() != B.size() || A.size() != n) {
        cerr << "Las matrices deben ser del mismo tamaño." << endl;
        return 1;
    }

    C.resize(n, vector<int>(n, 0)); // Inicializar C con el tamaño correcto

    auto start = chrono::high_resolution_clock::now();
    strassen(A, B, C, n);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    cout << "Tiempo en segundos: " << duration.count() << endl;
    writeResults(C, n, filename); // Guardar resultados en el archivo

    return 0;
}
