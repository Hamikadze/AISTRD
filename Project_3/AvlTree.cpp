#include "pch.h"
#include "AvlTree.h"
#include <iostream>
#include <string>
#include <windows.h>

AvlTree::AvlTree(const int key)
{
	root = new node(key);
}

AvlTree::AvlTree()
{
	root = nullptr;
}

Iterator* AvlTree::create_dft_iterator() const
{
	if (this == nullptr && this->root == nullptr) throw std::exception("Tree does not exist");
	return new DftIterator(this->root);
}

Iterator*AvlTree::create_bft_iterator() const
{
	if (this == nullptr && this->root == nullptr) throw std::exception("Tree does not exist");
	return new BftIterator(this->root);
}

Iterator* AvlTree::create_sft_iterator() const
{
	if (this == nullptr && this->root == nullptr) throw std::exception("Tree does not exist");
	return new SftIterator(this->root);
}

AvlTree::~AvlTree()
{
	root->Delete();
	if (root->left != nullptr)
		root->left = nullptr;
	if (root->right != nullptr)
		root->right = nullptr;
	root = nullptr;
}

int AvlTree::DftIterator::next()
{
	if (current != nullptr) {
		const int key = current->key;
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

AvlTree::node::~node()
{
	free(this);
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

int AvlTree::SftIterator::next()
{
	while (current != nullptr) {
		s.push(current);
		current = current->left;
	}
	current = s.top();
	s.pop();
	const int key = current->key;
	current = current->right;
	return key;
}

bool AvlTree::SftIterator::has_next()
{
	return (s.size() || current != nullptr);
}

AvlTree::node* AvlTree::node::Delete()
{
	if (this == nullptr) return nullptr;
	this->left->Delete();
	this->right->Delete();
	free(this);
	return nullptr;
}

void AvlTree::Insert(int key)
{
	root = root->insert(key);
}

void AvlTree::Remove(int key)
{
	root = root->remove(key);
}

bool AvlTree::Contains(int key) const
{
	return root->contains(key);
}

void AvlTree::Print() const
{
	root->print("", true, true);
}

unsigned AvlTree::node::Height()
{
	return this ? this->height : 0;
}

int AvlTree::node::BalanceValue() const
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
	if (!this)
		return nullptr;
	if (key < this->key)
	{
		this->left = this->left->remove(key);
	}
	else if (key > this->key)
	{
		this->right = this->right->remove(key);
	}
	else
	{
		node* q = this->left;
		node* r = this->right;
		free(this);
		if (!r)return q;
		node* min = r->find_min();
		min->right = r->remove_min();
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

void AvlTree::node::print(string indent, bool last, bool right) const
{
	const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (this == nullptr) return;
	std::cout << indent.c_str() << "+- ";
	if (indent != "") {
		SetConsoleTextAttribute(hConsole, (right ? 10 : 12));
		std::cout << (right ? "R:" : "L:");
	}
	else {
		SetConsoleTextAttribute(hConsole, 11);
	}
	std::cout << this->key << std::endl;
	SetConsoleTextAttribute(hConsole, 15);
	indent += last ? "   " : "|  ";
	this->left->print(indent, this->right == nullptr, false);
	this->right->print(indent, true, true);
}