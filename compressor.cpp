#include<iostream>
#include<fstream>
#include<queue>
#include<vector>
#include<string>

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

void writeCompressedFile(const string& inputPath,const string& outputPath,int* frequency,string* huffmanCodes){
    ifstream inFile(inputPath,ios::binary);
    ofstream outFile(outputPath,ios::binary);

    if(!inFile || !outFile){
        cout << "Error opening files during the compression phase" << endl;
        return;
    }

    outFile.write(reinterpret_cast<const char*>(frequency),256*sizeof(int));

    unsigned char bitbuffer = 0;
    int bitcount = 0;
    char ch;

    while(inFile.get(ch)){
        string code = huffmanCodes[(unsigned char)ch];

        for(char bit : code){
            bitbuffer = bitbuffer << 1;
            
            if(bit == '1'){
                bitbuffer = bitbuffer | 1;
            }
            bitcount++;

            if(bitcount == 8){
                outFile.put(bitbuffer);
                bitbuffer = 0;
                bitcount = 0;
            }
        }
    }

    if(bitcount > 0){
        bitbuffer = bitbuffer << (8-bitcount);
        outFile.put(bitbuffer);
    }
    inFile.close();
    outFile.close();
    cout << "Compression complete. Binary file saved." << endl;
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

    writeCompressedFile("example.txt","compressed.bin",frequency,code);

    return 0;
}