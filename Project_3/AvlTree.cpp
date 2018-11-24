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
	return new DftIterator(this->root);
}

Iterator*AvlTree::create_bft_iterator() const
{
	return new BftIterator(this->root);
}

Iterator* AvlTree::create_sft_iterator() const
{
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

void AvlTree::node::Delete()
{
	if (this == nullptr) return;
	this->left->Delete();
	this->right->Delete();
	free(this);
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
	return root->contains(0);
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
	if (!this) return nullptr;
	if (key < this->key)//если искомое значение меньше ключа
	{
		this->left = this->left->remove(key);//рекурсивный перебор левого дерева
	}
	else if (key > this->key)//если искомое значение больше ключа
	{
		this->right = this->right->remove(key);//рекурсивный перебор правого дерева
	}
	else // if(k == p->key) значение для удаления найдено, оно в текущем узле
	{
		node* q = this->left; //сохраняем для объединения левую и правую ветви
		node* r = this->right;
		free(this); //удаляем узел
		if (!r)return q; //если ветви справа не существует, то возвращаем левую ветвь ВСЁ, ЧТО МЫ ВОЗВРАЩАЕМ МЫ ВЕРХНИХ БЛОКАХ IF ELSE ПРИСВАЕМАЕМ К ПРАВОЙ ИЛИ ЛЕВОЙ ВЕТВИ
		node* min = r->find_min(); //находим минимальное значение в левой ветви, посути это вообще самое минимальное значение в дереве
		min->right = r->remove_min(); //посути мы выпрямляем веточку, чтобы потом было проще её сбалансировать
		min->left = q; //присваиваем левую ветвь на левую ветвь минимального значения
		return min->balance(); //выполняем балансировку ветки, которую мы сейчас склеивали
	}
	return this->balance();//выполняем балансировку всего дерева
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
	// you can loop k higher to see more color choices
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