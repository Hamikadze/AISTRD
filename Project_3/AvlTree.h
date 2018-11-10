#pragma once
#include "Iterator.h"

class AvlTree
{
public:
	AvlTree(int key);
	~AvlTree();
	class avl_iterator : public Iterator
	{
		enum move
		{
			left,
			right,
		};
		int next() override;
		bool has_next() override;
	};
public:
	class node
	{
	public:
		unsigned int Height();
		int BalanceValue();
		void FixHeight();
		node* RotateRight();
		node* RotateLeft();
		node* Balance();
		node* Insert(int key);
		node* FindMin();
		node* RemoveMin();
		node* Remove(int key);
		bool Contains(int key);
		void Print(int l);
		~node();
		int key;
		unsigned char height;
		node* left;
		bool is_root;
		node* right;
		node(int k);
	};
	node* root;
};
