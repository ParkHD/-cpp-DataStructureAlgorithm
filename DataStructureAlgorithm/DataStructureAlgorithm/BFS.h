#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include "Vector.h"
#include "List.h"
#include "Stack.h"
#include "Queue.h"

using namespace std;

struct Vertex
{
	//int data;
};
vector<Vertex> vertices;
vector<vector<int>> adjacent;

vector<bool> discovered;

void CreateGraph()
{
	vertices.resize(6);
	adjacent = vector<vector<int>>(6);

	//// ��������Ʈ
	//adjacent[0].push_back(1);
	//adjacent[0].push_back(3);
	//adjacent[1].push_back(0);
	//adjacent[1].push_back(2);
	//adjacent[1].push_back(3);
	//adjacent[3].push_back(4);
	//adjacent[5].push_back(4);

	// �������
	adjacent = vector<vector<int>>
	{
		{ 0, 1, 0, 1, 0, 0},
		{ 1, 0, 1, 1, 0, 0},
		{ 0, 0, 0, 0, 0, 0},
		{ 0, 0, 0, 0, 1, 0},
		{ 0, 0, 0, 0, 0, 0},
		{ 0, 0, 0, 0, 1, 0},
	};
}
void Bfs(int here)
{
	// ������ ���� �߰ߵǾ����� ?
	vector<int> parent(6, -1);
	// ���������� ��ŭ ������ �ִ���?
	vector<int> distance(6, -1);

	// ó�� ������������ �ʱ�ȭ
	queue<int> q;
	q.push(here);
	discovered[here] = true;

	parent[here] = here;
	distance[here] = 0;

	while (q.empty() == false)
	{
		here = q.front();
		q.pop();

		cout << "Visited : " << here << endl;

		////��������Ʈ
		//for (int there : adjacent[here])
		//{
		//	if (discovered[there])
		//		continue;
		//	q.push(there);
		//	discovered[there] = true;
		//	parent[there] = here;	// ��θ� ������ �����μ� �׷����� �׸��� �ִ�
		//	distance[there] = distance[here] + 1;
		//}

		// �������
		for (int there = 0; there < 6; there++)
		{
			if (adjacent[here][there] == 0)
				continue;
			if (discovered[there])
				continue;

			q.push(there);
			discovered[there] = true;

			parent[there] = here;	// ��θ� ������ �����μ� �׷����� �׸��� �ִ�
			distance[there] = distance[here] + 1;
		}
	}

}
void BfsAll()
{
	for (int i = 0; i < 6; i++)
	{
		if (discovered[i] == false)
			Bfs(i);
	}
}