#pragma once
#include "Iterator.h"
#include <stack>
#include <queue>
using namespace std;

class AvlTree
{
	class node
	{
	public:
		unsigned int Height();
		int BalanceValue();
		void FixHeight();
		node* rotate_right();
		node* rotate_left();
		node* balance();
		node* find_min();
		node* remove_min();
		node* insert(int key);
		node* remove(int key);
		bool contains(int key);
		void print(int l);
		node(int k);
		~node();
		int key;
		unsigned char height;
		node* left;
		node* right;
	};
private:
	node* root;

public:
	AvlTree(int key);
	~AvlTree();
	class DftIterator : public Iterator
	{
	public:
		DftIterator(node * root)
		{
			current = root;
		};
		int next() override;
		bool has_next() override;

	private:
		std::stack <node*> s;
		node * current;
	};

	class BftIterator : public Iterator
	{
	public:
		BftIterator(node * root)
		{
			current = root;
		};
		int next() override;
		bool has_next() override;

	private:
		std::queue<node*> q;
		node * current;
	};
public:
	void Insert(int key);
	void Remove(int key);
	bool Contains(int key);
	void Print();
	Iterator* create_dft_iterator(); // создание итератора, реализующего методы обхода в глубину (depth-first traverse)
	Iterator* create_bft_iterator(); // создание итератора, реализующего методы обхода в ширину (breadth-first traverse)
};
