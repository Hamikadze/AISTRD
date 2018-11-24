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

void heapify(int* arr, size_t count, int i)
{
	int largest = i; // Initialize largest as root
	int l = 2 * i + 1; // left = 2*i + 1
	int r = 2 * i + 2; // right = 2*i + 2

	// If left child is larger than root
	if (l < count && arr[l] > arr[largest])
		largest = l;

	// If right child is larger than largest so far
	if (r < count && arr[r] > arr[largest])
		largest = r;

	// If largest is not root
	if (largest != i)
	{
		swap(arr[i], arr[largest]);

		// Recursively heapify the affected sub-tree
		heapify(arr, count, largest);
	}
}

// main function to do heap sort
int* HeapSort(int* arr, size_t count)
{
	// Build heap (rearrange array)
	for (int i = count / 2 - 1; i >= 0; i--)
		heapify(arr, count, i);

	// One by one extract an element from heap
	for (int i = count - 1; i >= 0; i--)
	{
		// Move current root to end
		swap(arr[0], arr[i]);

		// call max heapify on the reduced heap
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

int BinarySearch(int* arr, size_t count, int num)
{
	// Проверить, имеет ли смыл вообще выполнять поиск:
	// - если длина массива равна нулю - искать нечего;
	// - если искомый элемент меньше первого элемента массива, значит, его в массиве нет;
	// - если искомый элемент больше последнего элемента массива, значит, его в массиве нет.
	if ((count == 0) || (num < arr[0]) || (num > arr[count - 1]))
		throw std::out_of_range("Index is greater than list size");

	// Приступить к поиску.
	// Номер первого элемента в массиве.
	int first = 0;
	// Номер элемента массива, СЛЕДУЮЩЕГО за последним
	int last = count;

	// Если просматриваемый участок не пуст, first < last
	while (first < last)
	{
		int mid = first + (last - first) / 2;

		if (num <= arr[mid])
			last = mid;
		else
			first = mid + 1;
	}

	// Теперь last может указывать на искомый элемент массива.
	if (arr[last] == num)
		return last;
	else
		return -1;
}

int Max(char* arr, size_t count)
{
	char max = arr[0];
	for (int i = 0; i < count; i++)
	{
		if (max < *(arr + i))
		{
			max = *(arr + i);
		}
	}
	return  max;
}

int Min(char* arr, size_t count)
{
	char min = arr[0];
	for (int i = 0; i < count; i++)
	{
		if (min > *(arr + i))
		{
			min = *(arr + i);
		}
	}
	return min;
}

char* CountingSort(char* arr, size_t count)
{
	int max = Max(arr, count);
	int min = Min(arr, count);
	int size = max - min + 1;
	char* countsArray = new char[max - min + 1];
	for (int i = min; i <= max; ++i)
		countsArray[i - min] = 0;

	for (int i = 0; i < count; ++i)
		++countsArray[arr[i] - min];

	for (int i = min; i <= max; ++i)
		for (int j = countsArray[i - min]; j--;)
			*arr++ = i;
	return arr;
}

int correct(int *arr, size_t size) {
	for (int i = 0; i < size - 1; i++)
		return !(arr[size] > arr[size + 1]);
	return true;
}

void shuffle(int *arr, size_t size) {
	for (int i = 0; i < size; i++)
		std::swap(arr[i], arr[(rand() % size)]);
}

int* BogoSort(int *arr, size_t size) {
	while (!correct(arr, size))
		shuffle(arr, size);
	return arr;
}

int* InsertionSort(int* arr, size_t size) {
	for (int j = 1; j < size; j++) {
		int i = j - 1;

		const int processedValue = arr[j];

		while ((i >= 0) && (arr[i] > processedValue)) {
			arr[i + 1] = arr[i];

			i--;
		}

		arr[i + 1] = processedValue;
	}

	return arr;
}

int partition(int* arr, int fromIndex, int toIndex) {
	int lastElementValue = arr[toIndex];
	int i = fromIndex - 1;
	for (int j = fromIndex; j < toIndex; j++) {
		if (arr[j] <= lastElementValue) {
			i++;
			std::swap(arr[i], arr[j]);
		}
	}
	std::swap(arr[i + 1], arr[toIndex]);
	return i + 1;
}

int *sortArrayPart(int* arr, int fromIndex, int toIndex)
{
	if (fromIndex < toIndex)
	{
		const int middleIndex = partition(arr, fromIndex, toIndex);
		sortArrayPart(arr, fromIndex, middleIndex - 1);
		sortArrayPart(arr, middleIndex + 1, toIndex);
	}
	return  arr;
}
int* QuickSort(int* arr, /*size_t fromIndex, */size_t size) {
	const auto toIndex = size - 1;
	return sortArrayPart(arr, 0, toIndex);
}

int* CopyArray(int arr[], int count)
{
	const auto new_array = new int[count];
	memcpy(new_array, arr, sizeof(int)*count);
	return new_array;
}

char* CopyArray(char arr[], int count)
{
	const auto new_array = new char[count];
	memcpy(new_array, arr, sizeof(char)*count);
	return new_array;
}

int* BubbleSort(int* arr, size_t size) {
	bool swappedElements;
	do {
		swappedElements = false;

		for (int i = 0; i < size - 1; i++) {
			if (arr[i] > arr[i + 1]) {
				std::swap(arr[i], arr[i + 1]);
				swappedElements = true;
			}
		}
	} while (swappedElements);
	return arr;
}