#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>

using namespace std;
#include "RedBlackTree.h"
#include <thread>
#include <Windows.h>

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

	// ��ȿ�� ������ edges�� �ֱ�
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
// �޸������̼�(memoization)
int cache[50][50];

int combination(int n, int r)
{
	// �������
	if (r == 0 || n == r)
		return 1;
	// �̹� ���� ������ ������ �ٷ� ��ȯ
	int& ret = cache[n][r];
	if (ret != -1)
		return ret;
	// ���� ���� ���ؼ� ĳ�ÿ� ����

	return ret = combination(n - 1, r - 1) + combination(n - 1, r);
}
// LIS(Longest Increasing Sequence)
// Seq : 1, 9, 2, 5, 7
// �κм��� : �Ϻμ��ڸ� ����� ���� ����
// ex) 1,2,5 
// ex) 1,9,5,7
// �� ���� �κм���
// ex) 1 2 5

// LIS : ���� �� �� ���� �κ� ������ ���� 
// 1 2 5 7 = ���� 4
int cache_LIS[100];
vector<int> seq;
int LIS(int pos)
{
	// ��������
	
	// ĳ��Ȯ��
	int& ret = cache_LIS[pos];
	if (ret != -1)
		return ret;
	// ���ϱ�
	// Seq : 1 9 2 5 7
	ret = 1; // �ּ� 1

	for (int i = pos + 1; i < seq.size(); i++)
	{
		if (seq[pos] < seq[i])
		{
			ret = max(ret, 1 + LIS(i));
		}
	}

	return ret;
}
int N;
vector<vector<int>> board;
vector<vector<int>> cache_path;
vector<vector<int>> nextX;
int path(int y, int x)
{
	// ��������
	if (y == N)
		return 0;
	// ĳ�� Ȯ��
	int& ret = cache_path[y][x];
	if (ret != -1)
		return ret;
	// ����
	// ���Ȯ��
	{
		int nextBottom = path(y + 1, x);
		int nextBottomRight = path(y + 1, x + 1);

		if (nextBottom > nextBottomRight)
			nextX[y][x] = x;
		else
			nextX[y][x] = x + 1;
	}
	return ret = board[y][x] + max(path(y + 1, x), path(y + 1, x + 1));
}


int HashKey(const vector<vector<char>>& board)
{
	int ret = 0;
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			ret = ret * 3;

			if (board[y][x] == 'o')
				ret += 1;
			else if (board[y][x] == 'x')
				ret += 2;
		}
	}
	return ret;
}
vector<vector<char>> Tboard;
int Tcache[19683];
enum
{
	DEFAULT = 2,
	WIN = 1,
	DRAW = 0,
	LOSE = -1,
};
bool IsFinished(const vector<vector<char>>& board, char turn)
{
	// �¿�
	for (int i = 0; i < 3; i++)
	{
		if (Tboard[i][0] == turn && board[i][1] == turn && board[i][2] == turn)
			return true;
	}
	// ����
	for (int i = 0; i < 3; i++)
	{
		if (Tboard[0][i] == turn && board[1][i] == turn && board[2][i] == turn)
			return true;
	}
	// �밢��
	if (Tboard[0][0] == turn && board[1][1] == turn && board[2][2] == turn)
		return true;
	if (Tboard[0][2] == turn && board[1][1] == turn && board[2][0] == turn)
		return true;

	return false;
}
int CanWin(vector<vector<char>>& board, char turn)
{
	// ��������
	if (IsFinished(board, 'o' + 'x' - turn))
	{
		return LOSE;
	}
	// ĳ�� Ȯ��
	int key = HashKey(board);
	int& ret = Tcache[key];
	if (ret != DEFAULT)
		return ret;
	
	// Ǯ��
	int minValue = DEFAULT;
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			// �̹� ������ ���� �Ǿ� �ִ�
			if (board[y][x] != '.')
				continue;

			// ����
			board[y][x] = turn;

			// Ȯ��
			minValue = min(minValue, CanWin(board, 'o' + 'x' - turn));

			// ���
			board[y][x] = '.';
		}
	}
	if (minValue == DRAW || minValue == DEFAULT)
		return ret = DRAW;

	return ret = -minValue;
}
int EnchantN;
int cache_ENCHANT[100];
int Enchant(int num)
{
	if (num > EnchantN)
		return 0;
	if (num == EnchantN)
		return 1;

	int& ret = cache_ENCHANT[num];
	if (ret != -1)
		return ret;
	
	return ret = Enchant(num + 1) + Enchant(num + 2) + Enchant(num + 3);
}

struct Shoe
{
	Shoe(int a, int b, int c, int d)
	{
		time = a;
		start = a + b;
		end = a + b + c;
		speed = d;
	}
	int time;	// a �Ź� �����ð�
	int start;	// a + b  �Ź� ȿ�� ���� �ð�
	int end;	// a + b + c �Ź� ȿ�� ������ �ð�
	int speed;	// d �Ź� �ӵ�
};

int T;
vector<Shoe> shoes;
vector<int> cache_RIDER;
int Solve()
{

}
int main()
{
	// �� �̵� �ð�
	T = 20;

	// �ð� ���� �����Ǵ� �Ź� ���
	shoes.push_back(Shoe(3, 4, 10, 3));
	shoes.push_back(Shoe(4, 1, 4, 2));
	shoes.push_back(Shoe(10, 2, 5, 5));
	shoes.push_back(Shoe(15, 1, 3, 7));
	std::sort(shoes.begin(), shoes.end(), [=](Shoe& left, Shoe& right) {return left.time < right.time; });
}

