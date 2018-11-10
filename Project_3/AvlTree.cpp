#include "pch.h"
#include "AvlTree.h"
#include <iostream>

AvlTree::AvlTree(int key)
{
	root = new node(key);
	root->is_root = true;
}

AvlTree::~AvlTree()
{
}

int AvlTree::avl_iterator::next()
{
	return 0;
}

bool AvlTree::avl_iterator::has_next()
{
	return false;
}

AvlTree::node::~node()
{
}

AvlTree::node::node(int k)
{
	key = k; left = right = nullptr; height = 1;
}

unsigned AvlTree::node::Height()
{
	return this ? this->height : 0;
}

int AvlTree::node::BalanceValue()
{
	return this->right->Height() - this->left->Height();
}

void AvlTree::node::FixHeight()
{
	unsigned int height_left = this->left->Height();
	unsigned int height_right = this->right->Height();

	this->height = (height_left > height_right ? height_left : height_right) + 1;
}

AvlTree::node* AvlTree::node::RotateRight()
{
	node * q = this->left;
	this->left = q->right;
	q->right = this;
	this->FixHeight();
	q->FixHeight();
	return q;
}

AvlTree::node* AvlTree::node::RotateLeft()
{
	node * p = this->right;
	this->right = p->left;
	p->left = this;
	this->FixHeight();
	p->FixHeight();
	return p;
}

AvlTree::node* AvlTree::node::Balance()
{
	this->FixHeight();
	switch (this->BalanceValue())
	{
	case 2:
		if (this->right->BalanceValue() < 0)
		{
			this->right = this->right->RotateRight();
		}
		return this->RotateLeft();
	case -2:
		if (this->left->BalanceValue() > 0)
		{
			this->left = this->left->RotateLeft();
		}
		return this->RotateRight();
	default: return this;
	}
}

AvlTree::node* AvlTree::node::Insert(int key)
{
	if (!this) return new node(key);
	if (key < this->key)
	{
		this->left = this->left->Insert(key);
	}
	else
	{
		this->right = this->right->Insert(key);
	}
	return this->Balance();
}

AvlTree::node* AvlTree::node::FindMin()
{
	return  this->left ? this->left->FindMin() : this;
}

AvlTree::node* AvlTree::node::RemoveMin()
{
	if (this->left == nullptr)
	{
		return this->right;
	}
	this->left = this->left->RemoveMin();
	return this->Balance();
}

AvlTree::node* AvlTree::node::Remove(int key)
{
	if (!this) return nullptr;
	if (key < this->key)
	{
		this->left = this->left->Remove(key);
	}
	else if (key > this->key)
	{
		this->right = this->right->Remove(key);
	}
	else // k == p->key
	{
		node* q = this->left;
		node* r = this->right;
		delete this;
		if (!r)return q;
		node* min = r->FindMin();
		min->right = RemoveMin();
		min->left = q;
		return min->Balance();
	}
	return this->Balance();
}

void AvlTree::node::Print(int l)
{
	if (this)
	{
		this->left->Print(l + 1);
		for (int i = 0; i < l; i++) std::cout << "   ";
		std::cout << this->key << std::endl;
		this->right->Print(l + 1);
	}
}