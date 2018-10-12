#include "stdafx.h"
#include "Include.h"

bool Equals(const int *  array1, size_t array1_size, const int *  array2, size_t array2_size) {
	if (array1_size != array2_size) return false;
	for (size_t i = 0; i < array1_size; i++) {
		if (array1[i] != array2[i])
			return false;
	}
	return true;
}

int Min(size_t a, size_t b) {
	return a < b ? a : b;
}

void Fill_Array(const Matrix& matrix)
{
	for (size_t i = 0; i < matrix.width; i++)
	{
		const int w_min = Min(i, matrix.width - i - 1);
		for (size_t j = 0; j < matrix.height; j++)
		{
			matrix.array[matrix.index(i, j)] = matrix.initial_value + Min(w_min, Min(j, matrix.height - j - 1));
		}
	}
}

void Print_Array(Matrix matrix)
{
	for (int i = 0; i < matrix.width; i++)
	{
		for (int j = 0; j < matrix.height; j++)
		{
			cout << setw(matrix.max_lenght_num) << matrix.array[matrix.index(i, j)] << " ";
		}
		cout << endl;
	}
}