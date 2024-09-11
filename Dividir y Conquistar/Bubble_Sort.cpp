
// C++ program for the implementation of Bubble sort
#include <bits/stdc++.h>
using namespace std;

void bubbleSort(vector<int>& v) {
    int n = v.size();

    // Outer loop that corresponds to the number of
    // elements to be sorted
    for (int i = 0; i < n - 1; i++) {

        // Last i elements are already
        // in place
        for (int j = 0; j < n - i - 1; j++) {
          
              // Comparing adjacent elements
            if (v[j] > v[j + 1])
              
                  // Swapping if in the wrong order
                swap(v[j], v[j + 1]);
        }
    }
}
// Funcion que imprime un vector
void printVector(vector<int>& arr)
{
    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {
    vector<int> arr = {} ;
    
    //Paso datos del dataset a un vector para ordenar
    int num;
    while(cin >> num){
        arr.push_back(num);
    }
    int n = arr.size();    
    
    auto start = chrono::high_resolution_clock::now();
    bubbleSort(arr);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Tiempo en segundos: "<< duration.count() << endl;
    
    return 0;
}
