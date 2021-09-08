#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <cassert>

/**********************************************
 * Stack : Implementation of stack ADT
 **********************************************/
template <class T>
class Stack{
   
public:
    // default constructor : empty and kinda useless
    Stack() : _size(0), _capacity(0), data(NULL) {}
    // non-default constructor : empty and kinda useless
    Stack(int capicity) throw (const char *);
    Stack(const Stack& rhs) throw (const char *);
    // destructor : free everything
    ~Stack() { if (_capacity) delete[] data; }
    //assignment operator
    Stack & operator = (const Stack & rhs) throw (const char *);
    //is it empty?
    bool empty()    const { return _size == 0; }
    //can you give me the size please?
    int  size()     const { return _size;   }
    //can you give me the capicity please?
    int  capacity() const { return _capacity;  }
    //clear the stuff but keep the capicity
    void clear ()         { _size = 0;          }
    
    void push(const T& t) throw (const char *);
    void pop() throw (const char *);
    T& top() throw (const char *);
    
private:
    T * data;
    int _capacity;
    int _size;

    bool isFull() { return _size == _capacity; } 
    void setDefault(int = 0);
    void copy(const Stack<T> & rhs) throw (const char *);
    void reallocate(int capacity) throw (const char *);
};

/**********************************************
 * Stack : SET DEFAULT
 * Set private members to default values
 **********************************************/
template <class T>
void Stack <T> :: setDefault(int capacity)
{
    _size = 0;
    _capacity = capacity;
    data = NULL;
}

/**********************************************
 * Stack : NON-DEFAULT CONSTRUCTOR
 * Preallocate the container to "capacity"
 **********************************************/
template <class T>
Stack <T> :: Stack(int capacity) throw (const char *)
{
   assert(capacity >= 0);
   setDefault(capacity);
   // do nothing if there is nothing to do
   if (capacity == 0)
      return;
   
   data = new (std::nothrow) T[capacity];
   if(!data)
      throw "ERROR: Unable to allocate a new buffer for Stack";
}

/**********************************************
 * Stack : ASSIGNMENT
 **********************************************/
template <class T>
Stack<T> & Stack <T> :: operator = (const Stack<T> & rhs) throw (const char *)
{
    assert(rhs.capacity() >= 0);
    if(this == &rhs) return *this;
    // do nothing if there is nothing to do
    if (rhs.capacity() == 0)
    {
        delete []data;
        setDefault();
        return *this;
    }
    
    copy(rhs);
    return *this;
}

/**********************************************
 * Stack : COPY CONSTRUCTOR
 **********************************************/
template <class T>
Stack <T> :: Stack(const Stack<T> & rhs) throw (const char *)
{
    assert(rhs.capacity() >= 0);
    setDefault();
    
    // do nothing if there is nothing to do
    if (rhs.capacity() == 0)
        return;
    
    copy(rhs);
}

/**********************************************
 * Stack : COPY the rest of the array
 **********************************************/
template <class T>
void Stack <T> :: copy(const Stack<T> & rhs) throw (const char *)
{
    if(_capacity < rhs.size()) //allocate a new one only if we need one
    {
       //used only for the assignment operator, but used for less code
        delete []data; //delete the exisiting array( C++ checks for you if null)
        
        _capacity = rhs.size(); //if capacity is enough leave the old one
        // attempt to allocate
        data = new (std::nothrow) T[rhs.size()]; //the size not the capacity!
        if (!data)
            throw "ERROR: Unable to allocate a new buffer for Stack";
    }
    
    // copy over and size
    assert(rhs.size() >= 0 && rhs.size() <= rhs.capacity());
    _size = rhs.size();
    
    // copy the items over one at a time using the assignment operator
    for (int i = 0; i < _size; ++i)
        data[i] = rhs.data[i];
}
   
/**********************************************
 * Stack : REALLOCATE
 * Reallocte to the new capacity
 **********************************************/
template <class T>
void Stack <T> :: reallocate(int capacity) throw (const char *)
{
   _capacity = capacity;
   T * newData = new (std::nothrow) T[capacity];
   if (!newData)
      throw "ERROR: Unable to allocate a new buffer for Stack";
    
   for (int i = 0; i < _size; ++i)
      newData[i] = data[i];
        
   delete[]data; //free memory
   data = newData;
}

/**********************************************
 * Stack : PUSH
 * Push on top of the stack
 **********************************************/
template <class T>
void Stack <T> :: push(const T& t) throw (const char *)
{
   if(isFull())
        reallocate(_capacity ? _capacity * 2 : 1);
        
    data[_size++] = t;
}

/**********************************************
 * Stack : POP
 * Pop from the top of the stack
 **********************************************/
template <class T>
void Stack <T> :: pop() throw (const char *)
{
    if(empty())
        throw "ERROR: Unable to pop from an empty Stack";

    _size--;
}

/**********************************************
 * Stack : TOP
 * Get the top of the stack by reference so
 * that it is a get and set.
 **********************************************/
template <class T>
T& Stack <T> :: top() throw (const char *)
{
    if(empty())
        throw "ERROR: Unable to reference the element from an empty Stack";
    
    return data[_size - 1];
}

#endif /* Stack_h */
