#pragma once
#include <string>
#include <vector>
#include "../Project_2/LinkedList.h"
#include <chrono>

//#include "../Project2/LinkedList.cpp"
class CommitRaid {
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
		commit();
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
		~commit();
	};
	CommitRaid();
	CommitRaid(LinkedList<commit> &commits, std::chrono::system_clock::time_point time)
	{
		this->commits = commits;
		this->time = time;
	}
	LinkedList<commit> commits;
	std::chrono::system_clock::time_point time{};
};
