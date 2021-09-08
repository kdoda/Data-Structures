/***********************************************************************
* Program:
*    Week 11, Sorting
*    Brother Ercanbrack, CS 235
*
* Author:
*   Klevin Doda
* Summary: 
*
************************************************************************/
#include <vector>
#include <fstream>

using namespace std;

/*********************************************
 * HEAP
 * Heap class that can Sorts an array
 *********************************************/
template <class T>
class Heap
{
public:
	Heap(vector<T> &vInput);
	void sort();

private:
	int n;
	vector<T> &v;
	void percolateDown(int index);
};

/*********************************************
* NON DEFAULT CONSTRUCTOR
* Heapify the vector
*********************************************/
template <class T>
Heap<T> ::Heap(vector<T> &rhsV) : v(rhsV)
{
	n = v.size();
	for (int i = n / 2 - 1; i >= 0; --i)
		percolateDown(i);
}

/*********************************************
* SORT
* Sort the vector using Heap Sort
*********************************************/
template <class T>
void  Heap<T>::sort()
{
	while (n > 1)
	{
		std::swap(v[0], v[n - 1]);
		--n;
		percolateDown(0);
	}
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

	if (indexRight < n && v[indexRight] > v[index] && v[indexRight] > v[indexLeft])
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
* READ FILE
* Read the file into the vector
*********************************************/
void readFile(vector<int> &v, char fileName[]) throw (const char *)
{
	ifstream fin(fileName);
	if (fin.fail())
		throw "ERROR: File not found!";

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
void print(const vector<int> &v)
{
	for (int i = 1;i <= v.size(); ++i)
	{
		cout << setw(3) << v[i - 1];
		if (i % 10 == 0)
			cout << endl;
	}
}

/*************************************************************************
* This function sorts a vector using a heap sort.
* Input:  data -  Vector to be sorted.
* Output: data -  Vector sorted
**************************************************************************/
template<class T>
void heapSort(vector<T> &data)
{
	Heap<int> heap(data);
	heap.sort();
}
