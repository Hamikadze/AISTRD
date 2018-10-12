#include "pch.h"
#include "LinkedList.h"
#include <stdexcept>
#include <iostream>

void LinkedList::reset_list()
{
	head = nullptr;
	tail = nullptr;
}

LinkedList::LinkedList()
{
	reset_list();
	size = 0;
}

LinkedList::~LinkedList()
{
}

void LinkedList::add_first(int newElem)
{
	head = new Node(newElem);
	tail = head;
}

size_t LinkedList::get_size() const
{
	return size;
}

void LinkedList::print_to_console() const
{
	if (size == 0)
		return;
	Node * current = head;
	while (current->next != tail) {
		std::cout << "[" << current->data << "] <- ";
		current = current->next;
	}
	std::cout << "[nullptr]";
}

void LinkedList::clear()
{
	if (size == 0) return;

	if (size == 1) {
		delete head;
		delete tail;
		reset_list();
	}
	else {
		Node * current = head;
		while (head != nullptr) {
			pop_front();
		}
		delete head;
		delete tail;
		reset_list();
	}
}

void LinkedList::set(size_t index, int newElem) const
{
	if (index >= size) {
		throw std::out_of_range("Index is greater than list size");
	}
	else {
		size_t counter = 0;
		Node * current = head;
		while (counter != index) {
			current = current->next;
			counter++;
		}
		current->data = newElem;
	}
}

bool LinkedList::isEmpty() const
{
	return size == 0;
}

bool LinkedList::contains(LinkedList* list) const
{
	Node * current = head;
	Node * current_find = list->head;
	bool contains = false;
	do {
		if (current->data == current_find->data)
		{
			current_find = current_find->next;
			if (current_find == nullptr)
			{
				contains = true;
				break;
			}
			current = current->next;
		}
		else
		{
			contains = false;
			current_find = list->head;
			current = current->next;
		}
	} while (current != nullptr);
	return contains;
}

void LinkedList::push_back(int newElem)
{
	if (size == 0) {
		add_first(newElem);
	}
	else {
		tail->next = new Node(newElem, nullptr, tail);
		tail = tail->next;
	}
	size++;
}

void LinkedList::push_front(int newElem)
{
	if (size == 0) {
		add_first(newElem);
	}
	else {
		head = new Node(newElem, head, nullptr);
	}
	size++;
}

void LinkedList::pop_back()
{
	if (size == 0) return;

	if (size == 1) {
		delete head;
		delete tail;
		reset_list();
	}
	else {
		Node * current = tail->prev;
		current->next = nullptr;
		delete tail;
		tail = current;
	}
	size--;
}

void LinkedList::pop_front()
{
	if (size == 0) return;

	if (size == 1) {
		delete head;
		delete tail;
		reset_list();
	}
	else {
		Node * current = head->next;
		delete head;
		head = current;
	}
	size--;
}

void LinkedList::insert(size_t index, int newElem)
{
	if (index >= size) {
		throw std::out_of_range("Index is greater than list size");
	}
	else {
		if (size == 0)
		{
			add_first(newElem);
			return;
		}
		if (index == 0)
		{
			push_front(newElem);
		}
		if (index == size - 1)
		{
			push_back(newElem);
			return;
		}
		size_t counter = 0;
		Node * current = head;
		Node * prev = nullptr;
		while (counter != index) {
			prev = current;
			current = current->next;
			counter++;
		}
		current = new Node(newElem, current);
		if (prev != nullptr) {
			prev->next = current;
		}
		else
		{
			head = current;
		}
	}
}

int LinkedList::at(size_t index) const
{
	if (index >= size) {
		throw std::out_of_range("Index is greater than list size");
	}
	else {
		size_t counter = 0;
		Node * current = head;
		while (counter != index) {
			current = current->next;
			counter++;
		}
		return current->data;
	}
}

void LinkedList::remove(size_t index)
{
	//TODO: Write for 2waylist
	if (index >= size) {
		throw std::out_of_range("Index is greater than list size");
	}
	else {
		if (size == 0)
		{
			return;
		}
		if (index == 0)
		{
			pop_front();
			return;
		}
		if (index == size - 1)
		{
			pop_back();
			return;
		}
		size_t counter = 0;
		Node * current = head;
		while (counter != index) {
			current = current->next;
			counter++;
		}
		if (current->prev != nullptr) {
			current = current->next;
		}
		else
		{
			head = current;
		}
	}
}