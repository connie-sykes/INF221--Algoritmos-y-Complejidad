#include <iostream>
#include <fstream> 
#include <random>

using namespace std;

string RandomString(int length) {
    const string characters = "abcdefghijklmnopqrstuvwxyz";
    string randomString;
    random_device rd;  // Obtain a random number from hardware
    mt19937 eng(rd()); // Seed the generator
    cout << "Seed is" << rd() << endl;

    uniform_int_distribution<> distr(0, characters.size() - 1); // Define the range

    for (int i = 0; i < length; ++i) {
        randomString += characters[distr(eng)]; // Generate random character
    }

    return randomString;
}

int main() {
    int quote = 100;

    std::ofstream outFile("strings.txt");
    if (!outFile) {
        std::cerr << "Error al abrir el archivo para escribir." << std::endl;
        return 1;
    }
for(int k=0;k<3;++k){
    for (int i = 0; i < 2; ++i) {
        std::string randomStr;
        if(k==0){
        randomStr = RandomString(4);
        }
        if(k==1){
        randomStr = RandomString(12);
        }
        if(k==2){
        randomStr = RandomString(18);
        }
        outFile << randomStr << std::endl; // Escribir la cadena en el archivo

    }
    outFile<<"\n";
}
    outFile.close();

    ofstream Insert("cost_insert.txt");
    int n;
    for(int i=0; i<26;++i){
        // Write to the file
        n = rand() % quote;
        Insert << n <<" ";
    }
    Insert.close();

    ofstream Delete("cost_delete.txt");
    int m;
    for(int i=0; i<26;++i){
        // Write to the file
        m = rand() % quote;
        Delete << m <<" ";
    }    
    Delete.close();

    ofstream Replace("cost_replace.txt");
    int o;
    for(int i=0; i<26;++i){
        for(int j=0; j<26;++j){
            if(i==j) o=0;
            else{
                o=rand() % quote;}
            Replace << o << " ";
        }
        Replace << "\n";
    }
    Replace.close();

    ofstream Transpose("cost_transpose.txt");
    int p;
    for(int i=0; i<26;++i){
        for(int j=0; j<26;++j){
            if(i==j) p=0;
            else{
                p=rand() % quote;}
            p=rand() % quote;
            Transpose << p << " ";
        }
        Transpose << "\n";
    }
    Transpose.close();
} 