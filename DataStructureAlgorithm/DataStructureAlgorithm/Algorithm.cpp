#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>

using namespace std;
#include "RedBlackTree.h"
#include <thread>

// �ؽ� ���̺�
// map : Red-Black Tree
// - �߰� Ž�� ���� O(logN)

// C# dictionary = C++ unordered_map

// Hash_map ( unordered_map)
// - �߰� Ž�� ���� O(1) ����;;
// �޸𸮸� ���ְ� �ӵ��� ���Ѵ�. �浹�� �Ͼ�� �ʴ´ٴ� �����Ͽ� ���� ������

// ����Ʈ ������
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

	// ���̺�
	// Ű�� �˸� �����͸� �ѹ��� �� �� �ִ�.
}
void TestHash()
{
	// �浹 ����
	// - ���� �����
	// 	   �浹 �� hash(key) + 1 ���� ��ĭ�� �о ����
	// - ���� �����
	//	   �������� �ϸ� �����Ͱ� ������ �����ϱ� +1 �� �ƴ϶� + 1^2 -> + 2^2..
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

// �׷���/Ʈ�� ����
// �ּҽ��д� Ʈ�� (Minimum Spanning Tree)

// ��ȣ ��Ÿ�� ����(Disjoint Set)
// -> ���Ͽ� ���ε� Union_Find

// Lineage Battleground (ȥ��!)
// ������ + �����̹�
// 1���� 1000��(��id 0~999)
// ����(1���� <-> 2����)
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

	// �� ����
	// users[1] <-> users[5]
	users[5].teamId = users[1].teamId;
	
	for (User& user : users)
	{
		// 
		if (user.teamId == 1)
			user.teamId = 2;
	}
}

// Ʈ�������� �̿��� ��ȣ ��Ÿ�� ������ ǥ��
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

// Ʈ���� �������� ���� ������ �ذ�
// Ʈ���� ��ĥ �� �׻� ���̰� ���� Ʈ���� ���̰� ���� Ʈ�� ������
// Union By Rank ��ũ�� ���� ��ġ�� ����ȭ 
// O(1)
class DisjointSet
{
public:
	DisjointSet(int n) : _parent(n), _rank(n, 1)
	{
		for (int i = 0; i < n; i++)
			_parent[i] = i;
	}
	// ��ξ���
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
		// rank[u] <= rank[v] �����

		_parent[u] = v;

		// [1]	     [3]         [3]
		// [2] +  [4][5]  ->  [4][5][1]
		// [6]       [0]         [0][2]
		//		                    [6]
		if (_rank[u] == _rank[v])
			_rank[v]++;
	}
private:
	vector<int> _parent;	// ������ ��ǥ(head)
	vector<int> _rank;		// Ʈ���� ����
};
struct Vertex
{
	
};
vector<Vertex> vertices;
vector<vector<int>> adjacent; // ���� ���

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

