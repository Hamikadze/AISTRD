#include "pch.h"
#include "Menu.h"
#include <iterator>

template <typename T>
Menu<T>::Menu(std::string header)
{
	this->header = header;
}

template <typename T>
void Menu<T>::Show(Item<T> item[])
{
	std::cout << "==========================================\n"
		"            " + header + "\n"
		"==========================================\n";
	auto size = std::size(item);
	do
	{
		for (int i = 0; i < size; i++)
		{
			std::cout << "[" << i << "]" << item[i].label << std::endl;
		}
		std::cout << "[" << size << "] EXIT/RETURN" << std::endl;
		std::cout << "Select an item : ";
		int select;
		std::cin >> select;
		if (select == size)
		{
			break;
		}
		for (int i = 0; i < size; i++)
		{
			if (select == i)
			{
				item[i].function(item[i].parameter);
			}
		}
	} while (true);
}

template <typename T>
Menu<T>::~Menu()
{
}