#include<iostream>
#include<cstdlib>
#include<iomanip>
#include<stdexcept>
#include<sstream>
#include<exception>
#include<stdexcept>
#include "myvector.h"
#include "contact.h"

using namespace std;

template <typename T>
MyVector<T>::MyVector()
{
	v_size = 0;
	v_capacity = 0;
	data = new T[v_capacity];
};

template <typename T>
MyVector<T>::MyVector(int cap): v_size(0), v_capacity(cap)
{
	data = new T[v_capacity];
};

template <typename T>
MyVector<T>::MyVector(const MyVector& other): v_size(other.v_size), v_capacity(other.v_capacity), data(nullptr)
{
	data = new T[v_capacity];
	for (int i = 0; i < v_size; ++i)
	{
		data[i] = other.data[i];
	}
};

template <typename T>
MyVector<T>::~MyVector() 
{
	delete [] data;
};

template <typename T>
void MyVector<T>::reserve(int N) 
{
	if (v_capacity >= N) return;
	T* B = new T[N]; // resize the array
	for (int j = 0; j < v_size; j++) // copy contents to new array
	{
		B[j] = data[j];
	}
	if (data != NULL) delete [ ] data; // discard old array
	data = B; // make B the new array
	v_capacity = N; // set new capacity
};

template <typename T>
void MyVector<T>::push_back(T element)
{

	if (v_size == v_capacity)
	{
		reserve(max(1,2*v_capacity));
	}
	data[v_size++] = element;

};

template <typename T>
void MyVector<T>::insert(int index, T element)
{

	if (index > size() - 1)
	{
		throw std::out_of_range("The Index is Out Of Range!");
	}

	if (v_size >= v_capacity) // overflow?
	 {
	 reserve( max(1, 2 * v_capacity) ); // double the size
	 }
	for (int j = (v_size - 1); j >= index; j--) // shift elements up A[j+1] = A[j];
		{
			data[j+1] = data[j];
		}
	data[index] = element; // put “e” at index “i”
	v_size++;
};

template <typename T>
void MyVector<T>::erase(int index)
{
	if (index > size())
	{
		throw std::out_of_range("The Index is Out Of Range!");
	}

	for (int j = index; j <= v_size; j++) //
	{
		data[j] = data[j+1];
	}

	v_size--;
};

template <typename T>
T& MyVector<T>::operator[](int index)
{
	return data[index];
};

template <typename T>
T& MyVector<T>::at(int index)
{
	if (index > size())
	{
		throw std::out_of_range("The Index is Out Of Range!");
	}
	else
	{
		return data[index];
	}
};

template <typename T>
const T& MyVector<T>::front()
{
	return data[0];
};

template <typename T>
const T& MyVector<T>::back()
{
	return data[v_size-1];
};

template <typename T>
int MyVector<T>::size() const
{
	return v_size;
};

template <typename T>
int MyVector<T>::capacity() const
{
	return v_capacity;
};

template <typename T>
void MyVector<T>::shrink_to_fit()
{
	v_capacity = v_size;
};

template <typename T>
bool MyVector<T>::empty() const
{
	return (v_size==0);
};

template class MyVector<Contact>;