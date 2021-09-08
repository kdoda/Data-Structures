/***********************************************************************
 * Module:
 *    Week 09, Sort Binary
 *    Brother Helfrich, CS 235
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This program will implement the Binary Tree Sort
 ************************************************************************/

#ifndef BINARY_H
#define BINARY_H

#include "bst.h"

/*****************************************************
 * SORT BINARY
 * Perform the binary tree sort
 ****************************************************/
template <class T>
void sortBinary(T array[], int num)
{
    BST<T> bst;
    for(int i = 0;i < num;++i)
        bst.insert(array[i]);

    int i = 0;
    for(BSTIterator<T> it = bst.begin(); it != bst.end();++it)
        array[i++] = *it;
}


#endif // SORT_BINARY_H
