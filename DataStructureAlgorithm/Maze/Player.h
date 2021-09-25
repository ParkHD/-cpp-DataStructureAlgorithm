#pragma once

class Board;

class Player
{
	enum
	{
		MOVE_TICK = 100
	};
public:
	void Init(Board* board);
	void Update(uint64 deltaTick);

	void Setpos(Pos pos) { _pos = pos; }
	Pos GetPos() { return _pos; }

	bool CanGo(Pos pos);
private:
	void RightHand();
	void Bfs();
private:
	Pos _pos = {};
	int32 _dir = DIR_UP;
	Board* _board = nullptr;

	// 이동경로
	vector<Pos> _path;
	uint32 _pathIndex = 0;
	uint64 _sumTick = 0;
};

