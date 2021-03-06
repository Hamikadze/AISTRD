// Course_work.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <windows.h>
#include <iomanip>
#include "CommitsUtils.h"

int main()
{
	CommitsUtils* commits = new CommitsUtils("changed.txt");

	LinkedList<std::string> main_menu;
	main_menu.push_back("View history");
	main_menu.push_back("Save changes");
	Menu menu("Main menu");
	do {
		switch (menu.Show(main_menu))
		{
		case 0:
			commits->show_commit_menu();
			break;
		case 1:
		{
			if (commits->analyze_changes())
				std::cout << "Сhanges were recorded!\n";
		}
		break;
		case 2:
			return 0;
		default:
			break;
		}
	} while (true);
}