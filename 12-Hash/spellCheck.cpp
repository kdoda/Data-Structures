/***********************************************************************
 * Module:
 *    Week 12, Spell Check
 *    Brother Helfrich, CS 235
 * Author:
 *    Klevin Doda
 * Summary:
 *    This program will implement the spellCheck() function
 ************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <fstream>

#include "spellCheck.h"

using namespace std;

/**************************************************
 * GetFileName
 * Get the name of the file to check from the user
 *************************************************/
string getFileName()
{
    string fileName;
    cout << "What file do you want to check? ";
    cin >> fileName;
    return  fileName;
}

/**************************************************
 * ReadFile
 * Read the file in the SHash
 *************************************************/
void readFile(SHash &set,const string& fileName)
{
    ifstream fin(fileName.c_str());
    if (fin.fail())
        throw "ERROR opening file!";

    string word;
    while (fin >> word)
        set.insert(word);
}

/**************************************************
 * SpellCheckFile
 * Print all the words from the file that are not in
 * SHash
 *************************************************/
void spellCheckFile(SHash &set,const string& fileName)
{
    ifstream fin(fileName.c_str());
    if(fin.fail())
        cout << "ERROR opening file!";

    string word;
    bool printFirst = false;
    while(fin >> word)
    {
        char firstLetter = word[0];
        word[0] = tolower(firstLetter);

        if (!set.find(word))
        {
            if(printFirst)
            {
                cout << ", ";
            }
            else
            {
                cout << "Misspelled: ";
                printFirst = true;
            }

            word[0] = firstLetter;
            cout << word;
        }
    }
    if(!printFirst)
        cout << "File contains no spelling errors";

    cout << endl;
}


/*****************************************
 * SPELL CHECK
 * Prompt the user for a file to spell-check
 ****************************************/
void spellCheck()
{
    string fileName = getFileName();
    /*
     * Picked this number since it's prime and roughly 1.5 times greater
     * than the number of english word in dictionary
     */
    SHash set(52289);
    readFile(set,"/home/cs235/week12/dictionary.txt");
    spellCheckFile(set,fileName);
}
