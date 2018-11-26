#include "console.h"

void gotoxy(int x, int y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void disappearConsoleCursor() {
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };													//Ŀ�����ִ� �ڵ� ��
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);		//Ŀ�����ִ� �ڵ� ��
}

void updateConsoleSize() {
	system("mode con cols=62 lines=31");			//(62,31)															//�ܼ�âũ�⼳��
}