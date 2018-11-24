// Project_4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "ArraySort.h"

int main()
{
	int count = 10;
	//std::cin >> count;
	int* array = new int[count];

	array[0] = 66;
	array[1] = 88;
	array[2] = 77;
	array[3] = 22;
	array[4] = 99;
	array[5] = 0;
	array[6] = 11;
	array[7] = 44;
	array[8] = 33;
	array[9] = 55;

	for (int i = 0; i < count; i++)
	{
		std::cout << (int)array[i] << " ";
	}
	std::cout << std::endl;

	int* new_arr = CopyArray(array, count);

	for (int i = 0; i < count; i++)
	{
		std::cout << (int)new_arr[i] << " ";
	}
	std::cout << std::endl;

	HeapSort(new_arr, count);
	/*int x = BinarySearch(new_arr, count, 22);
	std::cout << new_arr[x] << std::endl;*/

	for (int i = 0; i < count; i++)
	{
		std::cout << (int)new_arr[i] << " ";
	}
	std::cout << std::endl;
	system("pause");
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file