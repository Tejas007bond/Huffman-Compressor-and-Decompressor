#include<iostream>
#include<string>
#include<fstream>
using namespace std;

void decompressFile(const string& inputPath,const string& outputPath){
    ifstream inFile(inputPath,ios::binary);
    ofstream outFile(outputPath);

    if(!inFile || !outFile){
        cout << "Error opening files during compression" << endl;
        return;
    }

    int frequency[256] = {0};
    
}

int main(void){
}