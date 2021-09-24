#pragma once
#include<iostream>
// [front/back][][][][][][]
// ...
// [front][][back][][][][]
// [][][][][front][][back]
// [][back][][][front][][]

template<typename T>
class ArrayQueue
{
public:
	ArrayQueue()
	{
		
	}
	void push(const T& value)
	{
		if (_size == _container.size())
		{
			int newSize = max(1, _size * 2);
			vector<T> newData;
			newData.resize(newSize);
			for (int i = 0; i < _size; i++)
			{
				int index = (_front + i) % _container.size();
				newData[i] = _container[index];
			}
			_container.swap(newData);
			_front = 0;
			_back = _size;
		}
		_container[_back] = value;
		_back = (_back + 1) % _container.size();
		_size++;
	}
	void pop()
	{
		if (_size <= 0)
			return;
		_front = (_front + 1);
		_size--;
	}
	T& front()
	{
		return _container[_front];
	}
	bool empty()
	{
		return _size == 0;
	}
	int size() { return _size; }
private:
	vector<T> _container;

	int _front = 0;
	int _back = 0;
	int _size = 0;
};

const int MAX_SIZE = 100;
template<typename T>
class ArrayQueue1
{
public:
	ArrayQueue1()
	{
		_data = new T[MAX_SIZE];
	}

public:
	void push(const T& value)
	{
		if (_size == MAX_SIZE)
		{
			cout << "isfull" << endl;
			return;
		}

		_data[_back] = value;
		_back = (_back + 1) % MAX_SIZE;
		_size++;
	}
	void pop()
	{
		_size--;
		_front = (_front + 1) % MAX_SIZE;
	}
	T& front()
	{
		return _data[_front];
	}
	int size()
	{
		return _size;
	}
	bool empty()
	{
		return _size == 0;
	}

public:
	int _front = 0;
	int _back = 0;
	int _size = 0;

	T* _data;
};