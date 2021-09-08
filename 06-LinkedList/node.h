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
    Node() : pNext(NULL) {}
    Node(T data) : data(data), pNext(NULL) { }
    Node(T data, Node* pNext ) : data(data), pNext(pNext) { }
    
    friend std::ostream& operator<< (std::ostream& os, Node* pHead)
    {
        if(pHead)
        {
            while(pHead->pNext)
            {
                os << pHead->data << ", ";
                pHead = pHead->pNext;
            }
            os << pHead->data;
        }
        
        return os;
    }
    
    T data;
    Node* pNext;
};

/************************************************
 * INSERT
 * Insert into any position in the Linked list
 ***********************************************/
template <class T>
void insert(const T & t,
            Node<T> *& pHead,
            bool head = false)
{
    Node<T> *newNode = new Node<T>(t);
    if(!pHead || head)
    {
        newNode->pNext = pHead;
        pHead = newNode;
    }
    else
    {
        newNode->pNext = pHead->pNext;
        pHead->pNext = newNode;
    }
}

/************************************************
 * COPY
 * Create a new copy of the Linked List
 ***********************************************/
template <class T>
Node<T>* copy(Node<T> *pHead)
{
    if(!pHead) return NULL;
    
    Node<T> *pHeadCopy = new Node<T>(pHead->data);
    Node<T> *pCrawl = pHeadCopy;
    pHead = pHead->pNext;
    
    while(pHead)
    {
        pCrawl->pNext = new Node<T>(pHead->data);
        pHead = pHead->pNext;
        pCrawl = pCrawl->pNext;
    }
    return pHeadCopy;
}

/************************************************
 * DELETE
 * Free the memory, delete every node
 ***********************************************/
template <class T>
void freeData(Node<T> *&pHead)
{
    //works even when pHead is NULL no need to check
    Node<T> *prevHead = pHead;
    while(pHead)
    {
        pHead = pHead->pNext;
        delete prevHead;
        prevHead = pHead;
    }
    pHead = NULL;
}

/************************************************
 * FIND
 * Find the node, return NULL if it doesnt exist
 ***********************************************/
template <class T>
Node<T>* find(Node<T> *pHead,const T& t)
{
    while(pHead)
    {
        if(pHead->data == t)
            return pHead;
        
        pHead = pHead->pNext;
    }
    return NULL;
}

#endif

