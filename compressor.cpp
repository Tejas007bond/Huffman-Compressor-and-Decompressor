#include<iostream>
#include<fstream>
using namespace std;

struct Node{
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char character,int frequency){
        ch = character;
        freq = frequency;
        left = nullptr;
        right = nullptr;
    }
};

struct CompareNodes{
    bool operator()(Node* const& n1,Node* const& n2){
        return n1->freq > n2->freq;
    }
};



int main(void){
    ifstream file("example.txt");

    if(!file){
        cout << "Unable to open file" << endl;
        return 1;
    }

    char ch;
    int frequency[256] = {0};

    while(file.get(ch)){
        frequency[(unsigned char)ch]++;
    }

    file.close();

    for(int i=0;i<256;i++){
        if(frequency[i] > 0){
            if (i > 32 && i < 127) {
                cout << "'" << (char)i << "' : " << frequency[i] << endl;
        } 
        
        else {
                cout << "ASCII " << i << " : " << frequency[i] << endl;
        }
        }
    }

    return 0;
}