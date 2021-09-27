#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>

using namespace std;

// 힙트리
// 부모노드가 가진 값은 자식 노드보다 크다
// 마지막 레벨을 제외한 모든 레벨에 노드가 꽉차있다
// 마지막 레벨에 노드가 있을 때는 항상 왼쪽부터 순서대로 채운다

template<typename T, typename Container = vector<T>, typename Predicate = less<T>>
class PriorityQueue
{
public:
	void push(const T& data)
	{
		_heap.push_back(data);

		int now = static_cast<int>(_heap.size()) - 1;

		while (now > 0)
		{
			// 부모노드와 데이터와 비교
			int next = (now - 1) / 2; // 부모노드의 인덱스
			/*if (_heap[now] < _heap[next])
				break;*/
			if (_predicate(_heap[now], _heap[next]))
				break;
			::swap(_heap[now], _heap[next]);
			now = next;
		}
	}
	void pop()
	{
		_heap[0] = _heap.back();
		_heap.pop_back();

		int now = 0;
		while (true)
		{
			int left = 2 * now + 1;	// 왼쪽 자식 인덱스
			int right = 2 * now + 2;

			// 리프에 도달한 경우
			if (left >= _heap.size())
				break;

			int next = now;
			if (_predicate(_heap[next], _heap[left]))
				next = left;

			if (right < (int)_heap.size() && _predicate(_heap[next], _heap[right]))
				next = right;

			if (next == now)
				break;

			::swap(_heap[now], _heap[next]);
			now = next;
		}
	}
	T& top()
	{
		return _heap[0];
	}
	bool empty()
	{
		return _heap.empty();
	}
private:
	Container _heap = {};
	Predicate _predicate = {};
};