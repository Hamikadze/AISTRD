#pragma once
#include <string>
#include "CommitsUtils.h"

class Menu
{
	const char* header;
public:
	Menu(const char* header)
	{
		this->header = header;
	}
	int Show(LinkedList<std::string> list)
	{
		std::cout << "==========================================\n"
			"            " << header << "\n"
			"==========================================\n";
		size_t size = list.get_size();
		do
		{
			auto* print_iterator = list.create_list_iterator();
			int count = 0;
			while (print_iterator->has_next())
			{
				std::cout << "[" << count++ << "] " << print_iterator->next() << std::endl;
			}
			std::cout << "[" << size << "] EXIT/RETURN" << std::endl;
			std::cout << "Select an item : ";
			int select;
			std::cin >> select;
			if (select == size)
			{
				return select;
			}
			auto* select_iterator = list.create_list_iterator();
			count = 0;
			while (select_iterator->has_next())
			{
				auto item = select_iterator->next();
				if (select == count)
				{
					return select;
				}
				count++;
			}
		} while (true);
		return -1;
	};
	~Menu()
	{
		header = nullptr;
		delete[] header;
	};
};
