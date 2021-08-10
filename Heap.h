#ifndef Heap
#include<iostream>
#include<exception>
#include<math.h>
#include<iomanip>
#include<unistd.h>
using namespace std;

//Heap Class
template <typename T>
class Heap
{
	private:
		T *array;			//Initialize Array
		int capacity;		//Capacity
		int size;			//Size
	
	public:
		Heap(int capacity);		//Constructor
		~Heap();				//Destructor
		void insert(T key);		//Insert Method
		T removeMax();			//Remove Max
		T getMax();				//Return Max element
		int parent(int k);		//Return the index of parent node
		int left(int k);		//Return the index of left child node
		int right(int k);		//Return the index of right child node
		void siftup(int k);		//Siftup an element at index k
		void siftdown(int k);	//Siftdown an element at index k
		void sort();			//Sort the array
	private:
		void adjustSize();		//Adjust the size of the array if capacity is full
};
//==============================================================================================
// Constructor
template <typename T>
Heap<T>::Heap(int cap)
{
	size = 0;
	capacity = cap;
	array = new T[capacity];
}
//==============================================================================================
//Destructor
template <typename T>
Heap<T>::~Heap()
{
	delete[] array;
}
//==============================================================================================
// Insert an element in Heap keeping the Heap property intact 
template <typename T>
void Heap<T>::insert(T key)
{
	//todo
	if (size == capacity)
    {
        adjustSize();
    }
    array[size] = key;
    size++;
    siftup(size-1);
}
//==============================================================================================
// Remove the maximum value from Heap keeping the Heap property intact
template <typename T>
T Heap<T>::removeMax()
{
	//todo
	if (size <= 0)
        throw runtime_error("Heap is empty");
    if (size == 1)
    {
        size--;
        return array[0];
    }
  
    T val = array[0];
    array[0] = array[size-1];
    size--;
    siftdown(0);
    return val;
}
//==============================================================================================
// Return the maximum value from the Heap
template <typename T>
T Heap<T>::getMax()
{
	if(size>0)
		return array[0];
	throw runtime_error("Heap<T> is empty");
}
//==============================================================================================
// Returns the index of the parent of the node i
template <typename T>
int Heap<T>::parent(int k)
{
	return ((k - 1) / 2);
}
//==============================================================================================
// Returns the index of the left child of the node i
template <typename T>
int Heap<T>::left(int k)
{
	//todo
	return (2*k + 1);
}
//==============================================================================================
// Returns the index of the right child of the node i
template <typename T>
int Heap<T>::right(int k)
{
	//todo
	return (2*k + 2);
}
//==============================================================================================
// Sift-up an element at index k
template <typename T>
void Heap<T>::siftup(int k)
{
	 if (k && array[parent(k)].value < array[k].value)
        {
            swap(array[k], array[parent(k)]);
            siftup(parent(k));
        }
}
//==============================================================================================
// Sift-down an element at index k
// 1. if element has no children do nothing
// 2. if element has only a left child which is greater than element then swap the element with its left child
// 3. if element has both children and greater child is also greater than the node then swap it with that node
// 4. keep repeating step 1-3 until the element/node reaches to its correct position
template <typename T>
void Heap<T>::siftdown(int k)
{
	//todo	
        int l = left(k);
        int r = right(k);
 
        int highest = k;
 
        if (l < size && array[l].value > array[k].value) {
            highest = l;
        }
 
        if (r < size && array[r].value > array[highest].value) {
            highest = r;
        }
 
        if (highest != k)
        {
            swap(array[k], array[highest]);
            siftdown(highest);
        }

}
//==============================================================================================
// This method will sort the internal array of heap using an Auxilary heap
template <typename T>
void Heap<T>::sort()
{
	//todo
	if(size==0){
		throw runtime_error("Heap is Empty");
	}

	Heap<T> newHeap(capacity);
	for (int i = 0; i < size; i++)
	{	
		newHeap.insert(array[i]);
	}

	for (int i = 0; i<size; i++){
		array[i] = newHeap.removeMax();
	}
}
//==============================================================================================

//Adjust Size according to capacity
template <typename T>
void Heap<T>::adjustSize()
{
	T *newArray = new T[capacity*2];
	for(int i=0; i<capacity; i++)
		newArray[i] = array[i];
	delete[] array;
	array = newArray;
	capacity = capacity*2;	
}
#endif