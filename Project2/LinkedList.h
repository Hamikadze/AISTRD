#pragma once
#include <stdexcept>

class LinkedList
{
private:
	void add_first(int newElem);
	void reset_list();
	class Node
	{
	public:
		Node(int data, Node * next = nullptr, Node * prev = nullptr) {
			this->data = data;
			this->next = next;
			this->prev = prev;
		};
		~Node() {};
		int data;
		Node * next;
		Node * prev;
	};
	Node * head;
	Node * tail;
	size_t size;
public:
	LinkedList();
	~LinkedList();
	void push_back(int newElem);
	void push_front(int newElem);
	void pop_back(); // удаление последнего элемента
	void pop_front(); // удаление первого элемента
	void insert(size_t index, int newElem); // добавление элемента по индексу
	int at(size_t index) const;
	void remove(size_t index); // удаление элемента по индексу
	size_t get_size() const;
	void print_to_console() const; // вывод элементов списка в консоль через разделитель, не использовать at
	void clear(); // удаление всех элементов списка
	void set(size_t index, int newElem) const; // замена элемента по индексу на передаваемый элемент
	bool isEmpty() const; // проверка на пустоту списка
	bool contains(LinkedList* list) const; // проверка на содержание другого списка в списке
};
