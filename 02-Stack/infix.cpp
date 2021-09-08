/***********************************************************************
 * Module:
 *    Week 02, Stack
 *    Brother Ercanbrack, CS 235
 * Author:
 *    Klevin Doda
 * Summary:
 *    This program will implement the testInfixToPostfix()
 *    and testInfixToAssembly() functions
 ************************************************************************/

#include <iostream>    // for ISTREAM and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include <string>
#include <vector>
#include <sstream>
#include "stack.h"

#include "stack.h"     // for STACK
using namespace std;

/*****************************************************
 * Operator weights, custom define, used for the logic
 * from infix to postfix
 *****************************************************/
int operatorWeight(char op)
{
    //an unordered_map would be way cleaner, but it doesn't compile in the linux lab
    switch (op)
    {
        case ')':
            return -1;
        case '+':
        case '-':
            return 1;
        case '%':
        case '/':
        case '*':
            return 2;
        case '^':
            return 3;
        case '(':
            return 4;
        default:
            return 0;
    }
}

/*****************************************************
 * Is it higher level order, eg. * - returns true
 *****************************************************/
bool higherLevelOrder(string c1, string c2)
{
    return operatorWeight(c1[0]) >= operatorWeight(c2[0]);
}

/*****************************************************
 * Is it an math operator eg. + - / ...
 *****************************************************/
bool isOperator(char op)
{
    //the numbers evaluate to true, we could call this method righ way
    //but it offers a level of abstraction and a better name
    return operatorWeight(op);
}

/*****************************************************
 * Parse the string into an array of tokens
 *****************************************************/
void parseInfix(vector<string>& infixV, string infix)
{
    char c;
    stringstream ss(infix);
    
    while (ss >> skipws >> c) //skip white spaces
    {
        if (!isOperator(c))
        {
            string token(1,c); //get the rest
            while (ss >> noskipws >> c && c != ' ' && !isOperator(c)) //dont skip white spaces so we know when to stop
                token.push_back(c);
            
            infixV.push_back(token);
        }
        if (isOperator(c)) //because we read one more (the last one) in the nested while loop
            infixV.push_back(string(1, c));
    }
}

/*****************************************************
 * Pops from the stack and returns the values as a string
 *****************************************************/
string toString(Stack<string> &s)
{
    string operators = "";
    while (!s.empty() && s.top() != "(")
    {
        operators += " " + s.top();
        s.pop();
    }
    return operators;
}

/*****************************************************
 * CONVERT INFIX TO POSTFIX
 * Convert infix equation "5 + 2" into postifx "5 2 +"
 *****************************************************/
string convertInfixToPostfix(const string & infix)
{
    string postfix = "";
    vector<string> infixV;
    parseInfix(infixV, infix);
    Stack<string> s;
    
    for (int i = 0; i < infixV.size(); ++i)
    {
        if (isOperator(infixV[i][0]))
        {
            if (!s.empty() && higherLevelOrder(s.top(), infixV[i]))
                postfix += toString(s);
            
            infixV[i] == ")" ? s.pop() : s.push(infixV[i]); //pop the )
        }
        else
        {
            postfix += " " + infixV[i];
        }
    }
    postfix += toString(s); // the last values of the stack
    
    return postfix;
}

/*****************************************************
 * TEST INFIX TO POSTFIX
 * Prompt the user for infix text and display the
 * equivalent postfix expression
 *****************************************************/
void testInfixToPostfix()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";
   
   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }
      
      // prompt for infix
      cout << "infix > ";
      getline(cin, input);

      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << "\tpostfix: " << postfix << endl << endl;
      }
   }
   while (input != "quit");
}

/**********************************************
 * CONVERT POSTFIX TO ASSEMBLY
 * Convert postfix "5 2 +" to assembly:
 *     LOAD 5
 *     ADD 2
 *     STORE VALUE1
 **********************************************/
string convertPostfixToAssembly(const string & postfix)
{
   string assembly;

   return assembly;
}

/*****************************************************
 * TEST INFIX TO ASSEMBLY
 * Prompt the user for infix text and display the
 * resulting assembly instructions
 *****************************************************/
void testInfixToAssembly()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";

   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }
      
      // prompt for infix
      cout << "infix > ";
      getline(cin, input);
      
      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << convertPostfixToAssembly(postfix);
      }
   }
   while (input != "quit");
      
}
