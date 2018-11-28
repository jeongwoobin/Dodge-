#include "console.h"

void gotoxy(int x, int y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void disappearConsoleCursor() {
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };													//커서없애는 코드 ↓
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);		//커서없애는 코드 ↑
}

void updateConsoleSize() {
	system("mode con cols=62 lines=31");			//(62,31)															//콘솔창크기설정
}