#include <bits/stdc++.h>
using namespace std;

// Merges two subarrays of arr[].
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary vectors
    vector<int> L(n1), R(n2);

    // Copy data to temp vectors L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    // Merge temporary vectors into arr[left..right]
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Function to perform merge sort
void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right)
        return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// Function to print a vector to a file
void printVectorToFile(const vector<int>& arr, const string& filename) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const int& num : arr) {
            outFile << num << " ";
        }
        outFile.close();
    } else {
        cerr << "Unable to open file for writing: " << filename << endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    vector<int> arr;
    string inputFilename = argv[1]; // Get the filename from command line argument

    // Read numbers into the vector from standard input
    int num;
    while (cin >> num) {
        arr.push_back(num);
    }

    int n = arr.size();
    auto start = chrono::high_resolution_clock::now();
    mergeSort(arr, 0, n - 1);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Tiempo en segundos: " << duration.count() << endl;

    // Construct output filename
    string outputFilename = "Merge sorted " + inputFilename;

    // Print the sorted vector to the output file
    printVectorToFile(arr, outputFilename);

    return 0;
}
