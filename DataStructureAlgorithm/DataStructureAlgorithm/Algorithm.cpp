#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>

using namespace std;
#include "RedBlackTree.h"
#include <thread>
#include <Windows.h>

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

	// 유효한 간선만 edges에 넣기
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
// 메모이제이션(memoization)
int cache[50][50];

int combination(int n, int r)
{
	// 기저사례
	if (r == 0 || n == r)
		return 1;
	// 이미 답을 구한적 있으면 바로 반환
	int& ret = cache[n][r];
	if (ret != -1)
		return ret;
	// 새로 답을 구해서 캐시에 저장

	return ret = combination(n - 1, r - 1) + combination(n - 1, r);
}
// LIS(Longest Increasing Sequence)
// Seq : 1, 9, 2, 5, 7
// 부분수열 : 일부숫자를 지우고 남은 수열
// ex) 1,2,5 
// ex) 1,9,5,7
// 순 증가 부분수열
// ex) 1 2 5

// LIS : 제일 긴 순 증가 부분 수열의 길이 
// 1 2 5 7 = 길이 4
int cache_LIS[100];
vector<int> seq;
int LIS(int pos)
{
	// 기저사항
	
	// 캐시확인
	int& ret = cache_LIS[pos];
	if (ret != -1)
		return ret;
	// 구하기
	// Seq : 1 9 2 5 7
	ret = 1; // 최소 1

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
	// 기저사항
	if (y == N)
		return 0;
	// 캐시 확인
	int& ret = cache_path[y][x];
	if (ret != -1)
		return ret;
	// 적용
	// 경로확인
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
	// 좌우
	for (int i = 0; i < 3; i++)
	{
		if (Tboard[i][0] == turn && board[i][1] == turn && board[i][2] == turn)
			return true;
	}
	// 상하
	for (int i = 0; i < 3; i++)
	{
		if (Tboard[0][i] == turn && board[1][i] == turn && board[2][i] == turn)
			return true;
	}
	// 대각선
	if (Tboard[0][0] == turn && board[1][1] == turn && board[2][2] == turn)
		return true;
	if (Tboard[0][2] == turn && board[1][1] == turn && board[2][0] == turn)
		return true;

	return false;
}
int CanWin(vector<vector<char>>& board, char turn)
{
	// 기저사항
	if (IsFinished(board, 'o' + 'x' - turn))
	{
		return LOSE;
	}
	// 캐시 확인
	int key = HashKey(board);
	int& ret = Tcache[key];
	if (ret != DEFAULT)
		return ret;
	
	// 풀기
	int minValue = DEFAULT;
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			// 이미 공간에 착수 되어 있다
			if (board[y][x] != '.')
				continue;

			// 착수
			board[y][x] = turn;

			// 확인
			minValue = min(minValue, CanWin(board, 'o' + 'x' - turn));

			// 취소
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
	int time;	// a 신발 스폰시간
	int start;	// a + b  신발 효과 시작 시간
	int end;	// a + b + c 신발 효과 끝나는 시간
	int speed;	// d 신발 속도
};

int T;
vector<Shoe> shoes;
vector<int> cache_RIDER;
int Solve()
{

}
int main()
{
	// 총 이동 시간
	T = 20;

	// 시간 별로 생성되는 신발 등록
	shoes.push_back(Shoe(3, 4, 10, 3));
	shoes.push_back(Shoe(4, 1, 4, 2));
	shoes.push_back(Shoe(10, 2, 5, 5));
	shoes.push_back(Shoe(15, 1, 3, 7));
	std::sort(shoes.begin(), shoes.end(), [=](Shoe& left, Shoe& right) {return left.time < right.time; });
}

