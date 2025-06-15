#pragma once
#include <iostream>
#include <cstdlib>
using namespace std;

template <typename T>
void randArray(T arr[], int size, int a = 1, int b = 10){
	for (int i = 0; i < size; i++)	{
		arr[i] = rand() % (b - a + 1) + a;
	}
}

template <typename T>
void printArray(T arr[], int size, int w_cout = 5){
	for (int i = 0; i < size; i++)	{
		cout.width(w_cout);
		cout << arr[i];
	}
	cout << endl;
}

template <typename T>
void addItemBack(T*& arr, int& size, T value) {
	T* tmp = new T[size + 1];

	for (int i = 0; i < size; i++) {
		tmp[i] = arr[i];
	}

	size++;

	tmp[size - 1] = value;

	delete[] arr;

	arr = tmp;

}

template <typename T>
void addItemFront(T*& arr, int& size, T value) {
	T* tmp = new T[size + 1];

	tmp[0] = value;

	for (int i = 0; i < size; i++) {
		tmp[i + 1] = arr[i];
	}

	size++;

	delete[] arr;

	arr = tmp;
}

template <typename T>
void delItem(T*& arr, int& size, int index) {
	if (index < 0 || index >= size) {
		cerr << "Помилка: некоректний індекс!" << endl;
		return;
	}

	T* tmp = new T[size - 1];

	for (int i = 0, j = 0; i < size; i++) {
		if (i != index) {
			tmp[j++] = arr[i];
		}
	}

	delete[] arr;

	arr = tmp;

	size--;
}

template <typename T>
int myCount_if(T* array, int size, bool(*pFunk)(T)) {
	int count = 0; 

	for (int i = 0; i < size; i++) {
		if (pFunk(array[i]) == true) {
			count++;
		}
	}
	return count;
}

template<typename T>
int myCountIf(T* array, int size, bool (*predicate)(T)) {
	int count = 0;
	for (int i = 0; i < size; ++i) {
		if (predicate(array[i])) {
			count++;
		}
	}
	return count;
}


template <typename T, typename Predicate>
T mySum_if(T* array, int size, Predicate pred) {
    T sum = 0;
    for (int i = 0; i < size; ++i) {
        if (pred(array[i])) {
            sum += array[i];
        }
    }
    return sum;
}

inline int myFindIf(int* arr, int size, bool (*fP)(int)) {
	for (int i = 0; i < size; ++i) {
		if (fP(arr[i])) {
			return i;
		}
	}
	return -1;
}


template <typename T>
void myRemove_if(T*& arr, int& size, bool(*fP)(T)) {
	for (int i = 0; i < size; ++i) {
		if (fP(arr[i])) {
			delItem(arr, size, i--);
		}
	}
}

template <typename T>
int findMaxMin(T* array, int size, bool (*compare)(T, T)) {
    if (size <= 0) return -1;
    int maxIndex = 0;
    for (int i = 1; i < size; ++i) {
        if (compare(array[i], array[maxIndex])) {
            maxIndex = i;
        }
    }
    return maxIndex;
}

template <typename T>
void mySort(T* arr, int size, bool (*cmp)(T, T)) {
	for (int i = 0; i < size - 1; ++i) {
		for (int j = 0; j < size - i - 1; ++j) {
			if (cmp(arr[j], arr[j + 1])) {
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}

inline int findLast_if(int* arr, int size, bool (*fP)(int)) {
	for (int i = size - 1; i >= 0; --i) {
		if (fP(arr[i])) return i;
	}
	return -1; 
}


