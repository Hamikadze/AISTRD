#pragma once
#include "CommitsData.h"
#include <fstream>
#include "Menu.h"

class CommitsUtils :CommitsData
{
public:

	LinkedList<std::string> temp_text;//temp text without new but with last changes
	LinkedList<std::string> changed_text;//file with changes
	LinkedList<std::string> original_text;//file original
	LinkedList<CommitsData> commitRaid;
	std::string path_original;
	std::string path_changed;
	std::string path_commits;
	std::string path_temp;

public:
	CommitsUtils(const char* path)
	{
		try {
			std::string path_changed(path);
			int dot_index = path_changed.find_last_of(".");
			this->path_changed = path_changed;

			std::string path_original(path);
			path_original.insert(dot_index, "_original");
			this->path_original = path_original;

			std::string path_temp(path);
			path_temp.insert(dot_index, "_temp");
			this->path_temp = path_temp;

			std::string path_commits(path);
			path_commits = path_commits.substr(0, dot_index);
			path_commits.append("_commits.bin");

			this->path_commits = path_commits;
			read_bin(path_commits.c_str());
			changed_text = read(path_changed.c_str());
			original_text = read(path_original.c_str());
			temp_text = get_original();
			temp_text = apply_commits(temp_text);
		}
		catch (char* e)
		{
			throw e;
		}
	};
private:
	~CommitsUtils()
	{
		//Non pointer objects, nothing to delete
	}
	LinkedList<std::string> read(const char* path);
	void save(LinkedList<std::string> list, const char* path) const;
	void read_bin(const char* path);
	void save_bin(const char* path) const;
public:
	LinkedList<std::string> apply_commits_history(std::time_t time) const;
	LinkedList<std::string> apply_commits(LinkedList<std::string> text) const;
	LinkedList<std::string> apply_commit(LinkedList<std::string> text, LinkedList<commit> commit) const;
	LinkedList<std::string> get_original() const;
	LinkedList<std::string> get_changed() const;
	LinkedList<std::string> get_temp() const;
public:
	void show_commit_menu() const;
	bool analyze_changes();
};
