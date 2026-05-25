#include<iostream>
#include<fstream>
using namespace std;

int main(void){
    ifstream file("example.txt");

    if(!file){
        cout << "Unable to open file" << endl;
        return 1;
    }

    char ch;
    int frequency[256] = {0};
    
    while(file.get(ch)){
        frequency[(int)ch]++;
    }
}