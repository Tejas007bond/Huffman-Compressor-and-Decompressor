#ifndef HUFFMAN_H
#define HUFFMAN_H

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

#endif