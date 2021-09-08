/***********************************************************************
 * Module:
 *    Week 08, Huffman
 *    Brother Helfrich, CS 235
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This program will implement the huffman() function
 ************************************************************************/

#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <vector>
#include <string>
#include <list>
#include "bnode.h"
#include "pair.h"
#include <string>
#include <fstream>

typedef Pair<char,float> Code;

class Huffman
{
private:
    //keeps track of the order the codes were in file
    std::vector<BinaryNode<Code>*> finalCodes;
    
    //used process the huffman codes
    std::vector<BinaryNode<Code>*> codes;

    //merge two trees in a new one
    void merge(int iFirstMin ,int iSecondMin);
    
    //find two nodes with frequences
    Pair<int,int> findTwoMins();
    
    //traverse the tree bottom up and get the huffman code reversed
    std::string getCodeReversed(BinaryNode<Code> *root);
    
    //print String reversed
    void printCode(std::string s);
    
    //delete the BT
    void freeData(BinaryNode<Code> *root);

    //get and set the value of the frequency of the node
    float& freqValue(BinaryNode<Code>* pCode) { return pCode->data.second; }
    
    //get and set the value of the token of the node
    char& tokenValue(BinaryNode<Code>* pCode) { return pCode->data.first; }
public:
    //TODO since this class uses pointer we need the rule of 3 here
    
    //default constructor
    Huffman() {}

    //destructor
    ~Huffman() { freeData(codes.front()); }
    
    //read the huffman codes from file into both vectors
    bool readFile(std::string filename);

    //display the Huffman table
    void display();
    
    //process the huffman code
    void process();
};


void huffman(std::string fileName);

#endif // HUFFMAN_h
