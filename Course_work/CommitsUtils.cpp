#include "pch.h"
#include "CommitsUtils.h"
#include <fstream>
#include <iostream>

LinkedList<std::string> CommitsUtils::read(const char* path)
{
	LinkedList<std::string> list;
	std::string line;
	std::ifstream file(path);
	if (file)
	{
		while (getline(file, line))
		{
			list.push_back(line);
		}
		//file.close();
		std::cout << path << " loaded!\n";
	}
	else
	{
		//if (path == path_original.c_str()) {
		list = read(path_changed.c_str());
		save(list, path);
		analyze_changes();
		//}
		//else
		//{
			//throw "File not found!";
		//}
	}
	file.close();
	return list;
}

void CommitsUtils::save(LinkedList<std::string> list, const char* path) const
{
	std::string line;
	auto iterator = list.create_list_iterator();
	std::ofstream file(path);
	if (file)
	{
		while (iterator->has_next())
			file << iterator->next() << std::endl;
		//file.close();
		std::cout << path << " saved!\n";
	}
	else
	{
		//throw "File not found!";
	}
	file.close();
}

LinkedList<std::string> CommitsUtils::get_original() const
{
	LinkedList<std::string> list;
	auto* iterator = original_text.create_list_iterator();
	while (iterator->has_next())
	{
		std::string line = iterator->next();
		std::string h = line;
		list.push_back(line);
	}
	return list;
}

LinkedList<std::string> CommitsUtils::get_changed() const
{
	return changed_text;
}

LinkedList<std::string> CommitsUtils::get_temp() const
{
	return temp_text;
}

void CommitsUtils::save_bin(const char* path) const
{
	std::ofstream file(path, std::ios::binary);
	if (file) {
		size_t size = commitRaid.get_size();
		file.write(reinterpret_cast<const char*>(&size), sizeof(size));

		auto* iterator = commitRaid.create_list_iterator();

		for (size_t i = 0; i < size; i++)
		{
			auto item = iterator->next();
			file.write(reinterpret_cast<const char*>(&item.time), sizeof(item.time));

			size_t commit_size = item.commits.get_size();
			file.write(reinterpret_cast<const char*>(&commit_size), sizeof(commit_size));

			auto* commit_iter = item.commits.create_list_iterator();

			for (size_t j = 0; j < commit_size; j++)
			{
				auto commit_item = commit_iter->next();
				file.write(reinterpret_cast<const char*>(&commit_item.index), sizeof(commit_item.index));
				file.write(reinterpret_cast<const char*>(&commit_item.act), sizeof(commit_item.act));
				size_t string_size = commit_item.replace_value.size();
				file.write(reinterpret_cast<const char*>(&string_size), sizeof(string_size));
				file.write(commit_item.replace_value.c_str(), commit_item.replace_value.size());
			}
		}
		file.close();
		std::cout << path << " saved!\n";
	}
	else
	{
		throw "File not found!";
	}
}

void CommitsUtils::read_bin(const char* path)
{
	std::ifstream file(path, std::ios::binary);
	commitRaid.clear();
	if (file)
	{
		size_t size = 0;
		file.read(reinterpret_cast<char*>(&size), sizeof(size));

		for (size_t i = 0; i < size; ++i)
		{
			CommitsData item;
			file.read(reinterpret_cast<char*>(&item.time),
				sizeof(item.time));
			size_t commit_size = 0;
			file.read(reinterpret_cast<char*>(&commit_size), sizeof(commit_size));
			for (size_t j = 0; j < commit_size; j++) {
				commit commit_item;
				file.read(reinterpret_cast<char*>(&commit_item.index), sizeof(commit_item.index));
				file.read(reinterpret_cast<char*>(&commit_item.act), sizeof(commit_item.act));
				size_t string_size;
				file.read(reinterpret_cast<char*>(&string_size), sizeof(string_size));
				commit_item.replace_value.resize(string_size);
				file.read(&commit_item.replace_value[0], commit_item.replace_value.size());
				item.commits.push_back(commit_item);
			}
			commitRaid.push_back(item);
		}
		file.close();
		std::cout << path << " loaded!\n";
	}
	else
	{
		save_bin(path);
	}
}

void CommitsUtils::show_commit_menu() const
{
	LinkedList<std::string> commits_history;
	commits_history.clear();
	auto* iterator = commitRaid.create_list_iterator();
	while (iterator->has_next())
	{
		CommitsData data = iterator->next();
		std::time_t raw_time = data.time;
		struct tm timeinfo;
		localtime_s(&timeinfo, &raw_time);
		char buffer[80];

		//Item<void(*)(CommitsUtils*), CommitsUtils*>
		strftime(buffer, 80, "%X %x", &timeinfo);
		commits_history.push_back(std::string(buffer));
	}
	Menu menu("Commits history");
	auto selection = menu.Show(commits_history);
	if (selection == -1 || selection >= commitRaid.get_size())
		return;
	auto text = apply_commits_history(commitRaid.at(selection).time);
	save(text, path_temp.c_str());
}

LinkedList<std::string> CommitsUtils::apply_commits_history(std::time_t time) const
{
	auto* commits_iterator = commitRaid.create_list_iterator();
	auto text = get_original();
	while (commits_iterator->has_next())
	{
		auto commit = commits_iterator->next();
		text = apply_commit(text, commit.commits);
		if (commit.time == time)
		{
			break;
		}
	}
	return text;
};

LinkedList<std::string> CommitsUtils::apply_commits(LinkedList<std::string> text) const
{
	if (!commitRaid.isEmpty())
	{
		auto* changed_iter = commitRaid.create_list_iterator();
		while (changed_iter->has_next())
		{
			auto value = changed_iter->next();
			text = apply_commit(text, value.commits);
		}
	}
	return  text;
}

LinkedList<std::string> CommitsUtils::apply_commit(LinkedList<std::string> text, LinkedList<commit> commit) const
{
	if (!commit.isEmpty())
	{
		auto* commit_iter = commit.create_list_iterator();
		while (commit_iter->has_next())
		{
			const auto value = commit_iter->next();
			switch (value.act)
			{
			case remove://remove
				text.remove(value.index);
				break;
			case insert://insert
				text.insert(value.index, value.replace_value);
				break;
			case replace://replace
				text.set(value.index, value.replace_value);
				break;
			default:
				break;
			}
		}
	}
	return text;
}

bool CommitsUtils::analyze_changes()
{
	changed_text = read(path_changed.c_str());
	LinkedList<commit> commits;
	auto* changed_iter = changed_text.create_list_iterator();
	auto* temp_iter = temp_text.create_list_iterator();
	int index = 0;
	if (temp_text.isEmpty() || changed_text.isEmpty())
	{
		if (!temp_iter->has_next()) {
			while (changed_iter->has_next()) {
				commits.push_back(commit(index++, insert, changed_iter->next()));
			}
		}
		else if (!changed_iter->has_next())
		{
			while (temp_iter->has_next()) {
				commits.push_back(commit(0, remove, temp_iter->next()));
			}
		}
	}
	else
	{
		while (changed_iter->has_next() && temp_iter->has_next())
		{
			std::string line = changed_iter->next();

			if (line != temp_iter->next())
			{
				commits.push_back(commit(index, replace, line));
			}
			index++;
		}
		if (!temp_iter->has_next()) {
			while (changed_iter->has_next()) {
				commits.push_back(commit(index++, insert, changed_iter->next()));
			}
		}
		else if (!changed_iter->has_next())
		{
			while (temp_iter->has_next()) {
				commits.push_back(commit(index, remove, temp_iter->next()));
			}
		}
	}

	const CommitsData raid(commits, std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
	commitRaid.push_back(raid);
	temp_text = apply_commit(temp_text, commits);
	save_bin(path_commits.c_str());
	return temp_text.equals(&changed_text);
}