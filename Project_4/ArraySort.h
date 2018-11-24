//#include "../Project_3/AvlTree.h"
#pragma once
class ArraySort
{
public:
	ArraySort();
	~ArraySort();
};
int* InsertionSort(int* arr, size_t size);
int* QuickSort(int* arr, /*size_t fromIndex, */size_t size);
int* BubbleSort(int* arr, size_t size);
int* BogoSort(int *arr, size_t size);
int* CopyArray(int arr[], int count);
char* CopyArray(char arr[], int count);
char* CountingSort(char* arr, size_t count);
int BinarySearch(int* arr, size_t count, int num);
int* TreeSort(int* arr, size_t count);
int* HeapSort(int* arr, size_t count);
