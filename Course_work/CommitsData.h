#pragma once
#include <string>
#include <vector>
#include "../Project_2/LinkedList.h"
#include <chrono>

//#include "../Project2/LinkedList.cpp"
class CommitRaid {
public:
	class commit
	{
	public:
		commit();
		commit(size_t from_index, size_t to_index, LinkedList<std::string> replace_value = LinkedList<std::string>(), size_t lenght = 0)
		{
			this->from_index = from_index;
			this->to_index = to_index;
			this->lenght = lenght;
			this->replace_value = replace_value;
		}

		size_t from_index;
		size_t to_index;
		size_t lenght;
		LinkedList<std::string> replace_value;
		~commit();
	};
	CommitRaid();
	CommitRaid(LinkedList<commit> commits, std::chrono::system_clock::time_point time)
	{
		this->commits = commits;
		this->time = time;
	}
	LinkedList<commit> commits;
	std::chrono::system_clock::time_point time;
};
