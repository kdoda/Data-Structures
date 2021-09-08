/***********************************************************************
* Program:
*    Week 11, Sorting
*    Brother Ercanbrack, CS 235
*
* Author:
*   Klevin Doda
* Summary: 
*   Created a Heap class that implements HeapSort
************************************************************************/
#include <vector>
#include <cassert>
#include <fstream>

/*********************************************
 * HEAP
 * Heap class that can Sorts an array
 *********************************************/
template <class T>
class Heap
{
public:
	Heap(std::vector<T> &vInput);
	void sort();

private:
	int n;
	std::vector<T> &v;
	void percolateDown(int index);
};

/*********************************************
* NON DEFAULT CONSTRUCTOR
* Heapify the vector
*********************************************/
template <class T>
Heap<T> ::Heap(std::vector<T> &vInput) : v(vInput)
{
	//CAREFUL the only way it works, by initialising it this way!
	n = v.size();
	for (int i = n / 2 - 1; i >= 0; --i)
		percolateDown(i);
}

/***************************************************************
* PERCOLATE DOWN
* Puts the element of the vector(pos index) where it belongs 
* in the heap (both children <= than the element)
****************************************************************/
template <class T>
void Heap<T>::percolateDown(int index)
{
	int indexLeft = 2 * index + 1;
	int indexRight = 2 * index + 2;

	if (indexRight < n
		&& v[indexRight] > v[indexLeft]
		&& v[indexRight] > v[index])
	{
		std::swap(v[index], v[indexRight]);
		percolateDown(indexRight);
	}
	else if (indexLeft < n && v[indexLeft] > v[index])
	{
		std::swap(v[index], v[indexLeft]);
		percolateDown(indexLeft);
	}
}

/*********************************************
* SORT
* Sort the vector using Heap Sort
*********************************************/
template <class T>
void  Heap<T>::sort()
{
	//n is not the index of the last element
	assert(n > 0);
	while (n > 1)
	{
		std::swap(v[0], v[n - 1]);
		--n;
		percolateDown(0);
	}
}

/*********************************************
* READ FILE
* Read the file into the vector
*********************************************/
void readFile(std::vector<int> &v, char fileName[]) throw (const char *)
{
	std::ifstream fin(fileName);
	if (fin.fail())
		throw "ERROR: File could not be opened!";

	int number;
	while (fin >> number)
		v.push_back(number);

	fin.close();
}

/*********************************************
* PRINT
* Print the vector in the screen according to 
* the instructions
*********************************************/
void print(const std::vector<int> &v)
{
	for (int i = 1;i <= v.size(); ++i)
	{
		std::cout << std::setw(3) << v[i - 1];
		if (i % 10 == 0)
			std::cout << std::endl;
	}
}

/*************************************************************************
* This function sorts a vector using a heap sort.
* Input:  data -  Vector to be sorted.
* Output: data -  Vector sorted
**************************************************************************/
template<class T>
void heapSort(std::vector<T> &data)
{
	Heap<T> heap(data);
	heap.sort();
}
