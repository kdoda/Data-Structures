#ifndef BNODE_H
#define BNODE_H

#include <iostream>
#include <cassert>

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

/***************************************
 * ADD LEFT
 * Add on the left of this node, pNode
 ***************************************/
template <class T>
void BinaryNode<T> :: addLeft (BinaryNode <T> * pNode)
{
    if(pNode)
        pNode->pParent = this;

    this->pLeft = pNode;
}

/***************************************
 * ADD RIGHT
 * Add on the right of this node, pNode
 ***************************************/
template <class T>
void BinaryNode<T> :: addRight(BinaryNode <T> * pNode)
{
    if(pNode)
        pNode->pParent = this;

    this->pRight = pNode;
}

/***************************************
 * ADD LEFT
 * Add on the left of this node, t
 ***************************************/
template <class T>
void BinaryNode<T> :: addLeft (const T & t) throw (const char *)
{
    BinaryNode<T> *newNode = new (std::nothrow)BinaryNode<T>(t);
    if(!newNode)
        throw "ERROR: Unable to allocate a node";

    newNode->pParent = this;
    this->pLeft = newNode;
}

/***************************************
 * ADD RIGHT
 * Add on the right of this node, t
 ***************************************/
template <class T>
void BinaryNode<T> :: addRight(const T & t) throw (const char *)
{
    BinaryNode<T> *newNode = new (std::nothrow)BinaryNode<T>(t);
    if(!newNode)
        throw "ERROR: Unable to allocate a node";

    newNode->pParent = this;
    this->pRight = newNode;
}

/*********************************************
 * DELETE BINARY TREE
 * Delete the BT recursively, using post-order
 *********************************************/
template <class T>
void deleteBinaryTree(BinaryNode <T> * root)
{
    if(!root)
        return;

    deleteBinaryTree(root->pLeft);
    deleteBinaryTree(root->pRight);
    delete root;
}

/********************************
 * << OPERATOR
 * Print the tree in-order
 ********************************/
template <class T>
std::ostream& operator<< (std::ostream& os, const BinaryNode<T> *root)
{
    if(root)
    {
        os << root->pLeft;
        os << root->data << " ";
        os << root->pRight;
    }
    
    return os;
}

#endif // BNODE_H
