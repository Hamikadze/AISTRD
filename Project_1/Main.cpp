// Project_1.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "Include.h"

int main()
{
	int width, height, initial_value;
	cin >> width >> height >> initial_value;
	const Matrix matrix(width, height, initial_value);
	Fill_Array(matrix);
	Print_Array(matrix);
	system("pause");
	return 0;
}