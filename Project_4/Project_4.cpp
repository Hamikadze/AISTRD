// Project_4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "ArraySort.h"
#include "Stopwatch.h"

int main()
{
	const int count = 1000;
	int* array = new int[count];
	RandomFill(array, count, 0, 100);

	Stopwatch<> sw;
	std::cout.precision(20);
	std::cout << std::fixed;
	int iterations = 1000;

	{
		float time = 0;
		for (int i = 0; i < iterations; i++)
		{
			int* new_arr = CopyArray(array, count);
			sw.reset();
			TreeSort(new_arr, count);
			time += duration_cast<float>(sw.elapsed());
			if (!isCorrect(new_arr, 10))
			{
				std::cout << "TreeSort error" << std::endl;
				break;
			};
		}
		std::cout << "TreeSort : " << time / iterations << std::endl;
	}

	{
		float time = 0;
		for (int i = 0; i < iterations; i++)
		{
			char* new_arr = MoveArray(array, count);
			sw.reset();
			CountingSort(new_arr, count);
			time += duration_cast<float>(sw.elapsed());
			if (!isCorrect(new_arr, 10))
			{
				std::cout << "CountingSort error" << std::endl;
				break;
			};
		}
		std::cout << "CountingSort : " << time / iterations << std::endl;
	}

	{
		float time = 0;
		for (int i = 0; i < iterations; i++)
		{
			int* new_arr = CopyArray(array, count);
			sw.reset();
			QuickSort(new_arr, count);
			time += duration_cast<float>(sw.elapsed());
			if (!isCorrect(new_arr, 10))
			{
				std::cout << "QuickSort error" << std::endl;
				break;
			};
		}
		std::cout << "QuickSort : " << time / iterations << std::endl;
	}

	{
		float time = 0;
		for (int i = 0; i < iterations; i++)
		{
			int* new_arr = CopyArray(array, count);
			sw.reset();
			InsertionSort(new_arr, count);
			time += duration_cast<float>(sw.elapsed());
			if (!isCorrect(new_arr, 10))
			{
				std::cout << "InsertionSort error" << std::endl;
				break;
			};
		}
		std::cout << "InsertionSort : " << time / iterations << std::endl;
	}

	{
		float time = 0;
		for (int i = 0; i < iterations; i++)
		{
			int* new_arr = CopyArray(array, count);
			sw.reset();
			HeapSort(new_arr, count);
			time += duration_cast<float>(sw.elapsed());
			if (!isCorrect(new_arr, 10))
			{
				std::cout << "HeapSort error" << std::endl;
				break;
			};
		}
		std::cout << "HeapSort : " << time / iterations << std::endl;
	}

	{
		float time = 0;
		for (int i = 0; i < iterations; i++)
		{
			int* new_arr = CopyArray(array, count);
			sw.reset();
			TreeSort(new_arr, count);
			time += duration_cast<float>(sw.elapsed());
			if (!isCorrect(new_arr, 10))
			{
				std::cout << "TreeSort error" << std::endl;
				break;
			};
		}
		std::cout << "TreeSort : " << time / iterations << std::endl;
	}

	{
		float time = 0;
		for (int i = 0; i < iterations; i++)
		{
			int* new_arr = CopyArray(array, count);
			sw.reset();
			BubbleSort(new_arr, count);
			time += duration_cast<float>(sw.elapsed());
			if (!isCorrect(new_arr, 10))
			{
				std::cout << "BubbleSort error" << std::endl;
				break;
			};
		}
		std::cout << "BubbleSort : " << time / iterations << std::endl;
	}
	{
		float time = 0;
		/*for (int i = 0; i < iterations; i++)
		*/ {
			int* new_arr = new int[10];
			RandomFill(new_arr, 10, 0, 10);
			sw.reset();
			BogoSort(new_arr, 10);
			time += duration_cast<float>(sw.elapsed());
			if (!isCorrect(new_arr, 10))
			{
				std::cout << "BogoSort error" << std::endl;
				//break;
			};
			//}
			std::cout << "BogoSort : " << time /*/ iterations*/ << std::endl;
		}
	}

	{
		float time = 0;
		for (int i = 0; i < iterations; i++)
		{
			int* new_arr = CopyArray(array, count);
			sw.reset();
			BubbleSort(new_arr, count);
			time += duration_cast<float>(sw.elapsed());
			if (!isCorrect(new_arr, 10))
			{
				std::cout << "BubbleSort error" << std::endl;
				break;
			};
		}
		std::cout << "BubbleSort : " << time / iterations << std::endl;
	}

	{
		float time = 0;
		for (int i = 0; i < iterations; i++)
		{
			int* new_arr = CopyArray(array, count);
			QuickSort(new_arr, count);
			sw.reset();
			BinarySearch(new_arr, count, 10);
			time += duration_cast<float>(sw.elapsed());
			if (!isCorrect(new_arr, 10))
			{
				std::cout << "BinarySearch error" << std::endl;
				break;
			};
		}
		std::cout << "BinarySearch : " << time / iterations << std::endl;
	}
	/*int x = BinarySearch(new_arr, count, 22);
	std::cout << new_arr[x] << std::endl;*/

	/*for (int i = 0; i < count; i++)
	{
		std::cout << (int)new_arr[i] << " ";
	}
	std::cout << std::endl;*/
	system("pause");
}