#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <iostream>
#include <cassert>

// forward declaration for ContainerIterator
template <class T>
class SetIterator;

/************************************************
* SET
* A class that represents SET ADT,
* implemented using a sorted array
***********************************************/
template <class T>
class Set
{
public:
	// default constructor : empty and kinda useless
    Set() : numCapacity(0),numItems(0),data(NULL) {  }

	// copy constructor : copy it
	Set(const Set & rhs) throw (const char *);

	// non-default constructor : pre-allocate
	Set(int numCapacity) throw (const char *);

	// destructor : free everything
	~Set() { delete[] data; }

	// assignment operator
	Set & operator = (const Set & rhs) throw (const char *);

	// is the set currently empty
	bool empty() const { return numItems == 0; }

	// what is the capacity
	int capacity() const { return numCapacity; }

	// remove all the items from the set
	void clear() { numItems = 0; }

	// how many items are currently in the set?
	int size() const { return numItems; }

	// add an item to the set, if not there
	void insert(const T & t) throw (const char *);

	// find where is this element
	int find(const T & t) const;

	// erase if exist element
	void erase(int);

	// the intersection operator
	Set operator&&(const Set & rhs);

	// the union operator
	Set operator||(const Set & rhs);

	// return an iterator to the beginning of the list
	SetIterator <T> begin() { return SetIterator<T>(data); }

	// return an iterator to the end of the list
	SetIterator <T> end() { return SetIterator<T>(data + numItems); }

private:
	int numItems;          // how many items are currently in the Container?
	int numCapacity;       // how many items can I put on the Container before full?
	T * data;              // dynamically allocated array of T
	void reallocate(int numCapacity) throw (const char *);
	int findIndex(const T& t) const;
};

/**************************************************
* SET ITERATOR
* An iterator through VECTOR
*************************************************/
template <class T>
class SetIterator
{
public:
	// default constructor
	SetIterator() : p(NULL) {}

	// copy constructor
	SetIterator(const SetIterator& rhs) { this->p = rhs.p; }

	// initialize to direct p to some item
	SetIterator(T * p) : p(p) {}

	// equal operator
	bool operator == (const SetIterator & rhs) const
	{
		return rhs.p == this->p;
	}

	// assignment operator
	SetIterator<T> & operator = (const SetIterator & rhs)
	{
		this->p = rhs.p;
		return *this;
	}

	// not equals operator
	bool operator != (const SetIterator & rhs) const
	{
		return rhs.p != this->p;
	}

	// dereference operator
	T & operator * ()
	{
		return *p;
	}

	// prefix increment
	SetIterator <T> & operator ++ ()
	{
		p++;
		return *this;
	}

	// postfix increment
	SetIterator <T> operator++(int postfix)
	{
		SetIterator tmp(*this);
		p++;
		return tmp;
	}

private:
	T * p;
};

/**********************************************
* SET : NON-DEFAULT CONSTRUCTOR
* Preallocate the container to "capacity"
**********************************************/
template <class T>
Set <T> :: Set(int numCapacity) throw (const char *)
{
	assert(numCapacity >= 0);
    numItems = 0;
    this->numCapacity = numCapacity;
    data = NULL;
	reallocate(numCapacity);
}

/*******************************************
* SET :: COPY CONSTRUCTOR
*******************************************/
template <class T>
Set <T> ::Set(const Set <T> & rhs) throw (const char *)
{
	assert(rhs.numCapacity >= 0);
    numItems = 0;
    this->numCapacity = 0;
    data = NULL;
    
        reallocate(rhs.numCapacity);
        
        // copy over size
        assert(rhs.size() >= 0 && rhs.size() <= rhs.capacity());
        this->numItems = rhs.numItems;
        this->numCapacity = rhs.numCapacity;
        
        // copy the items over one at a time using the assignment operator
        for (int i = 0; i < numItems; ++i)
            data[i] = rhs.data[i];
}

/*******************************************
* SET :: ASSIGNMENT
*******************************************/
template <class T>
Set<T> & Set <T> :: operator = (const Set<T> & rhs) throw (const char *)
{
	assert(rhs.numCapacity >= 0);
	if (this == &rhs) return *this;
    
    if (numCapacity < rhs.numCapacity)
        reallocate(rhs.numCapacity);
        
        // copy over size
        assert(rhs.size() >= 0 && rhs.size() <= rhs.capacity());
        this->numItems = rhs.numItems;
        this->numCapacity = rhs.numCapacity;
        
        // copy the items over one at a time using the assignment operator
        for (int i = 0; i < numItems; ++i)
            data[i] = rhs.data[i];
            
            return *this;
}

/***********************************************************
* SET : FIND INDEX
* Search the element using binary search,
* It will return the position where the t should be inserted
************************************************************/
template <class T>
int Set <T> ::findIndex(const T& t) const
{
	int low = 0;              //left
	int high = numItems - 1;   //right

	while (low <= high)
	{
		int m = low + (high - low) / 2; //for overflow

		if (data[m] == t)
			return m;

		if (data[m] < t)
			low = m + 1;
		else
			high = m - 1;
	}
	return low;
}

/**********************************************************
* SET :: INSERT
* Insert t to the position it belongs to, so the array
* remains sorted.
***********************************************************/
template <class T>
void Set <T> ::insert(const T & t) throw (const char *)
{
	if (numItems == numCapacity)
    {
        if(numCapacity != 0)
            reallocate(2 * numCapacity);
        else
            reallocate(1);
    }

	int iInsert = findIndex(t);
	if (iInsert == numItems || data[iInsert] != t)
	{
		for (int i = numItems - 1; i >= iInsert; --i)
			data[i + 1] = data[i];

		data[iInsert] = t;
		numItems++;
	}
}

/***************************************************
* SET :: REALLOCATE
* reallocate to the new capacity
**************************************************/
template <class T>
void Set <T> ::reallocate(int numCapacity) throw (const char *)
{
    this->numCapacity = numCapacity;
	T * newData = NULL;
	if (numCapacity != 0)
	{
		newData = new (std::nothrow) T[numCapacity];
		if (!newData)
			throw "ERROR: Unable to allocate a new buffer for Set";

		for (int i = 0; i < numItems; ++i)
			newData[i] = data[i];
	}

	delete[] data; //free memory
	data = newData;
}

/***************************************************
 * SET :: FIND
 * Find if t is in the set,return it's index or -1
 * if it doesn't exist.
 **************************************************/
template <class T>
int Set <T> ::find(const T & t) const
{
	int i = findIndex(t);
	if( i != numItems && data[i] == t )
        return i;
        
    return -1;
}

/***************************************************
 * SET :: ERASE
 * Erase the element at the index if exist
 **************************************************/
template <class T>
void Set <T> ::erase(int iErase)
{
	assert(iErase >= 0);
	
		for (int i = iErase; i < numItems - 1; ++i)
			data[i] = data[i + 1];

		numItems--;
	
}

/*******************************************************
 * SET :: INTERSECTION
 * return the intersection of the two sets in a new one
 *******************************************************/
template <class T>
Set<T> Set <T> :: operator&&(const Set & rhs)
{
	Set temp;
  
    for(int i = 0; i < this->numItems; ++i)
    {
        if(rhs.find(data[i]) != -1)
            temp.insert(data[i]);
    }
     
	return temp;
}

/*******************************************************
 * SET :: UNION
 * return the union of the two sets in a new one
 *******************************************************/
template <class T>
Set<T> Set <T> :: operator||(const Set & rhs)
{
	Set temp = rhs;
 
    for(int i = 0; i < numItems; ++i)
        temp.insert(data[i]);
   
	return temp;
}

#endif
