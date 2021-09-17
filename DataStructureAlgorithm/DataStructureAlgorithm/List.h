#pragma once
template<typename T>
class Node
{
public:
	Node() : _prev(nullptr), _next(nullptr), _data(T())
	{

	}
	Node(const T& value) : _prev(nullptr), _next(nullptr), _data(value)
	{

	}
public:
	Node* _prev;
	Node* _next;
	T		_data;
};
template<typename T>
class Iterator
{
public:
	Iterator() : _node(nullptr)
	{

	}
	Iterator(Node<T>* node) : _node(node)
	{

	}
	// ++it
	Iterator& operator++()
	{
		_node = _node->_next;
		return *this;
	}
	// it++
	Iterator& operator++(int)
	{
		Iterator<T> temp = *this;
		_node = _node->_next;
		return temp;
	}
	// --it
	Iterator& operator--()
	{
		_node = _node->_prev;
		return *this;
	}
	// it--
	Iterator& operator--(int)
	{
		Iterator<T> temp = *this;
		_node = _node->_prev;
		return temp;
	}
	T& operator*()
	{
		return _node->_data;
	}
	bool operator == (const Iterator& other)
	{
		return _node == other._node;
	}
	bool operator != (const Iterator& other)
	{
		return _node != other._node;
	}
public:
	Node<T>* _node;
};
template<typename T>
class List
{
public:
	List() : _size(0)
	{
		_head = new Node<T>();
		_tail = new Node<T>();
		_head->_next = _tail;
		_tail->_prev = _head;
	}
	~List()
	{
		while (_size > 0)
			pop_back();
		delete _head;
		delete _tail;
	}
	void push_back(const T& value)
	{
		AddNode(_tail, value);
	}
	void pop_back()
	{
		RemoveNode(_tail->_prev);
	}
private:
	// [head] <-> ... <-> [prevNode] <-> [before] <-> [tail]
	// [head] <-> ... <-> [prevNode] <-> [newNode] <-> [before] <-> [tail]
	Node<T>* AddNode(Node<T>* before, const T& value)
	{
		Node<T>* newNode = new Node<T>(value);
		Node<T>* prevNode = before->_prev;

		prevNode->_next = newNode;
		newNode->_prev = prevNode;

		newNode->_next = before;
		before->_prev = newNode;

		_size++;

		return newNode;
	}

	// [head] <-> ... <-> [prevNode] <-> [node] <-> [nextNode] <-> [tail]
	// [head] <-> ... <-> [prevNode] <-> [nextNode] <-> [tail]
	Node<T>* RemoveNode(Node<T>* node)
	{
		Node<T>* prevNode = node->_prev;
		Node<T>* nextNode = node->_next;

		prevNode->_next = nextNode;
		nextNode->_prev = prevNode;

		delete node;

		_size--;

		return nextNode;
	}
	int size() { return _size; }
public:
	using iterator = Iterator<T>;

	iterator begin() { return iterator(_head->_next); }
	iterator end() { return iterator(_tail); }

	iterator insert(iterator it, const T& value)
	{
		Node<T>* node = AddNode(it._node, value);
		return iterator(node);
	}
	iterator erase(iterator it)
	{
		Node<T>* node = RemoveNode(it._node);
		return iterator(node);
	}
public:
	Node<T>* _head;
	Node<T>* _tail;
	int		_size;
};