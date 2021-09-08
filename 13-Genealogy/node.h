#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <iostream>
#include <cassert>

/************************************************
 * NODE
 * A class that represents a node of Linked-List
 ***********************************************/
template <class T>
class Node
{
public:
    Node(T data) : data(data),pLeft(NULL), pRight(NULL) { }
    Node(T data, Node* pLeft, Node* pRight ) : data(data), pLeft(pLeft), pRight(pRight) { }
    
    friend std::ostream& operator<< (std::ostream& os, Node* pHead)
    {
        if(pHead)
        {
            while(pHead->pRight)
            {
                os << pHead->data << ", ";
                pHead = pHead->pRight;
            }
            os << pHead->data;
        }
        
        return os;
    }
    
    T data;
    Node* pRight; //next pointer in the LL, mother pointer in pedigree
    Node* pLeft;  //used only for father pointer in pedigree
};


#endif

