#pragma once
#include <stack>
#include <queue>
//#include "../Project_2/LinkedList.h"
#include "../Project_2/Iterator.h"
#include "../Project_2/LinkedList.h"
#include "../Project_2/LinkedList.cpp"
using namespace std;

class AvlTree
{
	class node
	{
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
		void print(string indent, bool last, bool right) const;
		bool contains(int key);
		node* remove(int key);
		node* Delete();
		node* insert(int key);
		int key;
		node* left;
		node* right;
	};
	node* root;

	class DftIterator : public LIterator<int>
	{
	public:
		DftIterator(node * root)
		{
			current = root;
		};

	private:
		int next() override;
		bool has_next() override;
		LinkedList<node*> list;
		node * current;
	};

	class BftIterator : public LIterator<int>
	{
	public:
		BftIterator(node * root)
		{
			current = root;
		};

	private:
		int next() override;
		bool has_next() override;
		LinkedList<node*> list;
		node * current;
	};
	class SftIterator : public LIterator<int>
	{
	public:
		SftIterator(node * root)
		{
			current = root;
		};

	private:
		int next() override;
		bool has_next() override;
		LinkedList<node*> list;
		node * current;
	};
public:
	AvlTree(int key);
	AvlTree();
	~AvlTree();
	void Insert(int key);
	void Remove(int key);
	bool Contains(int key) const;
	void Print() const;
	LIterator<int>* create_dft_iterator() const; // создание итератора, реализующего методы обхода в глубину (depth-first traverse)
	LIterator<int>* create_bft_iterator() const; // создание итератора, реализующего методы обхода в ширину (breadth-first traverse)
	LIterator<int>* create_sft_iterator() const;
};
