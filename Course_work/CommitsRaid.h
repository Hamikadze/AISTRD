#pragma once
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>
#include "../Project_2/Iterator.h"
#include "../Project_2/LinkedList.h"
#include "../Project_2/LinkedList.cpp"

//#include "../Project2/LinkedList.cpp"
class CommitsRaid {
public:
	enum action
	{
		remove,
		replace,
		insert,
	};
	class commit
	{
	public:
		commit() {};
		commit(size_t from_index, action act, std::string replace_value = nullptr, size_t lenght = 0)
		{
			this->index = from_index;
			this->act = act;
			this->lenght = lenght;
			this->replace_value = replace_value;
		}

		size_t index;
		action act;
		size_t lenght;
		std::string replace_value;
		//~commit();
	};
	CommitsRaid() {};
	CommitsRaid(LinkedList<commit> &commits, std::time_t time)
	{
		this->commits = commits;
		this->time = time;
	}
	LinkedList<commit> commits;
	std::time_t time;
};
