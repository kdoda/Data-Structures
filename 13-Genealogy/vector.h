#ifndef VECTOR_H
#define VECTOR_H

#include <cassert>


/************************************************
 * Vector
 * A class that holds stuff
 ***********************************************/
template <class T>
class Vector
{
  public:
   // default constructor : empty and kinda useless
   Vector() : cap(0), data(NULL) {}
   
   // copy constructor : copy it
   Vector(const Vector & rhs) throw (const char *);
   
   // non-default constructor : pre-allocate
   Vector(int cap) throw (const char *);
   
   // destructor : free everything
   ~Vector() { if (cap) delete[] data; }
   
   // assignment operator
   Vector & operator = (const Vector & rhs) throw (const char *);
   
   // what is the capacity
   int capacity() const { return this->cap; }

   T & operator [](int index) throw (const char *);
   const T & operator [](int index) const throw (const char *);

   void reallocate(int newCap) throw (const char *);

  private:
   int cap;               // capacity
   T * data;              // dynamically allocated array of T

};

/*******************************************
 * VECTOR :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Vector <T> :: Vector(const Vector <T> & rhs) throw (const char *)
{
    assert(rhs.cap >= 0);
    // do nothing if there is nothing to do
    if (rhs.cap == 0)
    {
        cap = 0;
        data = NULL;
        return;
    }
    // attempt to allocate
    try
    {
        data = new T[rhs.cap];
    }
    catch (std::bad_alloc)
    {
        throw "ERROR: Unable to allocate buffer";
    }
    // copy over the capacity and size
    assert(rhs.numItems >= 0 && rhs.numItems <= rhs.cap);
    cap = rhs.cap;

    // the rest needs to be filled with the default value for T
    for (int i = 0; i < cap; ++i)
       data[i] = rhs.data[i];
}

/*******************************************
 * VECTOR :: ASSIGNMENT
 *******************************************/
template <class T>
Vector<T> & Vector <T> :: operator = (const Vector<T> & rhs) throw (const char *)
{
    assert(rhs.cap >= 0);
    if(this == &rhs) return *this;

    delete []data;
    // do nothing if there is nothing to do
    if (rhs.cap == 0)
    {
        cap = 0;
        data = NULL;
        return *this;
    }

    // attempt to allocate
    data = new (std::nothrow) T[rhs.cap];
    if (!data)
        throw "ERROR: Unable to allocate a new buffer for Vector";
    
    // copy over the capacity and size
    assert(rhs.numItems >= 0 && rhs.numItems <= rhs.cap);
    cap = rhs.cap;

    // the rest needs to be filled with the default value for T
    for (int i = 0; i < cap; ++i)
        data[i] = rhs.data[i];
    
    return *this;
}

/**********************************************
 * VECTOR : NON-DEFAULT CONSTRUCTOR
 * Preallocate the container to "capacity"
 **********************************************/
template <class T>
Vector <T> ::Vector(int cap) throw (const char *)
{
    assert(cap >= 0);
    // do nothing if there is nothing to do
    if (cap == 0)
    {
        this->cap = 0;
        this->data = NULL;
        return;
    }
    // attempt to allocate
    try
    {
        data = new T[cap];
    }
    catch (std::bad_alloc)
    {
        throw "ERROR: Unable to allocate buffer";
    }
    // copy over the stuff
    this->cap = cap;

    // initialize the container by calling the default constructor
    for (int i = 0; i < cap; i++)
        data[i] = T();
}


/***************************************************
 * VECTOR :: REALLOCATE
 * reallocate to the new capacity
 **************************************************/
template <class T>
void Vector <T> ::reallocate(int newCap) throw (const char *)
{

    T * newData = new (std::nothrow) T[newCap];
    if (!newData)
        throw "ERROR: Unable to allocate a new buffer for Vector";
    
    for (int i = 0; i < cap; ++i)
       newData[i] = data[i];

    for (int i = cap; i < newCap; ++i)
       newData[i] = T(); //default value the rest

    cap = newCap;
    delete[] data; //free memory
    data = newData;
}


/***************************************************
 * VECTOR :: operator []
 * Returns the object by reference at the specifix index
 **************************************************/
template <class T>
T & Vector <T> :: operator [](int index) throw (const char *)
{
   if (cap <= index || index < 0)
      throw "ERROR: Invalid index";
   return data[index];
}

/***************************************************
 * VECTOR :: operator []
 * Returns the object by const reference at the specifix index
 **************************************************/
template <class T>
const T & Vector <T> :: operator [](int index) const throw (const char *)
{
   if (cap <= index || index < 0)
      throw "ERROR: Invalid index";
   return data[index];
}
#endif


