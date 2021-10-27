#pragma once

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
				v[j + 1] = v[j];
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
		// O(logN)
		pq.push(num);

	v.clear();

	// O(NlogN)
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
//[5][1][3][7][9][2][4][6][8]
int Partition(vector<int>& v, int left, int right)
{
	int pivot = v[left];
	int low = left + 1;
	int high = right;

	// O(N)
	// low�� high�� �����ɶ�����
	while (low <= high)
	{
		// pivot������ v[low]�� ū���� ã�� ������ 
		while (low <= right && pivot >= v[low])
			low++;
		// pivot�� ������ ��ȿ�� -> left + 1
		while (high >= left + 1 && pivot <= v[high])
			high--;

		if (low < high)
			swap(v[low], v[high]);
	}
	// pivot�� v[high]�� ����
	swap(v[left], v[high]);
	return high;
}
void QuickSort(vector<int>& v, int left, int right)
{
	if (left >= right)
		return;

	// pivot �� ���� �Ϸ�
	int pivot = Partition(v, left, right);
	// pivot�������� �� �� �ٽ� ����
	QuickSort(v, left, pivot - 1);
	QuickSort(v, pivot + 1, right);
}