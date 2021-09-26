#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>	

using namespace std;

struct Vertex
{
	// int data;
};

vector<Vertex> vertices;
vector<vector<int>> adjacent;  // 인접행렬

void CreateGraph()
{
	vertices.resize(6);
	adjacent = vector<vector<int>>(6, vector<int>(6, -1));

	adjacent[0][1] = 15;
	adjacent[0][3] = 35;

	adjacent[1][0] = 15;
	adjacent[1][2] = 5;
	adjacent[1][3] = 10;

	adjacent[3][4] = 5;
	adjacent[5][4] = 5;
}
void Dijikstra(int here)
{
	struct VertexCost
	{
		int vertex;
		int cost;
	};

	list<VertexCost> discovered;
	vector<int> best(6, INT32_MAX); // 각 정점별로 지금까지 발견한 최소 거리
	vector<int> parent(6, -1);

	discovered.push_back(VertexCost{ here, 0 });
	best[here] = 0;
	parent[here] = here;

	while (discovered.empty() == false)
	{
		// 제일 좋은 후보(다음 경로인 vertex)를 찾는다
		// 후보를 찾는 for문으로 인해 느리다
		// 경로 cost가 작은 곳을 먼저 간다
		list<VertexCost>::iterator bestIt;
		int bestCost = INT32_MAX;

		for (auto it = discovered.begin(); it != discovered.end(); it++)
		{
			const int cost = it->cost;

			if (cost < bestCost)
			{
				bestCost = cost;
				bestIt = it;
			}
		}

		// 찾은 후보로 다음 경로를 계산한다
		int cost = bestIt->cost;
		here = bestIt->vertex;
		discovered.erase(bestIt);

		// 이미 찾은 경로의 cost가 더 작으면 스킵
		// 이미 discovered에 들어가있을 수 있다.
		if (best[here] < cost)
			continue;


		for (int there = 0; there < 6; there++)
		{
			// 연결되지 않았으면 스킵.
			if (adjacent[here][there] == -1)
				continue;
			// 더 좋은 경로를 과거에 찾았으면 스킵  
			int nextCost = best[here] + adjacent[here][there];
			if (nextCost >= best[there])
				continue;

			discovered.push_back(VertexCost{ there, nextCost });
			best[there] = nextCost;
			parent[there] = here;
		}
	}
}
// 어떤목적지를 대상으로 하는것은 아니고 시작점을 기준으로 가장 가까이있는 곳 순서대로 각 모든곳에 최소거리 계산