#pragma once
template<typename T>
class Stack
{
public:
	Stack()
	{

	}
	~Stack()
	{
		delete[] _data;
		_data = nullptr;
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