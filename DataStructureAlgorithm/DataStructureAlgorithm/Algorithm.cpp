#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>

using namespace std;
#include "RedBlackTree.h"
#include <thread>

// �ð����⵵ n^2
void BubbleSort(vector<int>& v)
{
	const int n = (int)v.size();

	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < (n - 1 - i); j++)
		{
			if (v[j] > v[j + 1])
			{
				int temp = v[j];
				v[j] = v[j + 1];
				v[j + 1] = temp;
			}
		}
	}
}
// ���� ����
void SelectionSort(vector<int>& v)
{
	const int n = (int)v.size();

	for (int i = 0; i < n - 1; i++)
	{
		int bestIdx = i;
		for (int j = i + 1; j < n - 1; j++)
		{
			if (v[j] < v[bestIdx])
				bestIdx = j;
		}

		int temp = v[i];
		v[i] = v[bestIdx];
		v[bestIdx] = temp;
	}
}

// !!�������� �߿�!!
void InsertionSort(vector<int>& v)
{
	const int n = (int)v.size();

	for (int i = 1; i < n; i++)
	{
		int insertData = v[i];
		for (int j = i - 1; j >= 0; j--)
		{
			if (v[j] > insertData)
			{
				v[j+1] = v[j];
			}
			else
			{
				v[j + 1] = insertData;
				break;
			}

		}
	}
}

// �� ����
void HeapSort(vector<int>& v)
{
	priority_queue<int, vector<int>, greater<int>> pq;

	// O(NlogN)
	for (int num : v)
		pq.push(num);

	v.clear();

	// O(NlogN)0
	while (pq.empty() == false)
	{
		v.push_back(pq.top());
		pq.pop();
	}
}
// ���� ����
// ���� ����(Divide and Conquer)
// - ����(Divide)	������ �� �ܼ��ϰ� ����
// - ����(Conquer)	���ҵ� ������ �ذ�
// - ����(Combine)	����� �����Ͽ� ������

// [3][k][7][2][j][4][8][9]
// [3][k][7][2]   [j][4][8][9]
// [2][3][7][k]   [4][8][9][j]
// [2][3][7][k]   [4][8][9][j]

void MergeResult(vector<int>& v, int left, int mid, int right)
{
	int leftIdx = left;
	int rightIdx = mid + 1;

	vector<int> temp;
	
	while (leftIdx <= mid && rightIdx <= right)
	{
		if (v[leftIdx] <= v[rightIdx])
		{
			temp.push_back(v[leftIdx]);
			leftIdx++;
		}
		else
		{
			temp.push_back(v[rightIdx]);
			rightIdx++;
		}
	}
	// ������ ���� ��������, ������ ������ �����ͺ���
	if (leftIdx > mid)
	{
		while (rightIdx <= right)
		{
			temp.push_back(v[rightIdx]);
			rightIdx++;
		}
	}
	else
	{
		while (leftIdx <= mid)
		{
			temp.push_back(v[leftIdx]);
			leftIdx++;
		}
	}
	for (int i = 0; i < temp.size(); i++)
	{
		v[left + i] = temp[i];
	}
}
void MergeSort(vector<int>& v, int left, int right)
{
	if (left >= right)
		return;

	int mid = (left + right) / 2;
	MergeSort(v, left, mid);
	MergeSort(v, mid + 1, right);

	MergeResult(v, left, mid, right);
}

int main()
{
#pragma region  redblacktree
	//RedBlackTree bst;
	//bst.Insert(30);
	//bst.Print();
	//this_thread::sleep_for(1s);

	//bst.Insert(10);
	//bst.Print();
	//this_thread::sleep_for(1s);

	//bst.Insert(20);
	//bst.Print();
	//this_thread::sleep_for(1s);

	//bst.Insert(25);
	//bst.Print();
	//this_thread::sleep_for(1s);

	//bst.Delete(20);
	//bst.Print();
	//this_thread::sleep_for(1s);

	//bst.Delete(10);
	//bst.Print();
	//this_thread::sleep_for(1s);
#pragma endregion
	vector<int> v;

	srand(time(0));

	for (int i = 0; i < 50; i++)
	{
		int randValue = rand() % 100;
		v.push_back(randValue);
	}
	
	//InsertionSort(v);

	MergeSort(v, 0, v.size() - 1);
	int x;
}

