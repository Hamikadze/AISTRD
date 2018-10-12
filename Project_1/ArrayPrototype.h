#pragma once
#include <string>

struct Matrix
{
	Matrix(const size_t width, const size_t height, const int initial_value);
	int width, height, initial_value;
	int* array = nullptr;
	int max_lenght_num{};
	size_t index(int x, int  y) const;
	~Matrix();
};
