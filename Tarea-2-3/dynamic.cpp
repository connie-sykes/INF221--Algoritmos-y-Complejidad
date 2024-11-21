#include <bits/stdc++.h>
using namespace std;
string s1,s2;

vector<vector<int>> m_sub(26, vector<int>(26));
vector<int> m_ins(26);
vector<int> m_del(26);
vector<vector<int>> m_tra(26, vector<int>(26));
vector<vector<int>> m_costos;
int n,m;

int costo_sub(char a, char b){
    return m_sub[a-97][b-97];
}
int costo_del(char a){
    return m_del[a-97];
}
int costo_ins(char a){
    return m_ins[a-97];
}
int costo_tras(char a, char b){
    return m_tra[a-97][b-97];
}

int Distancia(){

    // Inicializar la primera fila y columna
    for (int i = 0; i <= n; ++i) {
        m_costos[i][0] = i > 0 ? costo_del(s1[i - 1]) + m_costos[i - 1][0] : 0; // Costo de eliminar caracteres de s1
    }
    for (int j = 0; j <= m; ++j) {
        m_costos[0][j] = j > 0 ? costo_ins(s2[j - 1]) + m_costos[0][j - 1] : 0; // Costo de insertar caracteres de s2
    }

    // Llenar la matriz
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int insertion_cost = costo_ins(s2[j - 1]) + m_costos[i][j - 1]; // Costo de inserción
            int deletion_cost = costo_del(s1[i - 1]) + m_costos[i - 1][j]; // Costo de eliminación
            int substitution_cost = costo_sub(s1[i - 1], s2[j - 1]) + m_costos[i - 1][j - 1]; // Costo de sustitución

            m_costos[i][j] = min({insertion_cost, deletion_cost, substitution_cost});

            // Costo de transposición
            if (i > 1 && j > 1 && s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1]) {
                int transposition_cost = costo_tras(s1[i - 1], s2[j - 2]) + m_costos[i - 2][j - 2];
                m_costos[i][j] = min(m_costos[i][j], transposition_cost); // Actualizar si la transposición es menor
            }
        }
    }

    return m_costos[n][m]; // Retorna la distancia mínima de edición
}

int main(int argc, char* argv[]){
    //Process block
    vector<string> strings1, strings2; 

    ifstream inputFile("cadenas.txt");
    if (!inputFile.is_open()) {
        cerr << "Error al abrir el archivo: cadenas.txt" << endl;
        return 1;
    }
    // Leer las primeras dos líneas
    getline(inputFile, s1);
    getline(inputFile, s2);
    inputFile.close();

    ifstream costInsertFile(argv[2]);
    if (costInsertFile.is_open()) {
        for (int i = 0; i < 26; ++i) {
            costInsertFile >> m_ins[i];
        }
        costInsertFile.close();
    } else {
        cerr << "Error al abrir el archivo: " << argv[2] << endl;
        return 1;
    }

    ifstream costDeleteFile(argv[3]);
    if (costDeleteFile.is_open()) {
        for (int i = 0; i < 26; ++i) {
            costDeleteFile >> m_del[i];
        }
        costDeleteFile.close();
    } else {
        cerr << "Error al abrir el archivo: " << argv[3] << endl;
        return 1;
    }

    ifstream costReplaceFile(argv[4]);
    if (costReplaceFile.is_open()) {
        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < 26; ++j) {
                costReplaceFile >> m_sub[i][j];
            }
        }
        costReplaceFile.close();
    } else {
        cerr << "Error al abrir el archivo: " << argv[4] << endl;
        return 1;
    }
    
    ifstream costTransposeFile(argv[5]);
    if (costTransposeFile.is_open()) {
        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < 26; ++j) {
                costTransposeFile >> m_tra[i][j];
            }
        }
        costTransposeFile.close();
    } else {
        cerr << "Error al abrir el archivo: " << argv[5] << endl;
        return 1;
    }

        cout << "String 1: " << s1 << "\n";
        cout << "String 2: " << s2 << "\n";

        n = s1.length();
        m = s2.length();
        m_costos.resize(n + 1, vector<int>(m + 1,0));
        

        auto start = chrono::high_resolution_clock::now();
        int distancia = Distancia();
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;

        cout << "El costo mínimo de edición es: " << distancia << "\n";
        cout << "Tiempo de ejecución: " << duration.count() << " segundos.\n\n";
    
    return 0;
}