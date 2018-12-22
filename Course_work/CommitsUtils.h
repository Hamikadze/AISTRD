#pragma once
#include "CommitsRaid.h"
#include <fstream>
#include "Menu.h"
#include "Menu.cpp"

class CommitsUtils
{
private:
	std::fstream file_stream;
	LinkedList<CommitsRaid> commitRaid;
public:
	CommitsUtils() {}
	CommitsUtils(const char* path)
	{
		file_stream.open(path, std::ios::in | std::ios::out | std::ios::binary);
	};
	~CommitsUtils()
	{
		if (file_stream.is_open())
			file_stream.close();
	}
	void save();
	void read();
	void show_commit_menu();
	//void Apply_Commits(LinkedList<std::string>& text);
	void Apply_Commit(LinkedList<std::string>& text, LinkedList<CommitsRaid::commit>& commit);
	void Analyze_Changes(LinkedList<std::string> &changed_text, LinkedList<std::string> &temp_text);
};
