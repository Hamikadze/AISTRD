#pragma once
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>
#include "../Project_2/Iterator.h"
#include "../Project_2/LinkedList.h"
#include "../Project_2/LinkedList.cpp"
#include <fstream>

//#include "../Project2/LinkedList.cpp"
class CommitsData {
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
		commit(size_t from_index, action act, std::string replace_value = "")
		{
			this->index = from_index;
			this->act = act;
			this->replace_value = replace_value;
		}
		~commit()
		{
			//Non pointer objects, nothing to delete
		}
		size_t index;
		action act;
		std::string replace_value;
	};
	~CommitsData()
	{
		//Non pointer objects, nothing to delete
	};
	CommitsData() {};
	CommitsData(LinkedList<commit> &commits, std::time_t time)
	{
		this->commits = commits;
		this->time = time;
	}
	LinkedList<commit> commits;
	std::time_t time;
};