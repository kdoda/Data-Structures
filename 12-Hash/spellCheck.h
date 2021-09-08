/***********************************************************************
 * Module:
 *    Week 12, Spell Check
 *    Brother Helfrich, CS 235
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This program will implement the spellCheck() function
 ************************************************************************/

#ifndef SPELL_CHECK_H
#define SPELL_CHECK_H

#include "hash.h"
#include <string>

/*******************************************************
* S HASH
* A simple hash of strings
*******************************************************/
class SHash : public Hash <std::string>
{
public:
    SHash(int numBuckets)    throw (const char *) : Hash <std::string> (numBuckets) {}
    SHash(const SHash & rhs) throw (const char *) : Hash <std::string> (rhs)        {}

    // hash function for strings
    unsigned int hash(const std::string & value) const
    {
        unsigned int hash = 0;
        for(const char *c = value.c_str();*c; ++c)
            hash = hash * 101 + *c;

        return hash % capacity();
    }

};
void spellCheck();

#endif // SPELL_CHECK_H
