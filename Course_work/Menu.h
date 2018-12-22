#pragma once
#include <string>
#include <iostream>
#include "CommitsRaid.h"

template<typename T>
struct TypeHelper
{
	typedef void(*IntFunctionWithOneParameter) (T a);
};

template<typename T>
class Item
{
public:
	Item(const char* label, typename TypeHelper<T>::IntFunctionWithOneParameter function, T parameter)
	{
		this->label = label;
		this->function = function;
		this->parameter = parameter;
	}
	const char* label;
	typename TypeHelper<T>::IntFunctionWithOneParameter function;
	T parameter;
};

template<typename T>
class Menu
{
private:
	std::string header;
public:
	Menu(std::string header);
	void Show(Item<T> item[]);
	~Menu();
};
