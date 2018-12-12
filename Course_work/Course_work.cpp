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
LinkedList<std::pair<int, std::string>> temp_text;//temp text without new but with last changes
LinkedList<std::pair<int, std::string>> changed_text;//file with changes
LinkedList<std::pair<int, std::string>> original_text;//file original

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

void Apply_Commit(LinkedList<std::pair<int, std::string>>& text, LinkedList<CommitRaid::commit> commit)
{
	if (!commit.isEmpty())
	{
		auto* commit_iter = commit.create_list_iterator();
		while (commit_iter->has_next())
		{
			auto value = commit_iter->next();
			switch (value.to_index)
			{
			case -1://remove
				for (int i = 0; i < value.lenght; i++)
					text.remove(value.from_index);
				break;
			case 0://insert
				if (!value.replace_value.isEmpty()) {
					auto* insert_text_iter = value.replace_value.create_list_iterator();
					int index_counter = value.from_index;
					while (insert_text_iter->has_next())
					{
						text.insert(index_counter, std::make_pair(index_counter, insert_text_iter->next()));
						index_counter++;
					}
				}
				break;
			default://replace
				if (!value.replace_value.isEmpty()) {
					auto* insert_text_iter = value.replace_value.create_list_iterator();
					int index_counter = value.from_index;
					while (insert_text_iter->has_next())
					{
						text.set(index_counter, std::make_pair(index_counter, insert_text_iter->next()));
						index_counter++;
					}
				}
				break;
			}
		}
	}
}

void Apply_Commits(LinkedList<std::pair<int, std::string>>& text, LinkedList<CommitRaid> _commitRaid)
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

std::pair<int, std::string> Find(std::pair<int, std::string> find_line, Iterator<std::pair<int, std::string>>* iterator)
{
	if (!iterator->has_next())
		return std::make_pair(-1, "");
	const std::pair<int, std::string> compare_line = iterator->next();
	if (find_line.second != compare_line.second)
	{
		return Find(find_line, iterator);
	}
	else
	{
		return compare_line;
	}
}

void Process_Selection_Save_Changes()
{
	auto* changed_iter = changed_text.create_list_iterator();
	auto* temp_iter = temp_text.create_list_iterator();
	LinkedList<CommitRaid::commit> commits;
	while (!changed_text.equals(&temp_text))
	{
		std::pair<int, std::string> changes = changed_iter->next();
		std::pair<int, std::string> temp = temp_iter->next();
		if (changes.second != temp.second)
		{//add iter check line by line if forward its comparable
			auto temp_temp = new LinkedList<std::pair<int, std::string>>::ListIterator(changed_iter);
			std::pair<int, std::string> find_result = Find(changes, temp_temp);
			LinkedList<std::string> replace_lines;
			if (find_result.first == -1)//nothing find
			{
				replace_lines.push_back(changes.second);
				//continue;
			}
			else // somethind find and all betwin it must be deleted
			{
				/*while (changed_iter->has_next())
				{
					auto value = changed_iter->next();
					if (value.first == find_result.first)
						break;
					replace_lines.push_back(value.second);
				}*/
				while ((temp = temp_iter->next()).first != find_result.first);//Перемотка

				const CommitRaid::commit commit(changes.first, -1, LinkedList<std::string>(), find_result.first - changes.first);
				commits.push_back(commit);
				continue;
			}
			const CommitRaid::commit commit(changes.first, find_result.first, replace_lines);
			commits.push_back(commit);
		}
	}
	const CommitRaid raid(commits, std::chrono::system_clock::now());
	commitRaid.push_back(raid);
	Apply_Commit(temp_text, commits);
	//===========================
	std::ofstream commits_file_out("commits.txt", std::ios::out);
	if (commits_file_out)
	{
		std::cout << "commits.txt saved!\n";
		commits_file_out.write(reinterpret_cast<char*>(&commits), sizeof(commits));
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
			changed_text.push_back(std::make_pair(index, line));
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
			original_text.push_back(std::make_pair(index, line));
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
	Iterator<CommitRaid>* commits_list = commitRaid.create_list_iterator();
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