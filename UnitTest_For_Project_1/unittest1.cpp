#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Project_1/Include.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest_For_Project_1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(is_test_works)
		{
			Assert::IsTrue(true);
		}
		TEST_METHOD(is_equal_2_dif_array_test)
		{
			int array1[5] = { 1, 2, 3, 4, 5 };
			int array2[5] = { 1, 2, 5, 4, 5 };
			Assert::IsFalse(Equals(array1, 5, array2, 5));
		}
		TEST_METHOD(is_equal_2_eq_array_test)
		{
			int array1[5] = { 1, 2, 3, 4, 5 };
			int array2[5] = { 1, 2, 3, 4, 5 };
			Assert::IsTrue(Equals(array1, 5, array2, 5));
		}
		TEST_METHOD(is_min_value_dif_values)
		{
			Assert::IsFalse(Min(1, 10) == 10);
		}
		TEST_METHOD(is_min_value_eq_values)
		{
			Assert::IsTrue(Min(1, 10) == 1);
		}
		TEST_METHOD(is_fill_array_diff_array_test)
		{
			Matrix matrix(3, 3, 3);
			Fill_Array(matrix);
			int array[9] = { 1,1,1,
							1,2,1,
							1,1,1 };
			Assert::IsFalse(Equals(matrix.array, 9, array, 9));
		}
		TEST_METHOD(is_fill_array_eq_array_test)
		{
			Matrix matrix(3, 3, 3);
			Fill_Array(matrix);
			int array[9] = { 3,3,3,
							3,4,3,
							3,3,3 };
			Assert::IsTrue(Equals(matrix.array, 9, array, 9));
		}

		TEST_METHOD(is_initial_array_work)
		{
			Matrix matrix(3, 3, 3);
			Assert::IsTrue(matrix.array != nullptr);
		}

		TEST_METHOD(is_return_valid_index_1)
		{
			Matrix matrix(3, 3, 3);
			Assert::IsTrue(matrix.index(2, 0) == 2);
		}

		TEST_METHOD(is_return_valid_index_2)
		{
			Matrix matrix(3, 3, 3);
			Assert::IsTrue(matrix.index(2, 2) == 8);
		}

		TEST_METHOD(is_max_lenght_num_valid_1)
		{
			Matrix matrix(9, 9, 9);
			Assert::IsTrue(matrix.max_lenght_num == 2);
		}
		TEST_METHOD(is_max_lenght_num_valid_2)
		{
			Matrix matrix(3, 3, 3);
			Assert::IsTrue(matrix.max_lenght_num == 1);
		}
	};
}