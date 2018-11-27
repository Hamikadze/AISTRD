// Course_work.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdio.h>

int main()
{
	std::vector<std::string> original_text;
	std::string line;
	std::ifstream original_file("test.txt");
	std::ifstream commits_file("commits.txt");
	if (original_file)  // same as: if (myfile.good())
	{
		while (getline(original_file, line))  // same as: while (getline( myfile, line ).good())
		{
			original_text.push_back(line);
		}
		original_file.close();
	}
	if (commits_file)  // same as: if (myfile.good())
	{
		while (getline(original_file, line))  // same as: while (getline( myfile, line ).good())
		{
			const std::string str;
			int i;
			std::string delimiter = ">=";
			//std::string token = s.substr(0, s.find(delimiter));
			original_text.push_back(line);
		}
		original_file.close();
	}
	else std::cout << "fooey\n";

	return 0;
}