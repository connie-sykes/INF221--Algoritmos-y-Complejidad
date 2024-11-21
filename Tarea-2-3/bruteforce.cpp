#include <bits/stdc++.h>
using namespace std;
string s1,s2;

vector<vector<int>> m_sub(26, vector<int>(26));
vector<int> m_ins(26);
vector<int> m_del(26);
vector<vector<int>> m_tra(26, vector<int>(26));

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

int BruteForce(int i, int j) {
    // Casos base
    if (i == 0) return j > 0 ? costo_ins(s2[j - 1]) + BruteForce(i, j - 1) : 0; // Necesitamos j inserciones
    if (j == 0) return i > 0 ? costo_del(s1[i - 1]) + BruteForce(i - 1, j) : 0; // Necesitamos i eliminaciones

    // Si los últimos caracteres son iguales, no hay costo
    if (s1[i - 1] == s2[j - 1]) {
        return BruteForce(i - 1, j - 1); // No se requiere operación
    }

    // Cálculo de costos para inserción, eliminación y sustitución
    int cost_insertion = costo_ins(s2[j - 1]) + BruteForce(i, j - 1); // Inserción
    int cost_deletion = costo_del(s1[i - 1]) + BruteForce(i - 1, j); // Eliminación
    int cost_substitution = costo_sub(s1[i - 1], s2[j - 1]) + BruteForce(i - 1, j - 1); // Sustitución

    // Cálculo de costo de transposición
    int cost_transposition = numeric_limits<int>::max();
    if (i > 1 && j > 1 && s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1]) {
        cost_transposition = costo_tras(s1[i - 1], s2[j - 2]) + BruteForce(i - 2, j - 2); // Transposición
    }

    // Encuentra el costo mínimo
    return min({cost_insertion, cost_deletion, cost_substitution, cost_transposition});
}
int main(int argc, char* argv[]){
    vector<string> strings1, strings2; 

    ifstream stringsFile(argv[1]);
    if (stringsFile.is_open()) {
        string line;
        int count = 0;
        while (getline(stringsFile, line)) {
            s1 = line; // Asignar la primera línea a s1
            if (getline(stringsFile, line)) {
                s2 = line; // Asignar la segunda línea a s2
            } else {
                s2 = ""; // Asignar cadena vacía si no hay segunda línea
            }
            getline(stringsFile, line); // Omitir la tercera línea

            strings1.push_back(s1); // Almacenar s1
            strings2.push_back(s2); // Almacenar s2
            count++;
        }
        stringsFile.close();
    } else {
        cerr << "Error al abrir el archivo: " << argv[1] << endl;
        return 1;
    }
    
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
    for (size_t k = 0; k < strings1.size(); ++k) {
        s1 = strings1[k];  // Asignar el valor actual de s1
        s2 = strings2[k];  // Asignar el valor actual de s2

        cout << "Caso " << (k + 1) << ": \n";
        cout << "String 1: " << s1 << "\n";
        cout << "String 2: " << s2 << "\n";

        auto start = chrono::high_resolution_clock::now();

        int resultado = BruteForce(s1.length(), s2.length());

        // Detener el temporizador
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;

        cout << "El costo minimo de operaciones es: " << resultado << "\n";
        cout << "Tiempo de ejecución: " << duration.count() << " segundos. \n";
    }
    return 0;
}