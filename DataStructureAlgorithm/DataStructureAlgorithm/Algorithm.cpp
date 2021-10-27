#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>

using namespace std;
#include "RedBlackTree.h"
#include <thread>

// 해시 테이블
// map : Red-Black Tree
// - 추가 탐색 삭제 O(logN)

// C# dictionary = C++ unordered_map

// Hash_map ( unordered_map)
// - 추가 탐색 삭제 O(1) ㄷㄷ;;
// 메모리를 내주고 속도를 취한다. 충돌이 일어나지 않는다는 가정하에 ㅈㄴ 빠르당

// 아파트 우편함
// [201][202][203][204][205][]
// [101][102][103][104][105][]

// 1 ~ 1000 user(userID = 1 ~ 999)
void TestTable()
{
	struct User
	{
		int userId = 0;
		string username;
	};
	vector<User> users;
	users.resize(1000);

	users[777] = User{ 777, "Rookiss" };

	string name = users[777].username;
	cout << name << endl;

	// 테이블
	// 키를 알면 데이터를 한번에 알 수 있다.
}
void TestHash()
{
	// 충돌 문제
	// - 선형 조사법
	// 	   충돌 시 hash(key) + 1 접근 한칸씩 밀어서 접근
	// - 이차 조사법
	//	   선형으로 하면 데이터가 몰릴수 있으니까 +1 이 아니라 + 1^2 -> + 2^2..
}
void TestHashTableChaining()
{
	struct User
	{
		int userId = 0;
		string username;
	};
	vector<vector<User>> users;
	users.resize(1000);

	const int userId = 12345566;
	int key = (userId % 1000);

	users[key].push_back(User{ userId, "Rookiss" });
	
	vector<User>& bucket = users[key];
	for (User& user : bucket)
	{
		if (user.userId == userId)
		{
			string name = user.username;
			cout << name << endl;
		}
	}
}

// 그래프/트리 으용
// 최소스패닝 트리 (Minimum Spanning Tree)

// 상호 배타적 집합(Disjoint Set)
// -> 유니온 파인드 Union_Find

// Lineage Battleground (혼종!)
// 혈맹전 + 서바이벌
// 1인팀 1000명(팀id 0~999)
// 동맹(1번팀 <-> 2번팀)
void LineageBattleground()
{
	struct User
	{
		int teamId;

	};
	vector<User> users;
	for (int i = 0; i < 1000; i++)
	{
		users.push_back(User{ i });
	}

	// 팀 동맹
	// users[1] <-> users[5]
	users[5].teamId = users[1].teamId;
	
	for (User& user : users)
	{
		// 
		if (user.teamId == 1)
			user.teamId = 2;
	}
}

// 트리구조를 이용한 상호 배타적 집합의 표현
// [0][1][2][3][4]


//struct Node 
//{
//	Node* leader;
//};


class NaiveDisjointSet
{
public:
	NaiveDisjointSet(int n) : _parent(n)
	{
		for (int i = 0; i < n; i++)
			_parent[i] = i;
	}
	int Find(int u)
	{
		if (u == _parent[u])
			return u;
		return Find(_parent[u]);
	}
	void Merge(int u, int v)
	{
		u = Find(u);
		v = Find(v);

		if (u == v)
			return;

		_parent[u] = v;
	}
private:
	vector<int> _parent;
};

// 트리가 한쪽으로 기우는 문제를 해결
// 트리를 합칠 때 항상 높이가 낮은 트리를 높이가 높은 트리 밑으로
// Union By Rank 랭크에 의한 합치기 최적화 
// O(1)
class DisjointSet
{
public:
	DisjointSet(int n) : _parent(n), _rank(n, 1)
	{
		for (int i = 0; i < n; i++)
			_parent[i] = i;
	}
	// 경로압축
	int Find(int u)
	{
		if (u == _parent[u])
			return u;

		return _parent[u] = Find(_parent[u]);
	}
	// Union by rank
	void Merge(int u, int v)
	{
		u = Find(u);
		v = Find(v);

		if (u == v)
			return;

		if (_rank[u] > _rank[v])
			swap(u, v);
		// rank[u] <= rank[v] 보장됨

		_parent[u] = v;

		// [1]	     [3]         [3]
		// [2] +  [4][5]  ->  [4][5][1]
		// [6]       [0]         [0][2]
		//		                    [6]
		if (_rank[u] == _rank[v])
			_rank[v]++;
	}
private:
	vector<int> _parent;	// 집합의 대표(head)
	vector<int> _rank;		// 트리의 높이
};
struct Vertex
{
	
};
vector<Vertex> vertices;
vector<vector<int>> adjacent; // 인접 행렬

void CreateGraph()
{
	vertices.resize(6);
	adjacent = vector<vector<int>>(6, vector<int>(6, -1));

	adjacent[0][1] = adjacent[1][0] = 15;
	adjacent[0][3] = adjacent[3][0] = 35;
	adjacent[1][2] = adjacent[2][1] = 5;
	adjacent[1][3] = adjacent[3][1] = 10;
	adjacent[3][4] = adjacent[4][3] = 5;
	adjacent[3][5] = adjacent[5][3] = 10;
	adjacent[5][4] = adjacent[4][5] = 5;
}
struct CostEdge
{
	int cost;
	int u;
	int v;

	bool operator<(CostEdge& other)
	{
		return cost < other.cost;
	}
};
int Kruskal(vector<CostEdge>& selected)
{
	int ret = 0;

	selected.clear();

	vector<CostEdge> edges;

	for (int u = 0; u < adjacent.size(); u++)
	{
		for (int v = 0; v < adjacent[u].size(); v++)
		{
			if (u > v)
				continue;

			int cost = adjacent[u][v];
			if (cost == -1)
				continue;

			edges.push_back(CostEdge{ cost, u, v });
		}
	}

	std::sort(edges.begin(), edges.end());

	DisjointSet sets(vertices.size());

	for (CostEdge& edge : edges)
	{
		if (sets.Find(edge.u) == sets.Find(edge.v))
			continue;

		sets.Merge(edge.u, edge.v);
		selected.push_back(edge);
		ret += edge.cost;
	}

	return ret;
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

	CreateGraph();

	vector<CostEdge> selected;
	int cost = Kruskal(selected);


}

