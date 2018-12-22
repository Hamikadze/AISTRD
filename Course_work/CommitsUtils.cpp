#include "pch.h"
#include "CommitsUtils.h"
#include <fstream>
#include <iostream>

void CommitsUtils::save()
{
	size_t size = commitRaid.get_size();
	file_stream.write(reinterpret_cast<const char*>(&size), sizeof(size));

	auto* iterator = commitRaid.create_list_iterator();

	for (size_t i = 0; i < size; i++)
	{
		auto item = iterator->next();
		file_stream.write(reinterpret_cast<const char*>(&item.time), sizeof(item.time));

		size_t commit_size = commitRaid.get_size();
		file_stream.write(reinterpret_cast<const char*>(&commit_size), sizeof(commit_size));

		auto* commit_iter = item.commits.create_list_iterator();

		for (size_t j = 0; j < commit_size; j++)
		{
			auto commit_item = commit_iter->next();
			file_stream.write(reinterpret_cast<const char*>(&commit_item.index), sizeof(commit_item.index));
			file_stream.write(reinterpret_cast<const char*>(&commit_item.act), sizeof(commit_item.act));
			file_stream.write(reinterpret_cast<const char*>(&commit_item.lenght), sizeof(commit_item.lenght));
			size_t string_size = commit_item.replace_value.size();
			file_stream.write(reinterpret_cast<const char*>(&string_size), sizeof(string_size));
			file_stream.write(commit_item.replace_value.c_str(), commit_item.replace_value.size());
		}
	}
}

void CommitsUtils::read()
{
	size_t size = 0;
	file_stream.read(reinterpret_cast<char*>(&size), sizeof(size));

	for (size_t i = 0; i < size; ++i)
	{
		CommitsRaid item;
		file_stream.read(reinterpret_cast<char*>(&item.time),
			sizeof(item.time));
		size_t commit_size = 0;
		file_stream.read(reinterpret_cast<char*>(&commit_size), sizeof(commit_size));
		for (size_t j = 0; j < commit_size; j++) {
			CommitsRaid::commit commit_item;
			file_stream.read(reinterpret_cast<char*>(&commit_item.index), sizeof(commit_item.index));
			file_stream.read(reinterpret_cast<char*>(&commit_item.act), sizeof(commit_item.act));
			file_stream.read(reinterpret_cast<char*>(&commit_item.lenght), sizeof(commit_item.lenght));
			size_t string_size;
			file_stream.read(reinterpret_cast<char*>(&string_size), sizeof(string_size));
			commit_item.replace_value.resize(string_size);
			file_stream.read(&commit_item.replace_value[0], commit_item.replace_value.size());
			item.commits.push_back(commit_item);
		}
		commitRaid.push_back(item);
	}
}

void CommitsUtils::show_commit_menu()
{
	auto* iterator = commitRaid.create_list_iterator();
	while (iterator->has_next())
	{
		std::time_t raw_time = iterator->next().time;
		struct tm timeinfo;
		localtime_s(&timeinfo, &raw_time);
		char buffer[80];

		strftime(buffer, 80, "%X %x", &timeinfo);
		std::cout << buffer << std::endl;
	}
}

//first second - indexes => apply
//first - index & second - 0 => insert to first index
//first - index & second - -1 => remove line on index

void Apply_Commit(LinkedList<std::string>& text, LinkedList<CommitsRaid::commit>& commit)
{
	if (!commit.isEmpty())
	{
		auto* commit_iter = commit.create_list_iterator();
		while (commit_iter->has_next())
		{
			const auto value = commit_iter->next();
			switch (value.act)
			{
			case CommitsRaid::remove://remove
				text.remove(value.index);
				break;
			case CommitsRaid::insert://insert
				text.insert(value.index, value.replace_value);
				break;
			case CommitsRaid::replace://replace
				text.set(value.index, value.replace_value);
				break;
			default:
				//TODO add exception
				break;
			}
		}
	}
}
//
//void CommitsUtils::Apply_Commits(LinkedList<std::string>& text)
//{
//	if (!commitRaid.isEmpty())
//	{
//		auto* changed_iter = commitRaid.create_list_iterator();
//		while (changed_iter->has_next())
//		{
//			auto value = changed_iter->next();
//			Apply_Commit(text, value.commits);
//		}
//	}
//}

void CommitsUtils::Analyze_Changes(LinkedList<std::string> &changed_text, LinkedList<std::string> &temp_text)
{
	LinkedList<CommitsRaid::commit> commits;
	auto* changed_iter = changed_text.create_list_iterator();
	auto* temp_iter = temp_text.create_list_iterator();
	int count_temp = 0;
	int count_changed = 0;
	if (temp_text.isEmpty() || changed_text.isEmpty())
	{
		int count = 0;
		if (temp_text.isEmpty()) {
			while (changed_iter->has_next()) {
				commits.push_back(CommitsRaid::commit(count++, CommitsRaid::insert, changed_iter->next()));
			}
		}
		else if (changed_text.isEmpty())
		{
			while (temp_iter->has_next()) {
				commits.push_back(CommitsRaid::commit(0, CommitsRaid::remove, temp_iter->next()));
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
					commits.push_back(CommitsRaid::commit(count_changed, CommitsRaid::remove));
					count_temp += 2;
					count_changed++;
				}
				else
				{
					if (temp_text.get_size() > (count_temp + 1) && changed_text.get_size() > (count_changed + 1) && changed_text.at(count_changed + 1) == temp_text.at(count_temp + 1))
					{
						commits.push_back(CommitsRaid::commit(count_changed, CommitsRaid::replace, line));
						count_temp += 2;
						count_changed += 2;
					}
					else
					{
						commits.push_back(CommitsRaid::commit(count_changed, CommitsRaid::insert, line));
					}
				}
			}
			count_temp++;
			count_changed++;
		}
	}

	//Apply_Commit(temp_text, commits);
	const CommitsRaid raid(commits, std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
	commitRaid.push_back(raid);
	//===========================
	std::ofstream commits_file_out("commits.txt", std::ios::out);
	if (commits_file_out)
	{
		std::cout << "commits.txt saved!\n";
		save();
	}
	commits_file_out.close();
}