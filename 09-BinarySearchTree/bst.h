/***********************************************************************
 * Component:
 *    Week 09, Binary Search Tree (BST)
 *    Brother Ercanbrack, CS 235
 * Author:
 *    Br. Helfrich
 *    Modified by Scott Ercanbrack - removed most of the the BST class functions,
 *                                   but left BST Iterator class.
 * Summary:
 *    Create a binary search tree
 ************************************************************************/

#ifndef BST_H
#define BST_H

#include "bnode.h"    // for BinaryNode
#include "stack.h"    // for Stack

// forward declaration for the BST iterator
template <class T>
class BSTIterator;

/*****************************************************************
 * BINARY SEARCH TREE
 * Create a Binary Search Tree
 *****************************************************************/
template <class T>
class BST
{
public:
    // constructor
    BST(): root(NULL), numItems(0){};
    
    // copy constructor
    BST(const BST & rhs) throw (const char *);
    
    ~BST()              { clear();              }
    
    int  size() const   { return numItems;      }
    
    // determine if the tree is empty
    bool empty() const  { return numItems == 0; }
    
    // remove all the nodes from the tree.  Makes an empty tree.
    void clear();
    
    // overloaded assignment operator
    BST & operator = (const BST & rhs) throw (const char *);
    
    // insert an item
    void insert(const T & t) throw (const char * );
    
    // remove an item
    void remove(BSTIterator <T> & it);
    
    // find a given item
    BSTIterator <T> find(const T & t);
    
    // the usual iterator stuff
    BSTIterator <T> begin() const;
    BSTIterator <T> end() const  { return BSTIterator <T> (NULL) ; }
    BSTIterator <T> rbegin() const;
    BSTIterator <T> rend() const  { return BSTIterator <T> (NULL); }
    
private:
    
    BinaryNode <T>* root;
    int numItems;
    
    BinaryNode <T>* copy(BinaryNode <T>* rhsRoot) throw (const char *);
    void clearRek(BinaryNode<T>* root);
    BinaryNode <T>* findInOrderSuccessor(BinaryNode <T>* root);
};

/*********************************************************
 * copy constructor
 **********************************************************/
template <class T>
BST<T>::BST(const BST<T> &rhs) throw (const char *)
{
    this->numItems = rhs.numItems;
    this->root = copy(rhs.root);
}

/***************************************************
 * COPY
 * copy the tree in post-order and return the new head
 ****************************************************/
template <class T>
BinaryNode <T> * BST<T> :: copy(BinaryNode <T> * rhsRoot) throw (const char *)
{
    if(!rhsRoot)
        return NULL;
    
    BinaryNode<T>*pNode = new (std::nothrow)BinaryNode<T>(rhsRoot->data);
    if(!pNode)
        throw "ERROR: Unable to allocate a node";
    
    pNode->addLeft(copy(rhsRoot->pLeft));
    pNode->addRight(copy(rhsRoot->pRight));
    return pNode;
}

/***************************************************
 * ASSIGNMENT OPERATOR
 * Delete the current tree first tree first and
 * copy the new one
 ****************************************************/
template <class T>
BST<T> & BST<T> :: operator = (const BST<T> & rhs) throw (const char *)
{
    if(this != &rhs)
    {
        //TODO maybe more efficient
        clearRek(this->root);
        this->numItems = rhs.numItems;
        this->root = copy(rhs.root);
    }
    return *this;
}

/**************************************
 * CLEAR
 * Delete every node in the tree
 ***************************************/
template <class T>
void BST<T> :: clear()
{
    clearRek(this->root);
    this->root = NULL;
    numItems = 0;
}

/****************************************************
 * CLEAR REK
 * A util clear method to delete every node recursively
 ******************************************************/
template <class T>
void BST<T> :: clearRek(BinaryNode<T>* root)
{
    if(!root)
        return;
    
    clearRek(root->pLeft);
    clearRek(root->pRight);
    delete root;
}

/*****************************************************
 * BST :: BEGIN
 * Return the first node (left-most) in a binary search tree
 ****************************************************/
template <class T>
BSTIterator <T> BST <T> :: begin() const
{
    Stack < BinaryNode <T> * > nodes;
    
    nodes.push(NULL);
    nodes.push(root);
    while (nodes.top() != NULL && nodes.top()->pLeft)
        nodes.push(nodes.top()->pLeft);
    
    return BSTIterator<T>(nodes);
}

/*****************************************************
 * BST :: RBEGIN
 * Return the last node (right-most) in a binary search tree
 ****************************************************/
template <class T>
BSTIterator <T> BST <T> :: rbegin() const
{
    Stack < BinaryNode <T> * > nodes;
    
    nodes.push(NULL);
    nodes.push(root);
    while (nodes.top() != NULL && nodes.top()->pRight)
        nodes.push(nodes.top()->pRight);
    
    return BSTIterator<T>(nodes);
}

/*****************************************************
 * BST :: INSERT
 * Insert a node at a given location in the tree
 ****************************************************/
template <class T>
void BST <T> :: insert(const T & t) throw (const char *)
{
    //copy the root first, can do it recursively too
    BinaryNode <T>* pCrawl = root;
    BinaryNode <T>* pParent = root;
    while(pCrawl)
    {
        pParent = pCrawl;
        pCrawl = (t <= pCrawl->data ? pCrawl->pLeft : pCrawl->pRight);
    }
    
    
    BinaryNode<T>*pNode = new (std::nothrow)BinaryNode<T>(t);
    if(!pNode)
        throw "ERROR: Unable to allocate a node";
    if(!root) //special case, empty tree
        root = pNode;
        else
            t <= pParent->data ? pParent->addLeft(pNode) : pParent->addRight(pNode);
            
            ++numItems;
            }
            
        /*****************************************************
         * BST :: INSERT
         * Insert a node at a given location in the tree
         * Don't insert dublicates, useful for SET ADT
         ****************************************************/
            //void BST <T> :: insert(const T & t) throw (const char *)
            //{
            //    //copy the root first, can do it recursively too
            //    BinaryNode <T>* pCrawl = root;
            //    BinaryNode <T>* pParent = root;
            //    while(pCrawl && pCrawl->data != t)
            //    {
            //        pParent = pCrawl;
            //        pCrawl = (t < pCrawl->data ? pCrawl->pLeft : pCrawl->pRight);
            //    }
            //
            //    if(!pCrawl) //only when null insert, if not null means the key exist already
            //    {
            //        //TODO wrap this in a fucntion
            //        ++numItems;
            //        BinaryNode<T>*pNode = new (std::nothrow)BinaryNode<T>(t);
            //        if(!pNode)
            //            throw "ERROR: Unable to allocate a node";
            //        if(!root) //special case, empty tree
            //            root = pNode;
            //        else
            //            t < pParent->data ? pParent->addLeft(pNode) : pParent->addRight(pNode);
            //    }
            //}
            
        /*************************************************
         * BST :: REMOVE
         * Remove a given node as specified by the iterator
         ************************************************/
            template <class T>
            void BST <T> :: remove(BSTIterator <T> & it)
        {
            BinaryNode<T> *pDelete = it.getNode();
            
            if(!pDelete) //null case
                return;
            
            //TODO maybe use ternary operator
            //case 1: no children
            if(pDelete->pRight == NULL && pDelete->pLeft == NULL)
            {
                if(pDelete->pParent) //if it has a parent
                {   //could do this with a ternary operator one line
                    if (pDelete->pParent->pRight == pDelete) //if it's on the right of the parent
                        pDelete->pParent->pRight = NULL;
                    else                                     //else it's on the left of the parent
                        pDelete->pParent->pLeft = NULL;
                }
                delete pDelete;
            }//case 2.1: one child on the left
            else if(pDelete->pRight == NULL && pDelete->pLeft)
            {
                pDelete->pLeft->pParent = pDelete->pParent;
                if(pDelete->pParent) //if it has a parent
                {
                    if (pDelete->pParent->pRight == pDelete)
                        pDelete->pParent->pRight = pDelete->pLeft;
                    else
                        pDelete->pParent->pLeft = pDelete->pLeft;
                }
                delete pDelete;
            } //case 2: one child on the right
            else if(pDelete->pLeft == NULL && pDelete->pRight)
            {
                pDelete->pRight->pParent = pDelete->pParent;
                if(pDelete->pParent) //if it has a parent
                {
                    if (pDelete->pParent->pRight == pDelete)
                        pDelete->pParent->pRight = pDelete->pRight;
                    else
                        pDelete->pParent->pLeft = pDelete->pRight;
                }
                delete pDelete;
            } //case 3: 2 children
            else
            {
                BinaryNode<T> * inOrderSuccessor = findInOrderSuccessor(pDelete);
                // copy the data now
                pDelete->data = inOrderSuccessor->data;
                
                if(inOrderSuccessor->pRight) //if it has a right child
                    inOrderSuccessor->pRight->pParent = inOrderSuccessor->pParent;
                
                inOrderSuccessor->pParent->pLeft = inOrderSuccessor->pRight;
                
                delete inOrderSuccessor;
            }
        }
            
        /****************************************************
         * BST :: FIND
         * Return the node corresponding to a given value
         ****************************************************/
            template <class T>
            BSTIterator <T> BST <T> :: find(const T & t)
        {
            BinaryNode<T> *pCrawl = root;
            while(pCrawl && pCrawl->data != t)
                pCrawl = (t < pCrawl->data ? pCrawl->pLeft : pCrawl->pRight);
            
            return BSTIterator <T> (pCrawl);
        }
            
            template <class T>
            BinaryNode <T>* BST <T> :: findInOrderSuccessor(BinaryNode <T>* root)
        {
            root = root->pRight;
            while(root->pLeft)
                root = root->pLeft;
            
            return root;
        }
            
        /**********************************************************
         * BINARY SEARCH TREE ITERATOR
         * Forward and reverse iterator through a BST
         *********************************************************/
            template <class T>
            class BSTIterator
        {
        public:
            // constructors
            BSTIterator(BinaryNode <T> * p = NULL)    { nodes.push(p);  }
            BSTIterator(Stack <BinaryNode <T> *> & s) { nodes = s;         }
            BSTIterator(const BSTIterator <T> & rhs)  { nodes = rhs.nodes; }
            
            // assignment
            BSTIterator <T> & operator = (const BSTIterator <T> & rhs)
            {
                // need an assignment operator for the Stack class.
                nodes = rhs.nodes;
                return *this;
            }
            
            // compare
            bool operator == (const BSTIterator <T> & rhs) const
            {
                // only need to compare the leaf node
                return rhs.nodes.const_top() == nodes.const_top();
            }
            bool operator != (const BSTIterator <T> & rhs) const
            {
                // only need to compare the leaf node
                return rhs.nodes.const_top() != nodes.const_top();
            }
            
            // de-reference. Cannot change because it will invalidate the BST
            T & operator * ()
            {
                return nodes.top()->data;
            }
            
            // iterators
            BSTIterator <T> & operator ++ ();
            BSTIterator <T>   operator ++ (int postfix)
            {
                BSTIterator <T> itReturn = *this;
                ++(*this);
                return itReturn;
            }
            BSTIterator <T> & operator -- ();
            BSTIterator <T>   operator -- (int postfix)
            {
                BSTIterator <T> itReturn = *this;
                --(*this);
                return itReturn;
            }
            
            // must give friend status to remove so it can call getNode() from it
            friend void BST <T> :: remove(BSTIterator <T> & it);
            
        private:
            
            // get the node pointer
            BinaryNode <T> * getNode() { return nodes.top(); }
            
            // the stack of nodes
            Stack < BinaryNode <T> * > nodes;
        };
            
            
        /**************************************************
         * BST ITERATOR :: INCREMENT PREFIX
         * advance by one
         *************************************************/
            template <class T>
            BSTIterator <T> & BSTIterator <T> :: operator ++ ()
        {
            // do nothing if we have nothing
            if (nodes.top() == NULL)
                return *this;
            
            // if there is a right node, take it
            if (nodes.top()->pRight != NULL)
            {
                nodes.push(nodes.top()->pRight);
                
                // there might be more left-most children
                while (nodes.top()->pLeft)
                    nodes.push(nodes.top()->pLeft);
                return *this;
            }
            
            // there are no right children, the left are done
            assert(nodes.top()->pRight == NULL);
            BinaryNode <T> * pSave = nodes.top();
            nodes.pop();
            
            // if the parent is the NULL, we are done!
            if (NULL == nodes.top())
                return *this;
            
            // if we are the left-child, got to the parent.
            if (pSave == nodes.top()->pLeft)
                return *this;
            
            // we are the right-child, go up as long as we are the right child!
            while (nodes.top() != NULL && pSave == nodes.top()->pRight)
            {
                pSave = nodes.top();
                nodes.pop();
            }
            
            return *this;
        }
            
        /**************************************************
         * BST ITERATOR :: DECREMENT PREFIX
         * advance by one
         *************************************************/
            template <class T>
            BSTIterator <T> & BSTIterator <T> :: operator -- ()
        {
            // do nothing if we have nothing
            if (nodes.top() == NULL)
                return *this;
            
            // if there is a left node, take it
            if (nodes.top()->pLeft != NULL)
            {
                nodes.push(nodes.top()->pLeft);
                
                // there might be more right-most children
                while (nodes.top()->pRight)
                    nodes.push(nodes.top()->pRight);
                return *this;
            }
            
            // there are no left children, the right are done
            assert(nodes.top()->pLeft == NULL);
            BinaryNode <T> * pSave = nodes.top();
            nodes.pop();
            
            // if the parent is the NULL, we are done!
            if (NULL == nodes.top())
                return *this;
            
            // if we are the right-child, got to the parent.
            if (pSave == nodes.top()->pRight)
                return *this;
            
            // we are the left-child, go up as long as we are the left child!
            while (nodes.top() != NULL && pSave == nodes.top()->pLeft)
            {
                pSave = nodes.top();
                nodes.pop();
            }
            
            return *this;
        }
            
#endif // BST_H
