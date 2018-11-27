#include "pch.h"
#include "ArraySort.h"
#include <xutility>
#include <algorithm>
#include <stdexcept>
#include "../Project_3/AvlTree.h"
#include "../Project_3/AvlTree.cpp"

ArraySort::ArraySort()
{
}

ArraySort::~ArraySort()
{
}

//Двоичный поиск(BinarySearch)+
//Быстрая сортировка(QuickSort)+
//Сортировка вставками(InsertionSort)+
//Сортировка пузырьком(BubbleSort)+
//Сортировка с помощью двоичного дерева(TreeSort)+
//Пирамидальная сортировка(HeapSort)+
//Глупая сортировка(BogoSort)+
//Сортировка подсчётом(CountingSort) для типа char+

void Swap(int& first, int& second)
{
	const int temp = first;
	first = second;
	second = temp;
}

void heapify(int* arr, size_t count, int i)
{
	int largest = i;
	const int left = 2 * i + 1;
	const int right = 2 * i + 2;

	if (left < count && arr[left] > arr[largest])
		largest = left;

	if (right < count && arr[right] > arr[largest])
		largest = right;

	if (largest != i)
	{
		Swap(arr[i], arr[largest]);
		heapify(arr, count, largest);
	}
}

int* HeapSort(int* arr, size_t size)
{
	for (int i = size / 2 - 1; i >= 0; i--)
		heapify(arr, size, i);

	for (int i = size - 1; i >= 0; i--)
	{
		Swap(arr[0], arr[i]);

		heapify(arr, i, 0);
	}
	return arr;
}

int* TreeSort(int* arr, size_t count)
{
	auto avl = new AvlTree();
	for (int i = 0; i < count; i++)
		avl->Insert(arr[i]);
	Iterator* sortedOutput = avl->create_sft_iterator();
	int i = 0;
	while (sortedOutput->has_next())
		arr[i++] = sortedOutput->next();
	return arr;
}

int BinarySearch(const int* arr, size_t size, int num)
{
	if ((num >= arr[0]) && (num <= arr[size - 1]))
	{
		int first = 0;
		int last = size;
		while (first < last)
		{
			const int middle = first + (last - first) / 2;

			if (num <= arr[middle])
				last = middle;
			else
				first = middle + 1;
		}

		if (arr[last] == num)
			return last;
	}
	return -1;
}

int Max(const char* arr, size_t count)
{
	char maxValue = arr[0];
	for (int i = 0; i < count; i++)
	{
		if (maxValue < *(arr + i))
		{
			maxValue = *(arr + i);
		}
	}
	return maxValue;
}

int Min(const char* arr, size_t count)
{
	char minValue = arr[0];
	for (int i = 0; i < count; i++)
	{
		if (minValue > *(arr + i))
		{
			minValue = *(arr + i);
		}
	}
	return minValue;
}

char* CountingSort(char* arr, size_t size)
{
	const int maxValue = Max(arr, size);
	const int minValue = Min(arr, size);
	const auto countsArray = new int[maxValue - minValue + 1];
	for (int i = 0; i < maxValue - minValue + 1; i++)
		countsArray[i] = 0;

	for (int i = 0; i < size; ++i)
		countsArray[arr[i] - minValue]++;

	int k = 0;
	for (int i = 0; i < maxValue - minValue + 1; i++)
		for (int j = 0; j < countsArray[i]; j++) {
			arr[k] = i;
			k++;
		}
	return arr;
}

bool isCorrect(const int* arr, size_t size)
{
	for (int i = 0; i < size - 1; i++)
		if (arr[i] > arr[i + 1])
			return false;
	return true;
}

bool isCorrect(const char* arr, size_t size)
{
	for (int i = 0; i < size - 1; i++)
		if (arr[i] > arr[i + 1])
			return false;
	return true;
}

void shuffle(int* arr, size_t size)
{
	for (int i = 0; i < size; i++)
		Swap(arr[i], arr[(rand() % size)]);
}

int* BogoSort(int* arr, size_t size)
{
	while (!isCorrect(arr, size))
		shuffle(arr, size);
	return arr;
}

int* InsertionSort(int* arr, size_t size)
{
	for (int j = 1; j < size; j++)
	{
		const int processedValue = arr[j];
		int i = j - 1;
		for (; (i >= 0) && (arr[i] > processedValue); i--)
			arr[i + 1] = arr[i];
		arr[i + 1] = processedValue;
	}

	return arr;
}

int partition(int *arr, int fromIndex, int toIndex)
{
	const int last = arr[toIndex];
	int i = fromIndex - 1;
	for (int j = fromIndex; j < toIndex; j++)
	{
		if (arr[j] <= last)
		{
			i++;
			Swap(arr[i], arr[j]);
		}
	}
	Swap(arr[toIndex], arr[i + 1]);
	return i + 1;
}

int* sortArrayPart(int* arr, int fromIndex, int toIndex)
{
	if (fromIndex < toIndex)
	{
		const int middleIndex = partition(arr, fromIndex, toIndex);
		sortArrayPart(arr, fromIndex, middleIndex - 1);
		sortArrayPart(arr, middleIndex + 1, toIndex);
	}
	return arr;
}

int* QuickSort(int* arr, /*size_t fromIndex, */size_t size)
{
	const auto toIndex = size - 1;
	return sortArrayPart(arr, 0, toIndex);
}

int* CopyArray(int arr[], int count)
{
	const auto new_array = new int[count];
	memcpy(new_array, arr, sizeof(int) * count);
	return new_array;
}

char* MoveArray(const int arr[], int count)
{
	const auto new_array = new char[count];
	for (int i = 0; i < count; i++)
	{
		new_array[i] = arr[i];
	}
	return new_array;
}

int* BubbleSort(int* arr, size_t size)
{
	bool swappedElements;
	do
	{
		swappedElements = false;

		for (int i = 0; i < size - 1; i++)
		{
			if (arr[i] > arr[i + 1])
			{
				Swap(arr[i], arr[i + 1]);
				swappedElements = true;
			}
		}
	} while (swappedElements);
	return arr;
}

int* RandomFill(int* arr, size_t size, int min_value, int max_value)
{
	for (int i = 0; i < size; ++i)
	{
		arr[i] = rand() % max_value + min_value;
	}
	return arr;
}