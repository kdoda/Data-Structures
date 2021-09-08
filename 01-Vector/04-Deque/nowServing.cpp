/***********************************************************************
 * Implementation:
 *    NOW SERVING
 * Summary:
 *    This will contain the implementation for nowServing() as well as any
 *    other function or class implementations you may need
 * Author
 *    Klevin Doda
 **********************************************************************/

#include <iostream>     // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>       // for STRING
#include <cassert>      // for ASSERT
#include "nowServing.h" // for nowServing() prototype
#include "deque.h"      // for DEQUE
using namespace std;

/************************************************
 * STUDENT
 * A class representing a student to be served
 ***********************************************/
class Student
{
public:
    Student()
    : isEmergency(false),time(0)
    { }
private:
    bool isEmergency;
    string name;
    string csClass;
    int time;
    
    friend class NowServing;
};

/************************************************
 * NOWSERVING
 * A class that serves to student and keeps
 * track about it.
 ***********************************************/
class NowServing
{
public:
    NowServing() { }
    void display();
    void getStudent(string input);
    void serve();
    
private:
    Student current; //current student being served
    Deque<Student> toServe;
    void addToServe(Student s);
};

/************************************************
 * NOWSERVING
 * Display the current student being served on
 * the screen.
 ***********************************************/
void NowServing :: display()
{
   if(current.time > 0)
   {
       cout << (current.isEmergency ? "\tEmergency for " : "\tCurrently serving ")
            << current.name << " for class " << current.csClass << ". Time left: "
            << current.time  << endl;
   }
    
    --current.time;
}

/************************************************
 * NOWSERVING
 * Serve to the current student
 ***********************************************/
void NowServing :: serve()
{
    if(current.time <= 0 && !toServe.empty())
    {
        current = toServe.front();
        toServe.pop_front();
    }
}

/************************************************
 * NOWSERVING
 * Get the student, name, class , time, and
 * if it is an emergency.
 ***********************************************/
void NowServing :: getStudent(string input)
{
    Student s;
    if(input == "!!")
    {
        s.isEmergency = true;
        cin >> s.csClass;
    }else
    {
        s.isEmergency = false;
        s.csClass = input;
    }
    
    cin >> s.name >> s.time;
    addToServe(s);
}

/************************************************
 * NOW SERVING
 * Add the student to be served on the deque
 * Takes care about the emergency student.
 ***********************************************/
void NowServing :: addToServe(Student s)
{
    if(s.isEmergency)
        toServe.push_front(s);
    else
        toServe.push_back(s);
}

/************************************************
 * NOW SERVING
 * The interactive function allowing the user to
 * handle help requests in the Linux lab
 ***********************************************/
void nowServing()
{
    // instructions
    cout << "Every prompt is one minute.  The following input is accepted:\n";
    cout << "\t<class> <name> <#minutes>    : a normal help request\n";
    cout << "\t!! <class> <name> <#minutes> : an emergency help request\n";
    cout << "\tnone                         : no new request this minute\n";
    cout << "\tfinished                     : end simulation\n";
    
    NowServing serving;
    // your code here
    string input;
    for(int i = 0;;++i)
    {
        cout << "<" << i << "> ";
        cin >> input;
        if(input == "finished")
            break;
        else if(input == "none")
            ;
        else
            serving.getStudent(input);
        
        serving.serve();
        serving.display();
    }
    // end
    cout << "End of simulation\n";
}
