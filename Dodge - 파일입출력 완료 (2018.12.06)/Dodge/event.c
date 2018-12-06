#include "event.h"

void printFrame() {
	for (int i = 2; i < 60; i++) {		//2~58
		gotoxy(i++, 0);
		printf("■");
	}
	for (int i = 1; i < 30; i++) {		//1~29
		gotoxy(0, i);
		printf("■");
	}
	for (int i = 2; i < 60; i++) {
		gotoxy(i++, 30);
		printf("■");
	}
	for (int i = 1; i < 30; i++) {
		gotoxy(60, i);
		printf("■");
	}
}

void frameMove() {
	int upY = 1;
	int downY = 29;
	int leftX = 2;
	int rightX = 58;
	system("cls");
	printFrame();
	for (int i = 0; i < 15; i++) {			//그냥 반복		0~62    0~31			가운데 30,15
		for (int x = (i * 2) + 4; x < 58 - (i * 2); x++) {		//위
			gotoxy(x++, upY);
			printf("■");
		}
		for (int y = i + 2; y < 29 - i; y++) {		//왼쪽
			gotoxy(leftX, y);
			printf("■");
		}
		for (int x = (i * 2) + 4; x < 58 - (i * 2); x++) {		//아래
			gotoxy(x++, downY);
			printf("■");
		}
		for (int y = i + 2; y < 29 - i; y++) {		//오른쪽
			gotoxy(rightX, y);
			printf("■");
		}
		upY++;
		downY--;
		leftX += 2;
		rightX -= 2;
		delay(50);
	}//for
	upY -= 2;
	downY += 2;
	leftX -= 4;
	rightX += 4;
	for (int i = 0; i < 15; i++) {			//그냥 반복		0~62    0~31			가운데 30,15
		for (int x = 30 - (i * 2); x < (i * 2) + 32; x++) {		//위
			gotoxy(x++, upY);
			printf("   ");
		}
		for (int y = 15 - i; y < 16 + i; y++) {		//왼쪽
			gotoxy(leftX, y);
			printf(" ");
		}
		for (int x = 30 - (i * 2); x < (i * 2) + 32; x++) {		//아래
			gotoxy(x++, downY);
			printf("  ");
		}
		for (int y = 15 - i; y < 16 + i; y++) {		//오른쪽
			gotoxy(rightX, y);
			printf("  ");
		}
		upY--;
		downY++;
		leftX -= 2;
		rightX += 2;
		delay(50);
	}//for
	system("cls");
}

void printGameName() {
	gotoxy(8, 5); printf("■");
	gotoxy(10, 5); printf("■");
	gotoxy(12, 5); printf("■");
	gotoxy(8, 6); printf("■");
	gotoxy(14, 6); printf("■");
	gotoxy(8, 7); printf("■");
	gotoxy(14, 7); printf("■");
	gotoxy(8, 8); printf("■");
	gotoxy(14, 8); printf("■");
	gotoxy(8, 9); printf("■");
	gotoxy(10, 9); printf("■");
	gotoxy(12, 9); printf("■");		//D

	gotoxy(20, 5); printf("■");
	gotoxy(22, 5); printf("■");
	gotoxy(18, 6); printf("■");
	gotoxy(24, 6); printf("■");
	gotoxy(18, 7); printf("■");
	gotoxy(24, 7); printf("■");
	gotoxy(18, 8); printf("■");
	gotoxy(24, 8); printf("■");
	gotoxy(20, 9); printf("■");
	gotoxy(22, 9); printf("■");		//O

	gotoxy(28, 5); printf("■");
	gotoxy(30, 5); printf("■");
	gotoxy(32, 5); printf("■");
	gotoxy(28, 6); printf("■");
	gotoxy(34, 6); printf("■");
	gotoxy(28, 7); printf("■");
	gotoxy(34, 7); printf("■");
	gotoxy(28, 8); printf("■");
	gotoxy(34, 8); printf("■");
	gotoxy(28, 9); printf("■");
	gotoxy(30, 9); printf("■");
	gotoxy(32, 9); printf("■");		//D

	gotoxy(40, 5); printf("■");
	gotoxy(42, 5); printf("■");
	gotoxy(38, 6); printf("■");
	gotoxy(38, 7); printf("■");
	gotoxy(42, 7); printf("■");
	gotoxy(44, 7); printf("■");
	gotoxy(38, 8); printf("■");
	gotoxy(44, 8); printf("■");
	gotoxy(40, 9); printf("■");
	gotoxy(42, 9); printf("■");		//G

	gotoxy(48, 5); printf("■");
	gotoxy(50, 5); printf("■");
	gotoxy(52, 5); printf("■");
	gotoxy(48, 6); printf("■");
	gotoxy(48, 7); printf("■");
	gotoxy(50, 7); printf("■");
	gotoxy(52, 7); printf("■");
	gotoxy(48, 8); printf("■");
	gotoxy(48, 9); printf("■");
	gotoxy(50, 9); printf("■");
	gotoxy(52, 9); printf("■");		//E

}

void printGameOver() {
	gotoxy(7, 5); printf("■");
	gotoxy(9, 5); printf("■");
	gotoxy(5, 6); printf("■");
	gotoxy(5, 7); printf("■");
	gotoxy(9, 7); printf("■");
	gotoxy(11, 7); printf("■");
	gotoxy(5, 8); printf("■");
	gotoxy(11, 8); printf("■");
	gotoxy(7, 9); printf("■");
	gotoxy(9, 9); printf("■");		//G

	gotoxy(18, 5); printf("■");
	gotoxy(17, 6); printf("■");
	gotoxy(19, 6); printf("■");
	gotoxy(16, 7); printf("■");
	gotoxy(20, 7); printf("■");
	gotoxy(15, 8); printf("■");
	gotoxy(21, 8); printf("■");
	gotoxy(15, 9); printf("■");
	gotoxy(21, 9); printf("■");		//A

	gotoxy(25, 5); printf("■");
	gotoxy(31, 5); printf("■");
	gotoxy(25, 6); printf("■");
	gotoxy(27, 6); printf("■");
	gotoxy(29, 6); printf("■");
	gotoxy(31, 6); printf("■");
	gotoxy(25, 7); printf("■");
	gotoxy(28, 7); printf("■");
	gotoxy(31, 7); printf("■");
	gotoxy(25, 8); printf("■");
	gotoxy(31, 8); printf("■");
	gotoxy(25, 9); printf("■");
	gotoxy(31, 9); printf("■");		//M

	gotoxy(35, 5); printf("■");
	gotoxy(37, 5); printf("■");
	gotoxy(39, 5); printf("■");
	gotoxy(35, 6); printf("■");
	gotoxy(35, 7); printf("■");
	gotoxy(37, 7); printf("■");
	gotoxy(39, 7); printf("■");
	gotoxy(35, 8); printf("■");
	gotoxy(35, 9); printf("■");
	gotoxy(37, 9); printf("■");
	gotoxy(39, 9); printf("■");		//E
	delay(500);

	gotoxy(24, 12); printf("■");
	gotoxy(26, 12); printf("■");
	gotoxy(22, 13); printf("■");
	gotoxy(28, 13); printf("■");
	gotoxy(22, 14); printf("■");
	gotoxy(28, 14); printf("■");
	gotoxy(22, 15); printf("■");
	gotoxy(28, 15); printf("■");
	gotoxy(24, 16); printf("■");
	gotoxy(26, 16); printf("■");		//O

	gotoxy(32, 12); printf("■");
	gotoxy(38, 12); printf("■");
	gotoxy(32, 13); printf("■");
	gotoxy(38, 13); printf("■");
	gotoxy(33, 14); printf("■");
	gotoxy(37, 14); printf("■");
	gotoxy(34, 15); printf("■");
	gotoxy(36, 15); printf("■");
	gotoxy(35, 16); printf("■");		//V

	gotoxy(42, 12); printf("■");
	gotoxy(44, 12); printf("■");
	gotoxy(46, 12); printf("■");
	gotoxy(42, 13); printf("■");
	gotoxy(42, 14); printf("■");
	gotoxy(44, 14); printf("■");
	gotoxy(46, 14); printf("■");
	gotoxy(42, 15); printf("■");
	gotoxy(42, 16); printf("■");
	gotoxy(44, 16); printf("■");
	gotoxy(46, 16); printf("■");		//E

	gotoxy(50, 12); printf("■");
	gotoxy(52, 12); printf("■");
	gotoxy(54, 12); printf("■");
	gotoxy(50, 13); printf("■");
	gotoxy(55, 13); printf("■");
	gotoxy(50, 14); printf("■");
	gotoxy(52, 14); printf("■");
	gotoxy(54, 14); printf("■");
	gotoxy(50, 15); printf("■");
	gotoxy(55, 15); printf("■");
	gotoxy(50, 16); printf("■");
	gotoxy(55, 16); printf("■");		//R
	delay(500);
}

void printGameSet() {
	gotoxy(7, 5); printf("■");
	gotoxy(9, 5); printf("■");
	gotoxy(5, 6); printf("■");
	gotoxy(5, 7); printf("■");
	gotoxy(9, 7); printf("■");
	gotoxy(11, 7); printf("■");
	gotoxy(5, 8); printf("■");
	gotoxy(11, 8); printf("■");
	gotoxy(7, 9); printf("■");
	gotoxy(9, 9); printf("■");		//G

	gotoxy(18, 5); printf("■");
	gotoxy(17, 6); printf("■");
	gotoxy(19, 6); printf("■");
	gotoxy(16, 7); printf("■");
	gotoxy(20, 7); printf("■");
	gotoxy(15, 8); printf("■");
	gotoxy(21, 8); printf("■");
	gotoxy(15, 9); printf("■");
	gotoxy(21, 9); printf("■");		//A

	gotoxy(25, 5); printf("■");
	gotoxy(31, 5); printf("■");
	gotoxy(25, 6); printf("■");
	gotoxy(27, 6); printf("■");
	gotoxy(29, 6); printf("■");
	gotoxy(31, 6); printf("■");
	gotoxy(25, 7); printf("■");
	gotoxy(28, 7); printf("■");
	gotoxy(31, 7); printf("■");
	gotoxy(25, 8); printf("■");
	gotoxy(31, 8); printf("■");
	gotoxy(25, 9); printf("■");
	gotoxy(31, 9); printf("■");		//M

	gotoxy(35, 5); printf("■");
	gotoxy(37, 5); printf("■");
	gotoxy(39, 5); printf("■");
	gotoxy(35, 6); printf("■");
	gotoxy(35, 7); printf("■");
	gotoxy(37, 7); printf("■");
	gotoxy(39, 7); printf("■");
	gotoxy(35, 8); printf("■");
	gotoxy(35, 9); printf("■");
	gotoxy(37, 9); printf("■");
	gotoxy(39, 9); printf("■");		//E
	delay(500);

	gotoxy(34, 12); printf("■");
	gotoxy(36, 12); printf("■");
	gotoxy(38, 12); printf("■");
	gotoxy(34, 13); printf("■");
	gotoxy(34, 14); printf("■");
	gotoxy(36, 14); printf("■");
	gotoxy(38, 14); printf("■");
	gotoxy(38, 15); printf("■");
	gotoxy(34, 16); printf("■");
	gotoxy(36, 16); printf("■");
	gotoxy(38, 16); printf("■");		//S

	gotoxy(42, 12); printf("■");
	gotoxy(44, 12); printf("■");
	gotoxy(46, 12); printf("■");
	gotoxy(42, 13); printf("■");
	gotoxy(42, 14); printf("■");
	gotoxy(44, 14); printf("■");
	gotoxy(46, 14); printf("■");
	gotoxy(42, 15); printf("■");
	gotoxy(42, 16); printf("■");
	gotoxy(44, 16); printf("■");
	gotoxy(46, 16); printf("■");		//E

	gotoxy(49, 12); printf("■");
	gotoxy(51, 12); printf("■");
	gotoxy(53, 12); printf("■");
	gotoxy(55, 12); printf("■");
	gotoxy(52, 13); printf("■");
	gotoxy(52, 14); printf("■");
	gotoxy(52, 15); printf("■");
	gotoxy(52, 16); printf("■");		//T
	delay(500);
}

void printEnd() {
	gotoxy(20, 13); printf("■");
	gotoxy(22, 13); printf("■");
	gotoxy(24, 13); printf("■");
	gotoxy(20, 14); printf("■");
	gotoxy(20, 15); printf("■");
	gotoxy(22, 15); printf("■");
	gotoxy(24, 15); printf("■");
	gotoxy(20, 16); printf("■");
	gotoxy(20, 17); printf("■");
	gotoxy(22, 17); printf("■");
	gotoxy(24, 17); printf("■");		//E
	delay(500);

	gotoxy(28, 13); printf("■");
	gotoxy(34, 13); printf("■");
	gotoxy(28, 14); printf("■");
	gotoxy(30, 14); printf("■");
	gotoxy(34, 14); printf("■");
	gotoxy(28, 15); printf("■");
	gotoxy(31, 15); printf("■");
	gotoxy(34, 15); printf("■");
	gotoxy(28, 16); printf("■");
	gotoxy(32, 16); printf("■");
	gotoxy(34, 16); printf("■");
	gotoxy(28, 17); printf("■");
	gotoxy(34, 17); printf("■");		//N
	delay(500);

	gotoxy(38, 13); printf("■");
	gotoxy(40, 13); printf("■");
	gotoxy(42, 13); printf("■");
	gotoxy(38, 14); printf("■");
	gotoxy(44, 14); printf("■");
	gotoxy(38, 15); printf("■");
	gotoxy(44, 15); printf("■");
	gotoxy(38, 16); printf("■");
	gotoxy(44, 16); printf("■");
	gotoxy(38, 17); printf("■");
	gotoxy(40, 17); printf("■");
	gotoxy(42, 17); printf("■");		//D
	delay(500);


	gotoxy(4, 26);
}



void delay(clock_t n)					//printframe 딜레이
{
	clock_t start = clock();
	while (clock() - start < n);
}