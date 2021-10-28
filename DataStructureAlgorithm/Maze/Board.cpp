#include "pch.h"
#include "Board.h"
#include "Player.h"
#include "DisjointSet.h"

const char* TILE = "■";

Board::Board()
{

}

Board::~Board()
{

}

void Board::Init(int32 size, Player* player)
{
	_size = size;
	_player = player;

	//GenerateMap();
	GenerateMap_Prim();
}

void Board::Render()
{
	// 랜더링 => 보여주는것
	ConsoleHelper::SetCursorPosition(0, 0);
	ConsoleHelper::ShowConsoleCursor(false);

	for (int32 y = 0; y < 25; y++)
	{
		for (int32 x = 0; x < 25; x++)
		{
			ConsoleColor color = GetTileColor(Pos{y,x});
			ConsoleHelper::SetCursorColor(color);
			cout << TILE;
		}
		cout << endl;
	}
}

// Binary Tree 미로 생성 알고리즘
void Board::GenerateMap()
{
	for (int32 y = 0; y < _size; y++)
	{
		for (int32 x = 0; x < _size; x++)
		{
			if(x % 2 == 0 || y % 2 == 0)
				_tile[y][x] = TileType::WALL;
			else
				_tile[y][x] = TileType::EMPTY;
		}
	}
#pragma region BinaryTree

	/*
	//랜덤으로 우측혹은 아래로 길을 뚫는 작업
	for (int32 y = 0; y < _size; y++)
	{
		for (int32 x = 0; x < _size; x++)
		{
			if(x % 2 == 0 || y % 2 == 0)
				continue;
			if (y == _size - 2 && x == _size - 2)
				continue;
			if (y == _size - 2)
			{
				_tile[y][x+1] = TileType::EMPTY;
				continue;
			}
			if (x == _size - 2)
			{
				_tile[y+1][x] = TileType::EMPTY;
				continue;
			}
			const int32 randValue = ::rand() % 2;
			if (randValue == 0)
			{
				_tile[y][x+1] = TileType::EMPTY;
			}
			else
			{
				_tile[y+1][x] = TileType::EMPTY; 
			}
		}
	}
	*/
#pragma endregion
	struct CostEdge
	{
		int cost;
		Pos u;
		Pos v;

		bool operator< (CostEdge& other)
		{
			return cost < other.cost;
		}
	};
	vector<CostEdge> edges;
	//edge 후보를 랜덤 cost로 등록
	for (int32 y = 0; y < _size; y++)
	{
		for (int32 x = 0; x < _size; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
				continue;

			// 우측 연결하는 간선 후보
			if (x < _size - 2)
			{
				const int32 randValue = ::rand() % 100;
				edges.push_back(CostEdge{ randValue, Pos{y ,x }, Pos{y, x + 2} });
			}

			// 아래로 연결하는 간선 후보
			if (y < _size - 2)
			{
				const int32 randValue = ::rand() % 100;
				edges.push_back(CostEdge{ randValue, Pos{y ,x }, Pos{y + 2, x } });
			}
		}
	}

	std::sort(edges.begin(), edges.end());
	
	DisjointSet sets(_size * _size);

	for (CostEdge& edge : edges)
	{
		int u = edge.u.y * _size + edge.u.x;
		int v = edge.v.y * _size + edge.v.x;
		if (sets.Find(u) == sets.Find(v))
			continue;

		// 두 그룹을 합친다
		sets.Merge(u, v);

		//맵에 적용
		int y = (edge.u.y + edge.v.y) / 2;
		int x = (edge.u.x + edge.v.x) / 2;
		_tile[y][x] = TileType::EMPTY;
	}
}

void Board::GenerateMap_Prim()
{
	struct CostEdge
	{
		int cost;
		Pos vtx;

		bool operator< (const CostEdge& other) const
		{
			return cost < other.cost;
		}
	};
	for (int32 y = 0; y < _size; y++)
	{
		for (int32 x = 0; x < _size; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
				_tile[y][x] = TileType::WALL;
			else
				_tile[y][x] = TileType::EMPTY;
		}
	}

	// edges[u] : u정점과 연결된 간선 목록
	map<Pos, vector<CostEdge>> edges;
	// edges후보를 등록
	for (int32 y = 0; y < _size; y++)
	{
		for (int32 x = 0; x < _size; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
				continue;

			// 우측 연결하는 간선 후보
			if (x < _size - 2)
			{
				const int32 randValue = ::rand() % 100;
				Pos u = Pos{ y , x };
				Pos v = Pos{ y, x + 2 };
				// 연결된 정점들 등록
				edges[u].push_back(CostEdge{ randValue, v });
				edges[v].push_back(CostEdge{ randValue, u });
			}

			// 아래로 연결하는 간선 후보
			if (y < _size - 2)
			{
				const int32 randValue = ::rand() % 100;
				Pos u = Pos{ y , x };
				Pos v = Pos{ y + 2, x };
				// 연결된 정점들 등록
				edges[u].push_back(CostEdge{ randValue, v });
				edges[v].push_back(CostEdge{ randValue, u });
			}
		}
	}
	// 해당 정점이 트리에 포함되어 있나?
	map<Pos, bool> added;
	// 어떤 정점이 누구에 의해 연결 되었는지?
	map<Pos, Pos> parent;
	//만들고 있는 트리에 인접한 간선 중, 해당 정점에 닿는 최소 간선의 정보
	map<Pos, int32> best;

	// 다익스트라랑 거의 유사함
	// 다익스트라에서는 best가 시작점을 기준으로 한 cost
	// 프림에서는 best가 현재트리를 기준으로 한 간선 cost

	for (int32 y = 0; y < _size; y++)
	{
		for (int32 x = 0; x < _size; x++)
		{
			best[Pos{ y,x }] = INT32_MAX;
			added[Pos{ y,x }] = false;
		}
	}

	priority_queue<CostEdge> pq;
	const Pos startPos = Pos{ 1,1 };
	pq.push(CostEdge{ 0,startPos });
	best[startPos] = 0;
	parent[startPos] = startPos;

	while (pq.empty() == false)
	{
		CostEdge bestEdge = pq.top();
		pq.pop();

		Pos v = bestEdge.vtx;

		if (added[v])
			continue;

		added[v] = true;

		{
			int y = (parent[v].y + v.y) / 2;
			int x = (parent[v].x + v.x) / 2;
			_tile[y][x] = TileType::EMPTY;
		}

		// 방금 추가한 정점에 인접한 간선들을 검사
		for (CostEdge& edge : edges[v])
		{
			if (added[edge.vtx])
				continue;

			if (edge.cost > best[edge.vtx])
				continue;

			best[edge.vtx] = edge.cost;
			parent[edge.vtx] = v;
			pq.push(edge);
		}
	}
}

TileType Board::GetTileType(Pos pos)
{
	if(pos.x < 0 || pos.x >= _size)
		return TileType::NONE;
	if(pos.y < 0 || pos.y >= _size)
		return TileType::NONE;
	
	return _tile[pos.y][pos.x];
}

ConsoleColor Board::GetTileColor(Pos pos)
{
	if (_player && _player->GetPos() == pos)
		return ConsoleColor::YELLOW;
	
		
	if(GetExitPos() == pos)
		return ConsoleColor::BLUE;
	TileType tileType = GetTileType(pos);

	switch (tileType)
	{
		case TileType::EMPTY:
			return ConsoleColor::GREEN;
		case TileType::WALL:
			return ConsoleColor::RED;

	}
	return ConsoleColor::WHITE;
}
