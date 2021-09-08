/***********************************************************************
 * Module:
 *    Week 08, Huffman
 *    Brother Helfrich, CS 235
 * Author:
 *    Klevin Doda
 * Summary:
 *    This program will implement the huffman() function
 ************************************************************************/

#include "huffman.h"       // for HUFFMAN() prototype

using namespace std;

/**********************************************************
 * FREE DATA
 * Delete all the allocated nodes that are in a form of BT
 **********************************************************/
void Huffman :: freeData(BinaryNode<Code> *root)
{
    if(!root)
        return;

    freeData(root->pLeft);
    freeData(root->pRight);
    delete root;
}

/*************************************************************
 * READ FILE
 * Read the huffman codes, into both arrays codes, finalCodes
 ************************************************************/
bool Huffman :: readFile(std::string filename)
{
    ifstream fin(filename.c_str());
    if(fin.fail())
        return false;

    Code code;
    while(fin >> code)
    {
        //we are not doing any file validation here
        BinaryNode<Code>* pCode = new BinaryNode<Code>(code);
        
        //TODO check for memory allocation failure
        codes.push_back(pCode);
        finalCodes.push_back(pCode);
    }

    return true;
}

/**********************************************************
 * FIND TWO MINS
 * Returns a pair of two mins in the array, first will be
 * the first position min in the List, crucial for the
 * algorithm to work.
 **********************************************************/
Pair<int,int> Huffman :: findTwoMins()
{
    assert(codes.size() >=2);
    int iFirstMin = 0;
    int iSecondMin = 1;

    if(freqValue(codes[iFirstMin]) > freqValue(codes[iSecondMin]))
        std::swap(iFirstMin,iSecondMin);

    //first should have the lowest value of the two for the code below to work
    for(int i = 2; i < codes.size(); ++i)
    {
        if(freqValue(codes[i]) < freqValue(codes[iFirstMin]))
        {
            iSecondMin = iFirstMin;
            iFirstMin = i;
        }
        else if (freqValue(codes[i]) < freqValue(codes[iSecondMin]))
        {
            iSecondMin = i;
        }
    }
    
    if(iFirstMin > iSecondMin)
        std::swap(iFirstMin,iSecondMin);

    return Pair<int,int> (iFirstMin, iSecondMin);
}

/**********************************************************
 * MERGE
 * Merge the two nodes by forming a new tree, following
 * Br. Helfrich's instructions
 **********************************************************/
void Huffman :: merge(int iFirstMin ,int iSecondMin)
{
    BinaryNode<Code> *first = codes[iFirstMin];
    BinaryNode<Code> *second = codes[iSecondMin];
    float sumFreq = freqValue(first) + freqValue(second);
    BinaryNode<Code> *newNode = new BinaryNode<Code>(Code(' ',sumFreq));

    if(freqValue(first) <= freqValue(second))
    {
        newNode->addLeft(first);
        newNode->addRight(second);
    }
    else
    {
        newNode->addLeft(second);
        newNode->addRight(first);
    }

    codes[iFirstMin] = newNode;
    codes[iSecondMin] = codes.back();
    codes.pop_back();
}

/**********************************************************
 * PROCESS
 * Form the huffman tree, in O(n^2)
 **********************************************************/
void Huffman :: process()
{
    while(codes.size() != 1)
    {
        Pair<int,int> mins = findTwoMins();
        merge(mins.first,mins.second);
    }
    
    assert(codes.size() == 1);
}

/**********************************************************
 * DISPLAY
 * Display the huffman codes in order we read them from the
 * file, by using the finalCodes array, since that preserves
 * the order.
 **********************************************************/
void Huffman :: display()
{
    for(int i = 0;i < finalCodes.size();++i)
    {
        cout << tokenValue(finalCodes[i]) << " = ";
        printCode(getCodeReversed(finalCodes[i]));
    }
}

/**********************************************************
 * GET CODE REVERSED
 * Start from the leaf and go up the tree, form the code
 * string in reverse order
 **********************************************************/
string Huffman :: getCodeReversed(BinaryNode<Code> *leaf)
{
    string s = "";
    BinaryNode<Code> *pParent = leaf->pParent;
    while(pParent)
    {
        s.push_back(pParent->pLeft == leaf ? '0' : '1');
        leaf = pParent;
        pParent = pParent->pParent;
    }
    return s;
}


/**********************************************************
 * PRINT CODE
 * Print the code in reverse order
 **********************************************************/
void Huffman :: printCode(string s)
{
    for(int i = s.size() - 1; i >= 0;--i)
        cout << s[i];

    cout << endl;
}

/**********************************************************
 * HUFFMAN
 * Driver program to exercise the huffman generation code
 **********************************************************/
void huffman(string fileName)
{
    Huffman huffman;
    huffman.readFile(fileName);
    huffman.process();
    huffman.display();
    return;
}
