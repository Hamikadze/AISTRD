#pragma once
template <class T>
class Iterator
{
public:
	virtual std::pair<int, T> next() = 0;
	virtual bool has_next() = 0;
};
