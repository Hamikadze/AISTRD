#pragma once
#include "Iterator.h"
#include <stack>
#include <queue>
#include "../Project_2/LinkedList.h"
#include "../Project_2/LinkedList.cpp"
using namespace std;

class AvlTree
{
public://TODO fix it
	class node
	{
	private:
		~node();
		unsigned char height;
		unsigned int Height();
		int BalanceValue() const;
		void FixHeight();
		node* rotate_right();
		node* rotate_left();
		node* balance();
		node* find_min();
		node* remove_min();
	public:
		node(int k);
		int key;
		node* left;
		node* right;
		node* insert(int key);
		node* remove(int key);
		node* Delete();
		bool contains(int key);
		void print(string indent, bool last, bool right) const;
	};
public:
	node* root;

public:
	AvlTree(int key);
	AvlTree();
	~AvlTree();
	class DftIterator : public Iterator<int>
	{
	public:
		DftIterator(node * root)
		{
			current = root;
		};
		int next() override;
		bool has_next() override;

	private:
		LinkedList<node*> list;
		node * current;
	};

	class BftIterator : public Iterator<int>
	{
	public:
		BftIterator(node * root)
		{
			current = root;
		};
		int next() override;
		bool has_next() override;

	private:
		LinkedList<node*> list;
		node * current;
	};
	class SftIterator : public Iterator<int>
	{
	public:
		SftIterator(node * root)
		{
			current = root;
		};
		int next() override;
		bool has_next() override;

	private:
		LinkedList<node*> list;
		node * current;
	};
public:
	void Insert(int key);
	void Remove(int key);
	bool Contains(int key) const;
	void Print() const;
	Iterator<int>* create_dft_iterator() const; // создание итератора, реализующего методы обхода в глубину (depth-first traverse)
	Iterator<int>* create_bft_iterator() const; // создание итератора, реализующего методы обхода в ширину (breadth-first traverse)
	Iterator<int>* create_sft_iterator() const;
};
