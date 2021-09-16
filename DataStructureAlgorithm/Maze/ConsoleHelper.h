#pragma once
#include <windows.h>
#include "Types.h"

// �ֿܼ� ����� ����
enum class ConsoleColor
{
	BLACK = 0,
	RED = FOREGROUND_RED,
	GREEN = FOREGROUND_GREEN,
	BLUE = FOREGROUND_BLUE,
	YELLOW = RED | GREEN,
	WHITE = RED | GREEN | BLUE,
};

class ConsoleHelper
{
public:
	// ���콺 Ŀ�� ��ġ����
	static void SetCursorPosition(int32 x, int32 y);
	// ���콺 Ŀ�� ���� ����
	static void SetCursorColor(ConsoleColor color);
	// ���콺 Ŀ���� ������
	static void ShowConsoleCursor(bool flag);

};

