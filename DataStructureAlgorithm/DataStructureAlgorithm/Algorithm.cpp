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
		// 제일 좋은 후보를 찾는다
		list<VertexCost>::iterator bestIt;
		int bestCost = INT32_MAX;

		for (auto it = discovered.begin(); it != discovered.end(); it++)
		{
			const int cost = it->cost;

			if (cost < bestCost )
			{
				bestCost = cost;
				bestIt = it;
			}
		}
		int cost = bestIt->cost;
		here = bestIt->vertex;
		discovered.erase(bestIt);

		if (best[here] < cost)
			continue;


		for (int there = 0; there < 6; there++)
		{
			// 연결되지 않았으면 스킵.
			if (adjacent[here][there] == -1)
				continue;
			int nextCost = best[here] + adjacent[here][there];
			if (nextCost >= best[there])
				continue;

			discovered.push_back(VertexCost{ there, nextCost });
			best[there] = nextCost;
			parent[there] = here;
		}
	}
}

int main()
{
	CreateGraph();
	Dijikstra(0);
}