#include<iostream>
#include<fstream>
#include<queue>
#include<vector>
#include<string>
#include<unordered_map>
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

void generateCode(Node* root,string code,string* huffmanCodes){
    if(root == nullptr){
        return;
    }

    if(root->left == nullptr && root->right == nullptr){
        huffmanCodes[(unsigned char)root->ch] = code;
        return;
    }

    generateCode(root->left,code+"0",huffmanCodes);
    generateCode(root->right,code+"1",huffmanCodes);
}

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
    
    priority_queue<Node*, vector<Node*>, CompareNodes> minHeap;

    for(int i=0;i<256;i++){
        if(frequency[i] > 0){
            minHeap.push(new Node((char)i, frequency[i]));
        }
    }

    if(minHeap.empty()){
        cout << "The file is empty nothing to compress." << endl;
        return 0;
    }

    while (minHeap.size() > 1){
        Node* leftChild = minHeap.top();
        minHeap.pop();

        Node* rightChild = minHeap.top();
        minHeap.pop();

        int combinedFrequency =  leftChild->freq + rightChild->freq;
        Node* parentNode = new Node('\0',combinedFrequency);

        parentNode->left = leftChild;
        parentNode->right = rightChild;

        minHeap.push(parentNode);
    }

    Node* root = minHeap.top();
    string code[256];

    if(root->left == nullptr && root->right == nullptr){
        code[(unsigned char)root->ch] = "0";
    }
    else{
            generateCode(root,"",code);
    }
    for(int i=0;i<256;i++){
        if(!code[i].empty()){
            cout << (char)i << " : " << code[i] << endl;
        }
    }

    return 0;
}