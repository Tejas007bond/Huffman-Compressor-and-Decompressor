#include<iostream>
#include<string>
#include<fstream>
#include<queue>
#include<vector>
#include "huffman.h"

using namespace std;

int main(){
    ifstream inFile("compressed.bin",ios::binary);
    ofstream outFile("output_restored.txt");

    if(!inFile || !outFile){
        cout << "Error opening files for decompression" << endl;
        return 1;
    }
    
    int frequency[256] = {0};
    inFile.read(reinterpret_cast<char*>(frequency),256*sizeof(int));
    
}