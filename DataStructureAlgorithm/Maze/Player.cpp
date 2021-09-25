#include "pch.h"
#include "Player.h"
#include "Board.h"
#include <stack>

void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;

	//RightHand();
	Bfs();
}

void Player::Update(uint64 deltaTick)
{
	if(_pathIndex >= _path.size())
		return;

	_sumTick += deltaTick;
	if (_sumTick >= MOVE_TICK)
	{
		_sumTick = 0;
		_pos = _path[_pathIndex];
		_pathIndex++;
	}
}

bool Player::CanGo(Pos pos)
{
	TileType tileType = _board->GetTileType(pos);
	return tileType == TileType::EMPTY;
}

void Player::RightHand()
{
	Pos pos = _pos;

	_path.clear();
	_path.push_back(pos);
	
	Pos dest = _board->GetExitPos();

	// 방향에 따른 앞으로 가는 방향
	Pos front[4] =
	{
		Pos { -1, 0},	// UP
		Pos { 0, -1},	// LEFT
		Pos { 1, 0},	// DOWN
		Pos { 0, 1},	// RIGHT
	};
	while (pos != dest)
	{
		// 1. 현재 바라보는 방향을 기준으로오른쪽으로 갈 수 있는지
		int32 newDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT;
		if (CanGo(pos + front[newDir]))
		{
			// 오른쪽 방향으로 90도 회전
			_dir = newDir;
			// 앞으로 한보 전진
			pos += front[_dir];

			_path.push_back(pos);
		}

		// 2. 현재 바라보는 방향을 기준으로 전진할 수 있는지
		else if (CanGo(pos + front[_dir]))
		{
			// 앞으로 한 보 전진
			pos += front[_dir];

			_path.push_back(pos);
		}
		else
		{
			// 왼쪽 방향으로 90도 회전
			_dir = (_dir + 1) % DIR_COUNT;
		}
	}

	stack<Pos> s;
	for (int i = 0; i < _path.size() - 1; i++)
	{
		if (s.empty() == false && s.top() == _path[i + 1])
			s.pop();
		else
			s.push(_path[i]);

	}
	if (_path.empty() == false)
		s.push(_path.back());

	vector<Pos> path;
	while (s.empty() == false)
	{
		path.push_back(s.top());
		s.pop();
	}
	std::reverse(path.begin(), path.end());

	_path = path;
}

void Player::Bfs()
{
	Pos pos = _pos;

	Pos dest = _board->GetExitPos();

	// 방향에 따른 앞으로 가는 방향
	Pos front[4] =
	{
		Pos { -1, 0},	// UP
		Pos { 0, -1},	// LEFT
		Pos { 1, 0},	// DOWN
		Pos { 0, 1},	// RIGHT
	};

	const int32 size = _board->GetSize();
	vector<vector<bool>> discovered(size, vector<bool>(size, false));

	// parent[a] = b : 
	map<Pos, Pos> parent;


	queue<Pos> q;
	q.push(pos);
	discovered[pos.y][pos.x] = true;

	while (q.empty() == false)
	{
		pos = q.front();
		q.pop();

		if (pos == dest)
			break;
		for(int32 dir = 0; dir < 4; dir++)
		{
			Pos nextPos = pos + front[dir];
			if (CanGo(nextPos) == false)
				continue;
			if (discovered[nextPos.y][nextPos.x])
				continue;

			q.push(nextPos);
			discovered[nextPos.y][nextPos.x] = true;
			parent[nextPos] = pos;
		}
	}

	_path.clear();

	// 거꾸로 조립
	pos = dest;
	while (true)
	{
		_path.push_back(pos);
		if (pos == parent[pos])
			break;
		pos = parent[pos];
	}
	std::reverse(_path.begin(), _path.end());
	_path.push_back(pos);
}
