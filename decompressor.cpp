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

    priority_queue<Node*, vector<Node*>, CompareNodes> minHeap;
    for (int i = 0; i < 256; i++) {
        if (frequency[i] > 0) {
            minHeap.push(new Node((char)i, frequency[i]));
        }
    }

    if (minHeap.empty()) return 0;

    while (minHeap.size() > 1) {
        Node* left = minHeap.top(); minHeap.pop();
        Node* right = minHeap.top(); minHeap.pop();
        Node* parent = new Node('\0', left->freq + right->freq);
        parent->left = left; parent->right = right;
        minHeap.push(parent);
    }

    Node* root = minHeap.top();

    Node* curr = root;
    int charactersDecoded = 0;
    int totalCharacters = root->freq;
    char byte;

    while (inFile.get(byte) && charactersDecoded < totalCharacters) {
        for (int i = 7; i >= 0; i--) {
            int bit = (byte >> i) & 1;

            if (bit == 0) curr = curr->left;
            else curr = curr->right;

            // Arrived at a leaf character node
            if (curr->left == nullptr && curr->right == nullptr) {
                outFile.put(curr->ch);
                charactersDecoded++;
                curr = root;

                if (charactersDecoded == totalCharacters) break;
            }
        }
    }

    inFile.close();
    outFile.close();
    cout << "Decompression complete! Saved to output_restored.txt" << endl;
    return 0;
}
