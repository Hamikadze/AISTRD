#include "stdafx.h"
#include "Include.h"

Matrix::Matrix(const size_t width, const size_t height, const int initial_value)
{
	this->width = width;
	this->height = height;
	this->initial_value = initial_value;
	array = new int[width * height];
	const int longest_line = width > height ? width : height;
	max_lenght_num = std::to_string(initial_value + (longest_line / 2)).length();
}

size_t Matrix::index(int x, int y) const
{
	return x + width * y;
}

Matrix::~Matrix()
{
	delete[] array;
	array = nullptr;
}