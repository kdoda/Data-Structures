/***********************************************************************
* Program:
*    Week 11, Sorting
*    Brother Ercanbrack, CS 235
*
* Author:
*	Klevin Doda  
* Summary: 
*	External natural merge sort
************************************************************************/
#include <list>
#include <fstream>

using namespace std;

typedef list<int>::iterator listIterator;

/***********************************************************************
* MERGE
* Merge the two sorted sublists (iBegin1-iEnd1, iBegin2-iEnd2), into the 
* same list (iBegin1-iEnd2), by using a helper temporary list to merge
************************************************************************/
void merge(listIterator iBegin1, 
		   listIterator iBegin2, 
		   listIterator iEnd1, 
		   listIterator iEnd2)
{
	listIterator head = iBegin1;
	list<int> temp;

	while (iBegin1 != iEnd1 && iBegin2 != iEnd2) //post increment
			temp.push_back(*iBegin1 < *iBegin2 ? *iBegin1++ : *iBegin2++); 

	//copy the rest if iBegin1 finished first
	while (iBegin1 != iEnd1) 
		temp.push_back(*iBegin1++);

	//copy the rest if iBegin2 finished first
	while (iBegin2 != iEnd2) 
		temp.push_back(*iBegin2++);

	//copy back list temp to the original list that we are sorting
	//in the position noted by head now, that's why we stored it

	listIterator itTemp = temp.begin();
	while (head != iEnd2)
		*(head++) = *(itTemp++);
}

/*******************************
* READ FILE
* Read file into the list
*******************************/
void readFile(list<int> &l, char fileName[]) throw (const char *)
{
	ifstream fin(fileName);
	if (fin.fail())
		throw "ERROR: File could not be opened!";

	int number;
	while (fin >> number)
		l.push_back(number);

	fin.close();
}

/*********************************************
* PRINT
* Print the list in the screen according to
* the instructions
*********************************************/
void print(const list<int> &l)
{
 
	int i = 1;
	for (list<int>::const_iterator  it = l.begin();
		 it != l.end();
		 ++it, ++i)
	{
		cout << setw(3) << *it;
		if (i % 10 == 0)
			cout << endl;
	}
}

/*************************************************************************
* This function sorts a linked list using a External Natural Merge Sort.
* Input:  data -  linked list of data to be sorted.
* Output: data -  sorted linked list
**************************************************************************/
template<class T>
void mergeSort(list<T> &l)
{
	listIterator iBegin1, iBegin2, iEnd1, iEnd2; 
	int numMerges = 0;
  
  
	do
	{
    //find and merge while the whole list is sorted
		numMerges = 0;
		iBegin1 = l.begin();
		while (iBegin1 != l.end())
		{
      //find two sublists merge them, do this while all sublists are merge
			numMerges++;
			for (iEnd1 = next(iBegin1, 1); iEnd1 != l.end() && *prev(iEnd1, 1) <=
				*iEnd1; ++iEnd1)
				; //just move forward

			iBegin2 = iEnd1;

			 //the case when there is only one elemnet next throws error,that's why I'm checking here
			for (iEnd2 = iBegin2 != l.end() ? next(iBegin2, 1) : iBegin2; 
					iEnd2 != l.end() && *prev(iEnd2, 1) <= *iEnd2; 
				    ++iEnd2)
				; //just move forward
			
	    	//merge those and copy back to the positions starting from iBegin1
			if (iBegin2 != l.end())
				merge(iBegin1, iEnd1, iBegin2, iEnd2);
			
			iBegin1 = iEnd2;
		}

	} while (numMerges > 1);
}
