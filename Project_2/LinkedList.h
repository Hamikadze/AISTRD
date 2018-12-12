#pragma once
#include <stdexcept>
#include "../Project_3/Iterator.h"

template <typename  T>
class LinkedList {
	class Node
	{
	public:
		Node(T data, Node * next = nullptr, Node * prev = nullptr) {
			this->data = data;
			this->next = next;
			this->prev = prev;
		};
		~Node()
		{
			next = nullptr;
			delete next;
			prev = nullptr;
			delete prev;
			data = {};
		};
		T data;
		Node* next;
		Node* prev;
	};
public:
	void add_first(T newElem);
	void reset_list();
	Node * head{};
	Node * tail{};
	size_t size;
	LinkedList();
	~LinkedList();
	class ListIterator : public Iterator<T>
	{
	public:
		ListIterator(Node* head)
		{
			current = head;
		};

		T next() override;
		bool has_next() override;

	private:
		//LinkedList<Node*> list;
		Node* current;
	};
	void push_back(T newElem);
	void push_front(T newElem);
	void pop_back(); // удаление последнего элемента
	void pop_front(); // удаление первого элемента
	void insert(size_t index, T newElem); // добавление элемента по индексу
	T at(size_t index) const;
	void remove(size_t index); // удаление элемента по индексу
	size_t get_size() const;
	void print_to_console() const; // вывод элементов списка в консоль через разделитель, не использовать at
	void clear(); // удаление всех элементов списка
	void set(size_t index, T newElem) const; // замена элемента по индексу на передаваемый элемент
	bool isEmpty() const; // проверка на пустоту списка
	bool contains(LinkedList* list) const; // проверка на содержание другого списка в списке
	bool contains(T data) const;
	bool equals(LinkedList* list) const;

	Iterator<T>* create_list_iterator() const;
};

//#include "LinkedList.cpp"