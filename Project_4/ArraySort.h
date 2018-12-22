//#include "../Project_3/AvlTree.h"
#pragma once
class ArraySort
{
};
int* InsertionSort(int* arr, size_t size);
int* QuickSort(int* arr, size_t size);
int* BubbleSort(int* arr, size_t size);
int* BogoSort(int *arr, size_t size);
char* CountingSort(char* arr, size_t count);
int BinarySearch(const int* arr, size_t count, int num);
int* TreeSort(int* arr, size_t count);
int* HeapSort(int* arr, size_t count);

bool isCorrect(const int *arr, size_t size);
bool isCorrect(const char *arr, size_t size);
int* RandomFill(int* arr, size_t size, int max_value, int min_value);

int* CopyArray(int arr[], size_t count);
char* MoveArray(const int arr[], size_t count);
