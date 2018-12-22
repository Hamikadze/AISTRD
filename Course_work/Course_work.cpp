// Course_work.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <iomanip>
#include "CommitsUtils.h"

LinkedList<std::string> temp_text;//temp text without new but with last changes
LinkedList<std::string> changed_text;//file with changes
LinkedList<std::string> original_text;//file original

void Process_Selection_Save_Changes(CommitsUtils* commits)
{
	commits->Analyze_Changes(changed_text, temp_text);
};

void Process_Selection_View_History(CommitsUtils* commitsm)
{
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::string line;

	std::ifstream changed_file_in("changed.txt", std::ios::in);
	if (changed_file_in)
	{
		int index = 0;
		std::cout << "changed.txt loaded!\n";
		while (getline(changed_file_in, line))  // same as: while (getline( myfile, line ).good())
		{
			changed_text.push_back(line);
			index++;
		}
		changed_file_in.close();
	}
	changed_file_in.close();

	std::ifstream original_file_in("original.txt", std::ios::in);
	if (original_file_in)
	{
		int index = 0;
		std::cout << "original.txt loaded!\n";
		while (getline(original_file_in, line))  // same as: while (getline( myfile, line ).good())
		{
			original_text.push_back(line);
			index++;
		}
		original_file_in.close();
	}
	original_file_in.close();

	CommitsUtils* commits;
	commits = new CommitsUtils("commits.txt");
	//==================================
	Item<CommitsUtils*> functions[] =
	{
		Item<CommitsUtils*>("View history", Process_Selection_View_History, commits),
		Item<CommitsUtils*>("Save changes", Process_Selection_Save_Changes, commits),
	};
	Menu<CommitsUtils*> menu("Main menu");
	menu.Show(functions);
	return 0;
}