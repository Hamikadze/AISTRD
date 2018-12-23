#pragma once
#include "CommitsData.h"
#include <fstream>
#include "Menu.h"

class CommitsUtils :CommitsData
{
private:

	LinkedList<std::string> temp_text;//temp text without new but with last changes
	LinkedList<std::string> changed_text;//file with changes
	LinkedList<std::string> original_text;//file original
	LinkedList<CommitsData> commitRaid;
	std::string path_original;
	std::string path_changed;
	std::string path_commits;

public:
	CommitsUtils(const char* path)
	{
		std::string path_changed(path);
		path_changed.append(".txt");
		this->path_changed = path_changed;
		std::string path_original(path);
		path_original.append("_original.txt");
		this->path_original = path_original;
		std::string path_commits(path);
		path_commits.append("_commits.bin");
		this->path_commits = path_commits;
		read_bin(path_commits.c_str());
		changed_text = read(path_changed.c_str());
		original_text = read(path_original.c_str());
		temp_text = get_original();
		temp_text = apply_commits(temp_text);
	};
private:
	~CommitsUtils()
	{
		//Non pointer objects, nothing to delete
	}
	LinkedList<std::string> read(const char* path);
	void save(LinkedList<std::string> list, const char* path);
	void read_bin(const char* path);
	void save_bin(const char* path);
	LinkedList<std::string> get_original();
	LinkedList<std::string> get_changed();
	LinkedList<std::string> get_temp();
	LinkedList<std::string> apply_commits_history(std::time_t time);
	LinkedList<std::string> apply_commits(LinkedList<std::string> text);
	LinkedList<std::string> apply_commit(LinkedList<std::string> text, LinkedList<commit> commit);
public:
	void show_commit_menu();
	bool analyze_changes();
};
