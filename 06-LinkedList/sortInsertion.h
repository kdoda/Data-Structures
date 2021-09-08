/***********************************************************************
 * Header:
 *    INSERTION SORT
 * Summary:
 *    This will contain just the prototype for insertionSortTest(). You may
 *    want to put other class definitions here as well.
 * Author
 *    Klevin Doda
 ************************************************************************/

#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include "node.h"

/***********************************************
 * INSERT SORTED
 * Insert the value in the right pos in the LL
 **********************************************/
template <class T>
Node<T>* insertSorted(const T&t,Node<T> *pHead)
{
    Node<T> *newNode = new Node<T>(t);
    if(!pHead) //emtpy
        return newNode;
    if(pHead->data >= t) //insert in the first position
    {
        newNode->pNext = pHead;
        return newNode;
    }
    
    Node<T> *prevCrawl = pHead;
    Node<T> *pCrawl = pHead->pNext;
    
    //< makes it to insert it right way improves the case where all nodes equal
    while(pCrawl && pCrawl->data < t) //check this
    {
        prevCrawl = pCrawl;
        pCrawl = prevCrawl->pNext;
    }
    newNode->pNext = prevCrawl->pNext;
    prevCrawl->pNext = newNode;
    return pHead;
}

/***********************************************
 * COPY LIST TO ARRAY
 * Copy the elements of the Linked List to the
 * array
 **********************************************/
template <class T>
void copyListToArray(Node<T> *pHead,T *array)
{
    //no need for bounds checking since the list is the same size
    //as the array
    while(pHead)
    {
        *(array++) = pHead->data;
        pHead = pHead->pNext;
    }
}

/***********************************************
 * INSERTION SORT
 * Sort the items in the array
 **********************************************/
template <class T>
void sortInsertion(T array[], int num)
{
    //construct the sorted list
    Node<T> *pHead = NULL;
    for(int i = 0;i < num;++i)
        pHead = insertSorted(array[i],pHead);
    
    //copy the sorted list to the same array again
    copyListToArray(pHead,array);
    //free memory
    freeData(pHead);
}

#endif // INSERTION_SORT_H

