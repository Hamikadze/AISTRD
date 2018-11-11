#include "pch.h"
#include "AvlTree.h"
#include <iostream>

AvlTree::AvlTree(int key)
{
	root = new node(key);
}

Iterator* AvlTree::create_dft_iterator()
{
	return new DftIterator(this->root);
}

Iterator*AvlTree::create_bft_iterator()
{
	return new BftIterator(this->root);
}

AvlTree::~AvlTree()
{
}
int AvlTree::DftIterator::next()
{
	/*if (node == null) return;
	console.log(node.value);
	preOrder(node.left);
	preOrder(node.right);*/

	/*if (node == null) return;
		inOrder(node.left);
		console.log(node.value);
		inOrder(node.right);*/

	if (current != nullptr) {
		int key = current->key;
		if (current->right != nullptr)
			s.push(current);
		current = current->left;
		return key;
	}
	if (current == nullptr) {
		current = s.top();
		s.pop();
		current = current->right;
		next();
	}
}

bool AvlTree::DftIterator::has_next()
{
	return (s.size() || current != nullptr);
}

//
//int AvlTree::AvlIterator::next()
//{
//	while (current != nullptr) {
//		s.push(current);
//		current = current->left;
//	}
//	current = s.top();
//	s.pop();
//	const int key = current->key;
//	current = current->right;
//	return key;
//}
//
//bool AvlTree::AvlIterator::has_next()
//{
//	return (s.size() || current != nullptr);
//}

AvlTree::node::~node()
{
}

AvlTree::node::node(int k)
{
	key = k; left = right = nullptr; height = 1;
}

int AvlTree::BftIterator::next()
{
	if (q.size() == 0)
		q.push(current);
	current = q.front();
	q.pop();
	const int key = current->key;
	if (current->left) {
		q.push(current->left);
	}
	if (current->right) {
		q.push(current->right);
	}
	return key;
}

bool AvlTree::BftIterator::has_next()
{
	return (q.size() || current->left != nullptr && current->right != nullptr);
}

void AvlTree::Insert(int key)
{
	root = root->insert(key);
}

void AvlTree::Remove(int key)
{
	root = root->remove(key);
}

bool AvlTree::Contains(int key)
{
	return root->contains(0);
}

void AvlTree::Print()
{
	root->print(0);
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

AvlTree::node* AvlTree::node::rotate_right()
{
	node * q = this->left;
	this->left = q->right;
	q->right = this;
	this->FixHeight();
	q->FixHeight();
	return q;
}

AvlTree::node* AvlTree::node::rotate_left()
{
	node * p = this->right;
	this->right = p->left;
	p->left = this;
	this->FixHeight();
	p->FixHeight();
	return p;
}

AvlTree::node* AvlTree::node::balance()
{
	this->FixHeight();
	switch (this->BalanceValue())
	{
	case 2:
		if (this->right->BalanceValue() < 0)
		{
			this->right = this->right->rotate_right();
		}
		return this->rotate_left();
	case -2:
		if (this->left->BalanceValue() > 0)
		{
			this->left = this->left->rotate_left();
		}
		return this->rotate_right();
	default: return this;
	}
}

AvlTree::node* AvlTree::node::insert(int key)
{
	if (!this) return new node(key);
	if (key < this->key)
	{
		this->left = this->left->insert(key);
	}
	else
	{
		this->right = this->right->insert(key);
	}
	return this->balance();
}

AvlTree::node* AvlTree::node::find_min()
{
	return  this->left ? this->left->find_min() : this;
}

AvlTree::node* AvlTree::node::remove_min()
{
	if (this->left == nullptr)
	{
		return this->right;
	}
	this->left = this->left->remove_min();
	return this->balance();
}

AvlTree::node* AvlTree::node::remove(int key)
{
	if (!this) return nullptr;
	if (key < this->key)
	{
		this->left = this->left->remove(key);
	}
	else if (key > this->key)
	{
		this->right = this->right->remove(key);
	}
	else // k == p->key
	{
		node* q = this->left;
		node* r = this->right;
		delete this;
		if (!r)return q;
		node* min = r->find_min();
		min->right = remove_min();
		min->left = q;
		return min->balance();
	}
	return this->balance();
}

bool AvlTree::node::contains(int key)
{
	if (!this) return false;
	if (key < this->key)
	{
		return this->left->contains(key);
	}
	else if (key > this->key)
	{
		return this->right->contains(key);
	}
	else // k == p->key
	{
		return true;
	}
}

void AvlTree::node::print(int l)
{
	if (this)
	{
		this->left->print(l + 1);
		for (int i = 0; i < l; i++) std::cout << "   ";
		std::cout << this->key << std::endl;
		this->right->print(l + 1);
	}
}