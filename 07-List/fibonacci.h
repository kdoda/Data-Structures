/***********************************************************************
 * Header:
 *    FIBONACCI
 * Summary:
 *    This will contain just the prototype for fibonacci(). You may
 *    want to put other class definitions here as well.
 * Author
 *    Klevin Doda
 ************************************************************************/

#ifndef FIBONACCI_H
#define FIBONACCI_H

#include <stdio.h>
#include "list.h"


/*****************************************************************
 *    WholeNumber
 *    Representing Wholenumber,a class that can hold a huge integer
 *    Since there is no pointer involved,
 *    there is no need for the rule of 3 here
 *****************************************************************/
class WholeNumber
{
public:
    //default constructor
    WholeNumber(){}

    //non-default constructor
    WholeNumber(unsigned int);

    //copy constructor
    WholeNumber(const WholeNumber& rhs);

    //desctructors
    ~WholeNumber(){}

    //operators
    WholeNumber& operator = (const WholeNumber& rhs) throw (const char *);
    WholeNumber& operator = (unsigned int number) throw (const char *);
    WholeNumber& operator += (const WholeNumber& rhs) throw (const char *);
    WholeNumber  operator + (const WholeNumber& rhs) throw (const char *);

    void swap(WholeNumber& rhs) { this->parts.swap(rhs.parts); }
    friend std::ostream& operator<< (std::ostream& stream, const WholeNumber& rhs);
private:
    List<short> parts; //3 digit parts of the whole number
    void parseNumber(unsigned int number);
    short parseLast3Digits(unsigned int &number);
};


// the interactive fibonacci program
void fibonacci();

#endif //FIBONACCI_H
