//
// Created by Klevin Doda on 11/9/18.
//

#ifndef HASH_H
#define HASH_H

#include "list.h"
#include <vector>
#include <cassert>

/***********************************************
 * Abstract class Hash
 ***********************************************/
template <class T>
class Hash
{
public:
    Hash() : numItems(0) { }
    Hash(int numBuckets) throw (const char *);
    Hash(const Hash & rhs) throw (const char *);
    ~Hash() {  }
    Hash & operator = (const Hash & rhs) throw (const char *);

    int capacity() const { return table.size(); }
    int size() const { return numItems; }
    void clear();
    bool empty() const { return numItems == 0; }
    bool find(const T &t);
    void insert(const T &t);
    virtual unsigned int hash(const T &t) const = 0;
private:
    std::vector<List<T>> table;
    int numItems;

};

/***********************************************
 * Non-default constructor
 ***********************************************/
template <class T>
Hash<T> :: Hash(int numBuckets) throw (const char *)
{
    assert(numBuckets >= 0);
    this->numItems = 0;
    if (numBuckets == 0)
        return;

    try
    {
        table.resize(numBuckets);
    }
    catch (std::bad_alloc)
    {
        throw "ERROR: Unable to allocate memory for the hash.";
    }
}

/***********************************************
 * Copy constructor
 ***********************************************/
template <class T>
Hash<T> :: Hash(const Hash & rhs) throw (const char *)
{
    if(rhs.capacity() == 0)
        return;

    this->numItems = rhs.size();

    try
    {
        this->table = rhs.table;
    }
    catch (std::bad_alloc)
    {
        throw "ERROR: Unable to allocate memory for the hash.";
    }
}

/***********************************************
 * Assignment operator
 ***********************************************/
template <class T>
Hash<T> & Hash<T> :: operator = (const Hash<T> & rhs) throw (const char *)
{
    if (this == &rhs)
        return *this;

    this->numItems = rhs.size();
    this->table = rhs.table;
    return *this;
}

/***********************************************
 * Find
 * Check if the t is inside the Hash containter
 ***********************************************/
template <class T>
bool Hash<T> :: find(const T &t)
{
    int index = hash(t);
    return table[index].contains(t);
}

/***********************************************
 * Insert
 * Insert t in hash container if it's not already
 ***********************************************/
template <class T>
void Hash<T> :: insert(const T &t)
{

//    if we want a good implementation
//    if(numItems * 1.5 > capacity())
//        table.resize(capacity() * 1.5);

    int index = hash(t);
    if (!table[index].contains(t))
    {
        table[index].push_back(t);  //O(1)
        numItems++;
    }
}

/***********************************************
 * Clear
 * Clear all elements from the hash container
 ***********************************************/
template <class T>
void Hash<T> :: clear()
{
    for(int i = 0;i < table.size(); ++i)
        table[i].clear();

    numItems = 0;
}

#endif //HASH_H

