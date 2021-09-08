#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <fstream>
#include <sstream>

/******************************************************
 * PERSON CLASS
 * Represents an Individual in the Genealogy Tree
 *****************************************************/
class Person
{
private:

    std::string getYear(const std::string &date)
    {
        std::string part;
        std::stringstream ss(date);
        while (ss >> part)
            ;

        return part; //return the last part, which is the year
    }

    std::string toLower(const std::string& s)
    {
        std::string temp(s);
        for(int i = 0;i < temp.size();++i)
            temp[i] = tolower(temp[i]);

        return temp;
    }

public:

    int id;
    std::string givenName;
    std::string surname;
    std::string birthdate;

//    int getId() const                                { return id;                   }
//    void setId(int id)                               { this->id = id;               }
//
//    std::string getGivenName() const                 { return givenName;            }
//    void setGivenName(const std::string &givenName)  { this->givenName = givenName; }
//
//    std::string getSurname() const                   { return surname;              }
//    void setSurname(const std::string &surname)      { this->surname = surname;     }
//
//    std::string getBirthdate() const                 { return birthdate;            }
//    void  setBirthdate(const std::string &birthdate) { this->birthdate = birthdate; }

    bool operator< (const Person& rhs);
    std::string getFullName() const;
    std::string toString() const;


    friend std::ostream&  operator<< (std::ostream& stream,  const Person& person);
    friend std::ofstream& operator<< (std::ofstream& stream, const Person& person);
};


/******************************************************
 * < Operator
 * Used for sorting
 *****************************************************/
bool Person::operator< (const Person& rhs)
{
    //do this conversion only onces
    std::string thisSurname = this->toLower(this->surname);
    std::string rhsSurname  = this->toLower(rhs.surname);
    std::string thisGiven   = this->toLower(this->givenName);
    std::string rhsGiven    = this->toLower(rhs.givenName);

    //assuming that there are not to person with the same surname && givenName && same birthday year
    return  (thisSurname < rhsSurname) ||
            (thisSurname == rhsSurname && thisGiven < rhsGiven) ||
            (thisSurname == rhsSurname && thisGiven == rhsGiven
             && getYear(this->birthdate) < getYear(rhs.birthdate));

}

/******************************************************
 * << Operator
 * Used to print the person to the console
 *****************************************************/
std::ostream&  operator<< (std::ostream& out,  const Person& person)
{
    out << person.toString();
    return out;
}

/******************************************************
 * << Operator
 * Used to print the person to a file
 *****************************************************/
std::ofstream& operator<< (std::ofstream& out, const Person& person)
{
    out << person.toString();
    return out;
}

/******************************************************
 * TO STRING
 * Get the representation of the person as a string
 *****************************************************/
std::string Person::getFullName() const
{
    return givenName +
           (!givenName.empty() && !surname.empty() ? " " : "") +
           surname;
}


/******************************************************
 * TO STRING
 * Get the representation of the person as a string
 *****************************************************/
std::string Person::toString() const
{
    return getFullName() +
           (!birthdate.empty() ?  ", b. " : "") +
           birthdate;
}

#endif
