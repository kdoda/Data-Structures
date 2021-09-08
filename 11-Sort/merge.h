/***********************************************************************
* Program:
*    Week 11, Sorting
*    Brother Ercanbrack, CS 235
*
* Author:
* Klevin Doda
* Summary:
* External natural merge sort
************************************************************************/
#include <list>
#include <fstream>
#include <iomanip>
#include <iostream>

/*******************************
* READ FILE
* Read file into the list
*******************************/
void readFile(std::list<int> &l, char fileName[]) throw (const char *)
{
	std::ifstream fin(fileName);
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
void print(const std::list<int> &l)
{

	int i = 1;
	for (std::list<int>::const_iterator  it = l.begin();
		it != l.end();
		++it, ++i)
	{
		std::cout << std::setw(3) << *it;
		if (i % 10 == 0)
			std::cout << std::endl;
	}
}

/***********************************************************************
* MERGE
* Merge the two sorted sublists into the list starting from iDestionation
* Receive the iDestination by reference since we want the update 
* the iterator in mergesort because when we merge the next two sublists
* we want to continue were we left in the destination merged list
************************************************************************/
template <typename T>
void merge(typename std::list<T>::iterator &iDestination,
  	typename std::list<T>::iterator iBegin1,
  	typename std::list<T>::iterator iBegin2,
  	typename std::list<T>::iterator iEnd1,
  	typename std::list<T>::iterator iEnd2)
{
	//we are sure iDestination doesn't go out of bound since they both have the same size
	while (iBegin1 != iEnd1 || iBegin2 != iEnd2)
	{
		if (iBegin1 != iEnd1 && (iBegin2 == iEnd2 || *iBegin1 < *iBegin2))
			*iDestination++ = *iBegin1++; //move both the iterators post increment
		else
			*iDestination++ = *iBegin2++; //move both the iterators post increment
	}
}

/*************************************************************************
* This function sorts a linked list using a External Natural Merge Sort.
* Input:  data -  linked list of data to be sorted.
* Output: data -  sorted linked list
**************************************************************************/
template <typename T>
void mergeSort(std::list<T> &l)
{
	typename std::list<T>::iterator iBegin1;
	typename std::list<T>::iterator iBegin2;
	typename std::list<T>::iterator iEnd1;
	typename std::list<T>::iterator iEnd2;

	//creating a destination list which will be used to merge sublists
  //allocate a temp list just once and keep swaping in O(1) between those
	std::list<T> destination(l.size());
  //used to point the first node where we start mergin
	typename std::list<T>::iterator iDestination; 
	int numMerges = 0;

	do
	{
		numMerges = 0;
		iBegin1 = l.begin();
		iDestination = destination.begin();
		while (iBegin1 != l.end())
		{
			//find two sublist and merge them
			numMerges++;
			for (iEnd1 = next(iBegin1, 1); iEnd1 != l.end() && *prev(iEnd1, 1) <=
				*iEnd1; ++iEnd1)
				; //just move forward

			iBegin2 = iEnd1;

			//the case when there is only one elemnet next throws error,that's why I'm checking here
			for (iEnd2 = (iBegin2 != l.end() ? next(iBegin2, 1) : iBegin2);
				iEnd2 != l.end() && *prev(iEnd2, 1) <= *iEnd2;
				++iEnd2)
				; //just move forward

      //merge those and copy back to the positions starting from iDestination
		  //merge them even if only one sorted sublist is left
			merge<T>(iDestination, iBegin1, iEnd1, iBegin2, iEnd2);

			iBegin1 = iEnd2;
		}

		//swap and merge again
		l.swap(destination); //O(1) just swap the pointers

	} while (numMerges > 1);

}