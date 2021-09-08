/***********************************************************************
* Program:
*    Assignment 01, Go Fish
*    Brother Helfrich, CS 235
* Author:
*    Klevin Doda
* Summary: 
*    This is all the functions necessary to play Go Fish!
*
*    Estimated:  2.0 hrs
*    Actual:     1.0 hrs
************************************************************************/

#include <iostream>
#include <fstream>
#include "set.h"
#include "card.h"
#include "goFish.h"
using namespace std;


const int ROUNDS = 5;


/**********************************************
 * GOFISH a class representing the gofish game
 **********************************************/
class GoFish
{
private:
	Set<Card> cards;
	int matches;
public:
	GoFish()
    {
        matches = 0;
    }
    void display();
    bool guessCard(const Card & card);
    void readFile(string file);
};

/**********************************************
 * Guess the card of the user, if the card
 * is there delete it, and return if it is or not
 **********************************************/
bool GoFish :: guessCard(const Card & card)
{
	int it = cards.find(card);
    bool found = false;
	if (it != -1)
	{
		matches++;
		cards.erase(it);
		found = true;
	}

	return found;
}

/**********************************************
 * Read the cards from the file
 **********************************************/
void GoFish :: readFile(string file)
{
	ifstream fin(file.c_str());
	Card card;
	while (fin >> card)
		cards.insert(card);
	
	fin.close();
}

/********************************************************
 * Display how many cards did the user guess correctly
 * and the rest of the cards in the deck
 ********************************************************/
void GoFish :: display()
{
	cout << "You have " << matches << " matches!" << endl
		<< "The remaining cards: ";
    string toDisplay = "";
    SetIterator <Card> it = cards.begin();
    for(int i = 0;i < cards.size() - 1;++i,++it)
    {
        cout << *it << ", ";
    }
    cout << *it;
    
    cout << toDisplay << endl;
}

/**********************************************************************
* GO FISH
* The function which starts it all
***********************************************************************/
void goFish()
{
	cout << "We will play " << ROUNDS
         << " rounds of Go Fish.  Guess the card in the hand" << endl;
    
	Card card;
	GoFish goFish;
	goFish.readFile("/home/cs235e/week05/hand.txt");
	for (int i = 1; i <= ROUNDS; ++i)
	{
		cout << "round " << i << ": ";
		cin >> card;
		if (!goFish.guessCard(card))
            cout << "\tGo Fish!" << endl;
		else 
			cout << "\tYou got a match!" << endl;
	}
	goFish.display();
}
