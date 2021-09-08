//
// Created by Klevin Doda on 11/5/18.
//

#ifndef BNODE_H
#define BNODE_H

#include <iostream>

/*****************************************************************
 * BINARY NODE
 * A single node in a binary tree.  Note that the node does not know
 * anything about the properties of the tree so no validation can be done.
 *****************************************************************/
template <class T>
class BinaryNode
{
public:

    BinaryNode() : pLeft(NULL), pRight(NULL), pParent(NULL) { }
    BinaryNode(const T& data)
            : data(data), pLeft(NULL), pRight(NULL), pParent(NULL) { }

    // return size (i.e. number of nodes in tree)
    int size() const
    {
        return 1 +
               (pLeft == NULL ? 0 : pLeft->size()) +
               (pRight == NULL ? 0 : pRight->size());
    }

    // add a node to the left/right
    void addLeft (BinaryNode <T> * pNode);
    void addRight(BinaryNode <T> * pNode);

    // create a node and add it to the left/right
    void addLeft (const T & t) throw (const char *);
    void addRight(const T & t) throw (const char *);

    // since no validation is done, everything is public
    BinaryNode <T> * pLeft;
    BinaryNode <T> * pRight;
    BinaryNode <T> * pParent;
    T data;
};

/********************************
 * ADD LEFT
 * Add the node on the left
 ********************************/
template <class T>
void BinaryNode<T> :: addLeft (BinaryNode <T> * pNode)
{
    if(pNode)
        pNode->pParent = this;
    
    this->pLeft = pNode;
}

/********************************
 * ADD RIGHT
 * Add the node on the right
 ********************************/
template <class T>
void BinaryNode<T> :: addRight(BinaryNode <T> * pNode)
{
    if(pNode)
        pNode->pParent = this;
    
    this->pRight = pNode;
}

/********************************
 * ADD LEFT
 * Add the value on the left
 ********************************/
template <class T>
void BinaryNode<T> :: addLeft (const T & t) throw (const char *)
{
    BinaryNode<T> *newNode = new (std::nothrow)BinaryNode<T>(t);
    if(!newNode)
        throw "ERROR: Unable to allocate a node";
    
    newNode->pParent = this;
    this->pLeft = newNode;
}

/********************************
 * ADD RIGHT
 * Add the value on the right
 ********************************/
template <class T>
void BinaryNode<T> :: addRight(const T & t) throw (const char *)
{
    BinaryNode<T> *newNode = new (std::nothrow)BinaryNode<T>(t);
    if(!newNode)
        throw "ERROR: Unable to allocate a node";
    
    newNode->pParent = this;
    this->pRight = newNode;
}

#endif //BNODE_H
