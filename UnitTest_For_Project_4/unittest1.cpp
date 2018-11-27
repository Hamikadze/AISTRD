#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Project_4/ArraySort.h"
#include "../Project_1/ArrayUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest_For_Project_4
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(is_correct_int_array_test_work)
		{
			int array1[5] = { 1, 2, 3, 4, 5 };
			int array2[5] = { 1, 3, 2, 5, 4 };
			Assert::IsTrue(isCorrect(array1, 5) && !isCorrect(array2, 5));
		}
		TEST_METHOD(is_correct_char_array_test_work)
		{
			char array1[5] = { 1, 2, 3, 4, 5 };
			char array2[5] = { 1, 3, 2, 5, 4 };
			Assert::IsTrue(isCorrect(array1, 5) && !isCorrect(array2, 5));
		}

		TEST_METHOD(is_InsertionSort_works_with_corrent_indexes)
		{
			int array1[5] = { 3, 2, 4, 5, 1 };
			InsertionSort(array1, 5);
			Assert::IsTrue(isCorrect(array1, 5));
		}

		TEST_METHOD(is_QuickSort_works_with_corrent_indexes)
		{
			int array1[5] = { 3, 2, 4, 5, 1 };
			QuickSort(array1, 5);
			Assert::IsTrue(isCorrect(array1, 5));
		}

		TEST_METHOD(is_BubbleSort_works_with_corrent_indexes)
		{
			int array1[5] = { 3, 2, 4, 5, 1 };
			BubbleSort(array1, 5);
			Assert::IsTrue(isCorrect(array1, 5));
		}

		TEST_METHOD(is_BogoSort_works_with_corrent_indexes)
		{
			int array1[5] = { 3, 2, 4, 5, 1 };
			BogoSort(array1, 5);
			Assert::IsTrue(isCorrect(array1, 5));
		}

		TEST_METHOD(is_CountingSort_works_with_corrent_indexes)
		{
			char array1[5] = { 3, 2, 4, 5, 1 };
			CountingSort(array1, 5);
			Assert::IsTrue(isCorrect(array1, 5));
		}
		TEST_METHOD(is_TreeSort_works_with_corrent_indexes)
		{
			int array1[5] = { 3, 2, 4, 5, 1 };
			TreeSort(array1, 5);
			Assert::IsTrue(isCorrect(array1, 5));
		}
		TEST_METHOD(is_HeapSort_works_with_corrent_indexes)
		{
			int array1[5] = { 3, 2, 4, 5, 1 };
			HeapSort(array1, 5);
			Assert::IsTrue(isCorrect(array1, 5));
		}
		TEST_METHOD(is_BinarySearch_works_with_corrent_values)
		{
			int array1[5] = { 1,2,3,4, 10 };
			Assert::IsTrue(
				BinarySearch(array1, 5, 1) == 0 &&
				BinarySearch(array1, 5, 2) == 1 &&
				BinarySearch(array1, 5, 3) == 2 &&
				BinarySearch(array1, 5, 4) == 3 &&
				BinarySearch(array1, 5, 10) == 4 &&
				BinarySearch(array1, 5, 5) == -1);
		}
		TEST_METHOD(is_BinarySearch_works_with_incorrent_values_1)
		{
			int array1[5] = { 1,2,3,4, 10 };
			Assert::IsTrue(BinarySearch(array1, 5, -1) == -1);
		}
		TEST_METHOD(is_BinarySearch_works_with_incorrent_values_2)
		{
			int array1[5] = { 1,2,3,4, 10 };
			Assert::IsTrue(BinarySearch(array1, 5, 100) == -1);
		}

		TEST_METHOD(is_copy_array_int_works)
		{
			int array1[5] = { 1, 2, 3, 4, 5 };
			int* array2 = CopyArray(array1, 5);
			Assert::IsTrue(array2 != nullptr&& Equals(array1, 5, array2, 5));
		}

		TEST_METHOD(is_move_array_char_works)
		{
			int array1[5] = { 1, 2, 3, 4, 5 };
			char* array2 = MoveArray(array1, 5);
			Assert::IsTrue(array2 != nullptr &&
				array1[0] == array2[0] &&
				array1[1] == array2[1] &&
				array1[2] == array2[2] &&
				array1[3] == array2[3] &&
				array1[4] == array2[4]
			);
		}
	};
}