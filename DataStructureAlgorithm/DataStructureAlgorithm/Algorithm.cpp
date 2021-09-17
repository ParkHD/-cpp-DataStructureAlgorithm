#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include "Vector.h"
#include "List.h"

using namespace std;

template<typename T>
class Stack
{
public:
	Stack()
	{

	}
	~Stack()
	{

	}

	void push(const T& value)
	{
		if (_size >= _capacity)
		{
			int newCapacity = static_cast<int>(_capacity * 1.5);

			if (newCapacity == _capacity)
				newCapacity++;

			reserve(newCapacity);
		}
		_data[_size] = value;
		_size++;
	}
	void pop()
	{
		if (_size <= 0)
			return;

		_size--;
	}
	T& top()
	{
		return _data[_size - 1];
	}
	bool empty() { return _size <= 0; }
	int size() { return _size; }

private:
	void reserve(int capacity)
	{
		if (capacity <= _capacity)
			return;

		_capacity = capacity;
		T* temp = new T[_capacity];

		for (int i = 0; i < _size; i++)
		{
			temp[i] = _data[i];
		}
		delete[] _data;

		_data = temp;
	}
public:
	T* _data = nullptr;
	int _size = 0;
	int _capacity = 0;
};

int main()
{
	Stack<int> s;

	s.push(1);
	s.push(2);
	s.push(3);


	while (s.empty() == false)
	{
		int data = s.top();
		s.pop();

		cout << data << endl;
	}
	int size = s.size();
}