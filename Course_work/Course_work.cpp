// Course_work.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <windows.h>
#include "../Project_2/LinkedList.h"
#include "../Project_2/LinkedList.cpp"
#include "CommitsData.h"

typedef void(*Menu_Processing_Function)(void);
LinkedList<std::string> temp_text;//temp text without new but with last changes
LinkedList<std::string> changed_text;//file with changes
LinkedList<std::string> original_text;//file original
LinkedList<CommitRaid::commit> commits;
LinkedList<CommitRaid> commitRaid;

struct Menu_Option
{
	char choice;
	char const * selection_text;
	Menu_Processing_Function processing_function;
};

void Process_Selection_Exit()
{
	std::exit(0);
};

//first second - indexes => apply
//first - index & second - 0 => insert to first index
//first - index & second - -1 => remove line on index

void Apply_Commit(LinkedList<std::string>& text, LinkedList<CommitRaid::commit>& commit)
{
	if (!commit.isEmpty())
	{
		auto* commit_iter = commit.create_list_iterator();
		while (commit_iter->has_next())
		{
			const auto value = commit_iter->next();
			switch (value.act)
			{
			case CommitRaid::remove://remove
				text.remove(value.index);
				break;
			case CommitRaid::insert://insert
				text.insert(value.index, value.replace_value);
				break;
			case CommitRaid::replace://replace
				text.set(value.index, value.replace_value);
				break;
			default:
				//TODO add exception
				break;
			}
		}
	}
}

void Apply_Commits(LinkedList<std::string>& text, LinkedList<CommitRaid> _commitRaid)
{
	if (!_commitRaid.isEmpty())
	{
		auto* changed_iter = _commitRaid.create_list_iterator();
		while (changed_iter->has_next())
		{
			auto value = changed_iter->next();
			Apply_Commit(text, value.commits);
		}
	}
}

//std::pair<int, std::string> Find(std::string find_line, LinkedList<std::string> list, size_t from_index)
//{
//	auto* iter = list.create_list_iterator();
//	if (!iter->has_next())
//		return std::make_pair(-2, "");//list is empty
//	while (iter->has_next())
//		if (iter->next().first == from_index)
//			break;
//	while (iter->has_next()) {
//		auto compare_line = iter->next();
//		if (find_line == compare_line.second)
//		{
//			return compare_line;//something find
//		}
//	}
//	return std::make_pair(-1, "");//nothing find
//}

void Process_Selection_Save_Changes()
{
	auto* changed_iter = changed_text.create_list_iterator();
	auto* temp_iter = temp_text.create_list_iterator();
	int count_temp = 0;
	int count_changed = 0;
	if (temp_text.isEmpty() || changed_text.isEmpty())
	{
		int count = 0;
		if (temp_text.isEmpty()) {
			while (changed_iter->has_next()) {
				commits.push_back(CommitRaid::commit(count++, CommitRaid::insert, changed_iter->next()));
			}
		}
		else if (changed_text.isEmpty())
		{
			while (temp_iter->has_next()) {
				commits.push_back(CommitRaid::commit(0, CommitRaid::remove, temp_iter->next()));
			}
		}
	}
	else {
		while (changed_text.get_size() > count_changed)
		{
			std::string line = changed_text.at(count_changed);

			if (temp_text.get_size() > count_temp && line != temp_text.at(count_temp))
			{
				if (temp_text.get_size() > (count_temp + 1) && line == temp_text.at(count_temp + 1))
				{
					commits.push_back(CommitRaid::commit(count_changed, CommitRaid::remove));
					count_temp += 2;
					count_changed++;
				}
				else
				{
					if (temp_text.get_size() > (count_temp + 1) && changed_text.get_size() > (count_changed + 1) && changed_text.at(count_changed + 1) == temp_text.at(count_temp + 1))
					{
						commits.push_back(CommitRaid::commit(count_changed, CommitRaid::replace, line));
						count_temp += 2;
						count_changed += 2;
					}
					else
					{
						commits.push_back(CommitRaid::commit(count_changed, CommitRaid::insert, line));
					}
				}
			}
			count_temp++;
			count_changed++;
		}
	}

	const CommitRaid raid(commits, std::chrono::system_clock::now());
	Apply_Commit(temp_text, commits);
	commitRaid.push_back(raid);
	//===========================
	std::ofstream commits_file_out("commits.txt", std::ios::out);
	if (commits_file_out)
	{
		std::cout << "commits.txt saved!\n";
		commits_file_out.write(reinterpret_cast<char*>(&commitRaid), sizeof(commitRaid));
		commits_file_out.close();
	}
};

void Process_Selection_View_History()
{
	std::exit(0);
}

void Process_Selection_Initial_File()
{
	std::cout << "Enter file location : ";
	std::exit(0);
}

void Process_Selection_Open_File()
{
	std::exit(0);
}

static const Menu_Option main_menu[] =
{
	{'0', "Exit", Process_Selection_Exit},
	{'1', "Save changes", Process_Selection_Save_Changes},
	{'2', "Initial file", Process_Selection_Initial_File},
	{'3', "Open file", Process_Selection_Open_File},
	{'4', "View history", Process_Selection_View_History}
};

static const size_t quantity_seletions = sizeof(main_menu) / sizeof(main_menu[0]);

int main()
{
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

	std::ifstream commits_file_in("commits.txt", std::ios::in);
	if (commits_file_in)
	{
		std::cout << "commits.txt loaded!\n";
		commits_file_in.read(reinterpret_cast<char*>(&commitRaid), sizeof(commitRaid));
		commits_file_in.close();
	}

	std::ofstream commits_file_out("commits.txt", std::ios::out);
	if (commits_file_out)
	{
		std::cout << "commits.txt saved!\n";
		commits_file_out.write(reinterpret_cast<char*>(&commitRaid), sizeof(commitRaid));
		commits_file_out.close();
	}

	//==================================
	LIterator<CommitRaid>* commits_list = commitRaid.create_list_iterator();
	while (commits_list->has_next())
	{
		CommitRaid data = commits_list->next();
	}

	Process_Selection_Save_Changes();

	//==================================
	static const char* menu_title =
		"\n"
		"========================================\n"
		"              Main menu\n"
		"========================================\n";
	std::cout << menu_title;
	do {
		for (size_t i = 0; i < quantity_seletions; i++)
		{
			std::cout << "[" << main_menu[i].choice << "] " << main_menu[i].selection_text << "\n";
		}
		std::cout << "Enter selection, 0 to quit: ";
		char choice;
		std::cin >> choice;
		for (size_t i = 0; i < quantity_seletions; i++)
		{
			if (choice == main_menu[i].choice)
			{
				Menu_Processing_Function function = main_menu[i].processing_function;
				(function)();
				//break;
			}
		}
	} while (true);
	return 0;
}