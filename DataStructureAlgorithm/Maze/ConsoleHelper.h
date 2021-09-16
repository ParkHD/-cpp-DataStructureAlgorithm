#pragma once
#include <windows.h>
#include "Types.h"

// 콘솔에 사용할 색깔
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
	// 마우스 커서 위치설정
	static void SetCursorPosition(int32 x, int32 y);
	// 마우스 커서 색상 설정
	static void SetCursorColor(ConsoleColor color);
	// 마우스 커서를 보일지
	static void ShowConsoleCursor(bool flag);

};

