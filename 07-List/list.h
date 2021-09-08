#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <iostream>
#include <cassert>

template <class T>
class ListIterator;

/************************************************
 * NODE
 * A class that represents a node of DL-List
 ***********************************************/
template <class T>
class Node
{

public:
    Node() : pNext(NULL),pPrev(NULL) { }
    Node(T data) : data(data), pNext(NULL),pPrev(NULL)  { }
    Node(T data, Node* pPrev, Node* pNext)
            : data(data), pPrev(pPrev), pNext(pNext) { }

    T data;
    Node* pNext;
    Node* pPrev;
};

/************************************************
 * LIST
 * A class that represents List ADT, implemented
 * by a double linked list circular
 ***********************************************/
template <class T>
class List
{
public:
    // default constructor : empty and kinda useless
    List() { setDefault(); };

    // copy constructor : copy it
    List(const List& rhs) throw (const char *);

    //destructor
    ~List() { clear(); }

    // assignment operator
    List& operator = (const List& rhs) throw (const char *);

    // is the set currently empty
    bool empty() const { return numItems == 0; }

    // what is the capacity
    int size() const { return numItems; }

    // remove all the items from the set
    void clear();

    // add to the end
    void push_back(const T &t)  throw (const char *);

    //add the the front
    void push_front(const T &t) throw (const char *);

    //get set back and front
    T&   back()  throw       (const char *);
    T&   front() throw       (const char *);

    //get back and front
    T    back()  const throw (const char *);
    T    front() const throw (const char *);

    //Insert at the pos iterator and return an iterator to the inserted node
    ListIterator<T> insert(const ListIterator<T>& it, const T & t) throw (const char *);

    //Remove the node pointed by iterator, and return an iterator to the next node
    ListIterator<T> remove(const ListIterator<T>& it) throw (const char *);

    // return an iterator to the beginning of the list
    ListIterator <T> begin() const { return ListIterator<T>(pHead); }

    // return an iterator to the end of the list
    ListIterator <T> end() const { return ListIterator<T>(NULL); }

    // return an iterator to the beginning of the list
    ListIterator <T> rbegin() const { return ListIterator<T>(pTail); }

    // return an iterator to the end of the list
    ListIterator <T> rend() const { return ListIterator<T>(NULL); }

    //swap just the pointers in O(1)
    void swap(List& rhs);

private:
    Node<T>* pHead;        // pointer to the first node
    Node<T>* pTail;        // pointer to the last node
    int numItems;          // home many nodes are in the DLL

    void swapPointers(Node<T>*& p, Node<T>*& q);
    void setDefault();
};


/**************************************************
 * LIST ITERATOR
 * An iterator through LIST
 *************************************************/
template <class T>
class ListIterator
{
public:
    // default constructor
    ListIterator() : p(NULL) {}

    // copy constructor
    ListIterator(const ListIterator& rhs) { this->p = rhs.p; }

    // initialize to direct p to some item
    ListIterator(Node<T> * p) : p(p) {}

    // equal operator
    bool operator == (const ListIterator & rhs) const
    {
        return rhs.p == this->p;
    }

    // assignment operator
    ListIterator<T> & operator = (const ListIterator & rhs)
    {
        this->p = rhs.p;
        return *this;
    }

    // not equals operator
    bool operator != (const ListIterator & rhs) const
    {
        return rhs.p != this->p;
    }

    // dereference operator
    T & operator * ()
    {
        return p->data;
    }

    // prefix increment
    ListIterator <T> & operator ++ ()
    {
        p = p->pNext;
        return *this;
    }

    // postfix increment
    ListIterator <T> operator++(int postfix)
    {
        ListIterator tmp(*this);
        p = p->pNext;
        return tmp;
    }

    // prefix decrement
    ListIterator <T> & operator -- ()
    {
        p = p->pPrev;
        return *this;
    }

    // postfix decrement
    ListIterator <T> operator--(int postfix)
    {
        ListIterator tmp(*this);
        p = p->pPrev;
        return tmp;
    }


    friend  ListIterator<T> List <T> :: insert(const ListIterator<T>& it, const T & data) throw (const char *);
    friend  ListIterator<T> List <T> :: remove(const ListIterator<T>& it) throw (const char *);
private:
    Node<T> * p;

    ListIterator<T> & operator = (Node<T> * p)
    {
        this->p = p;
        return *this;
    }
};

/**********************************************
 * SET : SET DEFAULT
 * Set data to default values
 **********************************************/
template <class T>
void List <T> :: setDefault()
{
    numItems = 0;
    pHead = pTail = NULL;
}

/**********************************************
 * SET : SET DEFAULT
 * Set data to default values
 **********************************************/
template <class T>
List <T> :: List(const List <T> &rhs) throw (const char *)
{
    setDefault();
    for(Node<T> *p = rhs.pHead; p ; p = p->pNext)
        this->push_back(p->data);
}

/**********************************************
 * Assignment operator inefficient
 **********************************************/
//template <class T>
//List<T>& List <T> :: operator = (const List<T> & rhs) throw (const char *)
//{
//    if (this == &rhs)
//        return *this;
//
//    if(!empty())
//        clear(); //free the memory
//
//    setDefault();
//
//    for(Node<T> *p = rhs.pHead; p ; p = p->pNext)
//        this->push_back(p->data);
//
//    return *this;
//}

/**********************************************
 * Assignment operator efficient
 **********************************************/
template <class T>
List<T>& List <T> :: operator = (const List<T> & rhs) throw (const char *)
{
    if (this == &rhs)
        return *this;

    Node<T>* thisP = pHead;
    Node<T>* prevThisP = pHead;
    Node<T>* rhsP  = rhs.pHead;

    while(thisP && rhsP)
    {
        thisP->data = rhsP->data;
        prevThisP = thisP;
        thisP = thisP->pNext;
        rhsP  = rhsP->pNext;
    }
    //two cases, this is long than rhs, or otherwise

    //set the next of the last node to NULL, and move the tail
    if(prevThisP)
    {
        prevThisP->pNext = NULL;
        pTail = prevThisP;
    }

    //in case we are going to delete the rest tail is right where we want
    //in case we are going to add push_back moves the tail

    //we must take care of the case when this is longer first to avoid memory leaks
    while(thisP)
    {
        Node<T> *thisPNext = thisP->pNext;
        delete thisP;
        thisP = thisPNext;
    }

    while(rhsP)
    {
        this->push_back(rhsP->data);
        rhsP = rhsP->pNext;
    }

    return *this;
}

/**********************************************
 * Destructor
 * Delete allocated nodes, except the dummy one
 **********************************************/
template <class T>
void List <T> ::  clear()
{
    Node<T> *pCrawl = pHead;
    while(pCrawl)
    {
        Node<T> *pCrawlNext = pCrawl->pNext;
        delete pCrawl;
        pCrawl = pCrawlNext;
    }
    setDefault();
}

/**********************************************
 * Push back
 * Add to the end of the DLL
 **********************************************/
template <class T>
void List <T> :: push_back(const T &t) throw (const char *)
{
    Node<T> *newNode = new (std::nothrow)Node<T>(t,pTail,NULL);
    if(!newNode)
        throw "ERROR: unable to allocate a new node for a list";

    pTail = (pHead ? pTail->pNext : pHead) = newNode;
    numItems++;
}

/**********************************************
 * Push front
 * Add to the front of the DLL
 **********************************************/
template <class T>
void List <T> :: push_front(const T &t) throw (const char *)
{
    Node<T> *newNode = new (std::nothrow)Node<T>(t,NULL,pHead);
    if(!newNode)
        throw "ERROR: unable to allocate a new node for a list";

    pHead = (pHead ? pHead->pPrev : pTail) = newNode;
    numItems++;
}

//TODO maybe merge in a function
/**********************************************
 * Back
 * Get and set the last element
 **********************************************/
template <class T>
T&   List <T> :: back()  throw       (const char *)
{
    if(empty())
        throw "ERROR: unable to access data from an empty list";

    return pTail->data;
}

/**********************************************
 * Front
 * Get and set the first element
 **********************************************/
template <class T>
T&   List <T> :: front() throw       (const char *)
{
    if(empty())
        throw "ERROR: unable to access data from an empty list";

    return pHead->data;
}

/**********************************************
 * Back
 * Get the last element
 **********************************************/
template <class T>
T    List <T> :: back()  const throw (const char *)
{
    if(empty())
        throw "ERROR: unable to access data from an empty list";

    return pTail->data;
}

/**********************************************
 * Front
 * Get the first element
 **********************************************/
template <class T>
T    List <T> :: front() const throw (const char *)
{
    if(empty())
        throw "ERROR: unable to access data from an empty list";

    return pHead->data;
}

/**********************************************
 * Insert
 * Insert t at the iterator position,
 * Return the iterator of the inserted node
 **********************************************/
template <class T>
ListIterator<T> List <T> :: insert(const ListIterator<T>& it, const T & t) throw (const char *)
{

    Node<T> *newNode = new(std::nothrow)Node<T>(t);
    if (!newNode)
        throw "ERROR: unable to allocate a new node for a list";

    Node<T> *pInsert = it.p;

    //we could reuse the push_front and push_back, but this method is used heavily
    //and I want it to be as fast as possible
    if(pInsert == NULL) //empty
    {
        newNode->pPrev = pTail;
        pTail = (pHead ? pTail->pNext : pHead) = newNode;
        //if there is a node, NULL in this case means the end of the list or insert when empty,push_back logic
    }
    else if (pInsert == pHead)  //first position
    {
        newNode->pNext = pHead;
        pHead = pHead->pPrev = newNode;
    }
    else  //somewhere in the middle
    {
        Node<T> *prevInsert = pInsert->pPrev;
        newNode->pNext = pInsert;
        newNode->pPrev = prevInsert;
        prevInsert->pNext = pInsert->pPrev = newNode;
    }

    numItems++;
    return ListIterator<T>(newNode);
}

/**********************************************
 * Remove
 * Remove node at the iterator position
 * Return iterator of the next node
 **********************************************/
template <class T>
ListIterator<T> List <T> :: remove(const ListIterator<T>& it) throw (const char *)
{
    if(empty())
        throw "ERROR: unable to remove from an empty list";

    if(it == this->end())
        throw "ERROR: unable to remove from an invalid location in a list";

    Node<T> *pDelete = it.p;
    ListIterator<T> nextIt;

    if(pHead == pTail) //only one node in
    {
        delete pTail;
        nextIt = pHead = pTail = NULL;
    }
    else if(pHead == pDelete) //first one, in a list of at least 2 nodes
    {
        Node<T> *nextHead = pHead->pNext;
        nextHead->pPrev = NULL;
        delete pHead;
        nextIt = pHead = nextHead;
    }
    else if(pTail == pDelete) //last one, in a list of at least 2 nodes
    {
        Node<T> *prevTail = pTail->pPrev;
        prevTail->pNext = NULL;
        delete pTail; //TODO  merge those
        pTail = prevTail;
        nextIt = NULL;
    }
    else //somewhere in the middle
    {
        Node<T> *prevDelete = pDelete->pPrev;
        Node<T> *nextDelete = pDelete->pNext;
        prevDelete->pNext = nextDelete;
        nextDelete->pPrev = prevDelete;
        delete pDelete;
        nextIt = nextDelete;
    }

    numItems--;
    return nextIt;
}

/**********************************************
 * SWAP
 * Swap this with rhs, by swapping just the
 * pointers in O(1)
 **********************************************/
template <class T>
void List <T> :: swap(List<T>& rhs)
{
    swapPointers(this->pHead,rhs.pHead);
    swapPointers(this->pTail,rhs.pTail);
    std::swap(this->numItems,rhs.numItems);
}

/**********************************************
 * SWAP
 * Swap two pointers
 **********************************************/
template <class T>
void List <T> :: swapPointers(Node<T>*& p, Node<T>*& q)
{
    Node<T>* temp = p;
    p = q;
    q = temp;
}

#endif /* LIST_H */

