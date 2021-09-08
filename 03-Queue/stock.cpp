/***********************************************************************
 * Implementation:
 *    STOCK
 * Summary:
 *    This will contain the implementation for stocksBuySell() as well
 *    as any other function or class implementation you need
 * Author
 *    Klevin Doda
 **********************************************************************/

#include <iostream>    // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include "stock.h"     // for STOCK_TRANSACTION
#include "queue.h"     // for QUEUE
#include "dollars.h"     // for QUEUE
using namespace std;


/***********************************************************************
 * TRANSACTION
 * A class that represents a transcation
 **********************************************************************/
class Transaction
{
private:
    int shares;      //number of shares
    Dollars price;   //price per share
    Dollars profit;  //used only for selling transaction
    
public:
   Transaction(): shares(0) {}
   Transaction(int shares,Dollars price)
         : shares(shares), price(price), profit(0){ }
   Transaction(int shares, Dollars soldPrice, Dollars boughtPrice)
         : shares(shares),price(soldPrice),profit((soldPrice - boughtPrice) * shares) {  }
   friend class Portfolio;
};

/***********************************************************************
 * PORTFOLOI
 * A class that holds the history of transactions
 **********************************************************************/
class Portfolio
{
private:
    Queue<Transaction> bought;
    Queue<Transaction> sold;
    static char getComparisonOperator(int);
public:
    void buy(Transaction);
    void sell(Transaction);
    void display();
};

/***********************************************************************
 * PORTFOLOI :: GET DIFFERE
 * Get the comparisson operator based on the difference passed
 **********************************************************************/
char Portfolio::getComparisonOperator(int difference)
{
    if(difference == 0)
        return '=';
    else if(difference < 0)
        return '<';
    else
        return '>';
}

/***********************************************************************
 * PORTFOLOI :: BUY
 * Buy the transaction
 **********************************************************************/
void Portfolio::buy(Transaction t)
{
    bought.push(t);
}

/***********************************************************************
 * PORTFOLOI :: SELL
 * Sell the transaction
 **********************************************************************/
void Portfolio::sell(Transaction t)
{

   for(;;)
   {
      Transaction e = bought.front(); //e for the earliest transaction
      char cOperator = getComparisonOperator(e.shares - t.shares); //to determine the three cases, when you sell a transaction
      switch(cOperator)
      {
         case '=': //selling the same number of shares as the earliest transaction
            bought.pop();
            sold.push(Transaction(e.shares,t.price,e.price));
            return;
         case '<': //selling more than the number of shares as the earliest transaction
            bought.pop();
            t.shares -= e.shares; //sold those
            sold.push(Transaction(e.shares,t.price,e.price));
            break;
         case '>':
            bought.front().shares -= t.shares;
            sold.push(Transaction(t.shares,t.price,e.price));
            return;
         default: //shouldn't ever hit this line
            return;
      }
   }
}

/***********************************************************************
 * PORTFOLOI :: DISPLAY
 * Display the history of the portfolio
 **********************************************************************/
void Portfolio::display()
{
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);
    Dollars proceeds = 0;
    if(!bought.empty())
    {
        cout << "Currently held:" << endl;
        Queue<Transaction> copy(bought);
        while(!copy.empty())
        {
            cout << "\tBought " << copy.front().shares << " shares at " << copy.front().price << endl;
            copy.pop();
        }
    }
    
    if(!sold.empty())
    {
        cout << "Sell History:" << endl;
        Queue<Transaction> copy(sold);
        while(!copy.empty())
        {
            proceeds += copy.front().profit;
            cout << "\tSold " << copy.front().shares << " shares at "
                << copy.front().price << " for a profit of " << copy.front().profit << endl;
            copy.pop();
        }
    }
    cout << "Proceeds: " << proceeds << endl;
}

/************************************************
 * GET Transaction
 * Get the trasaction from the user
 ***********************************************/
Transaction getTransaction()
{
    //we could do sth fancier by overloading the >> operator
    int shares;
    Dollars price;
    cin >> shares >> price;
    return Transaction(shares,price);
}

/************************************************
 * STOCKS BUY SELL
 * The interactive function allowing the user to
 * buy and sell stocks
 ***********************************************/
void stocksBuySell()
{
    // instructions
    cout << "This program will allow you to buy and sell stocks. "
    << "The actions are:\n";
    cout << "  buy 200 $1.57   - Buy 200 shares at $1.57\n";
    cout << "  sell 150 $2.15  - Sell 150 shares at $2.15\n";
    cout << "  display         - Display your current stock portfolio\n";
    cout << "  quit            - Display a final report and quit the program\n";
    
    // your code here...
    Portfolio portfolio;
    
    string command;
    do
    {
        cout << "> ";
        cin  >> command;
        if (command == "buy")
            portfolio.buy(getTransaction());
        else if (command == "sell")
            portfolio.sell(getTransaction());
        else if (command == "display")
            portfolio.display();
    }
    while (command != "quit");
}
