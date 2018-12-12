//#pragma once
//#include <string>
//#include "../Project_2/LinkedList.h"
//
//class StringUtils : protected LinkedList<std::pair<int, std::string>>, protected Node<std::pair<int, std::string>>, LinkedList<std::pair<int, std::string>>::ListIterator
//{
//public:
//	std::pair<int, std::string> find(std::pair<int, std::string> string);
//	bool contains(std::pair<int, std::string> string);
//	Node* next(int i);
//};
//
//class StringIterator :Iterator<Node<std::pair<int, std::string>>>
//{
//public:
//	StringIterator(Node<Node<std::pair<int, std::string>>>* head)
//	{
//		current = head;
//	};
//	Node<std::pair<int, std::string>> next() override;
//	bool has_next() override;
//
//private:
//	//LinkedList<Node*> list;
//	Node<Node<std::pair<int, std::string>>>* current;
//};
