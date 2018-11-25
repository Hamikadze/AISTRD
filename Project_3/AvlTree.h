#pragma once
#include "Iterator.h"
#include <stack>
#include <queue>
using namespace std;

class AvlTree
{
public:
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
	class SftIterator : public Iterator
	{
	public:
		SftIterator(node * root)
		{
			current = root;
		};
		int next() override;
		bool has_next() override;

	private:
		std::stack<node*> s;
		node * current;
	};
public:
	void Insert(int key);
	void Remove(int key);
	bool Contains(int key) const;
	void Print() const;
	Iterator* create_dft_iterator() const; // создание итератора, реализующего методы обхода в глубину (depth-first traverse)
	Iterator* create_bft_iterator() const; // создание итератора, реализующего методы обхода в ширину (breadth-first traverse)
	Iterator* create_sft_iterator() const;
};
