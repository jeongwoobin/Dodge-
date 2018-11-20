#include "show.h"
//메뉴
//랭킹(입출력)시스템
//사운드(충돌시, 게임시작카운트)
//게임종료시 ■로 END

//@@@@@@@@@@@@@@@@@@@오류 : 게임 하다보면 총알피한갯수누적->강제종료


int start, end;		//시간변수
int temp = 0;		//while문 반복횟수

void menu() {
	//게임이름 ■로 쓰기
	while (1) {
		int num = 0;		//메뉴선택

		printFrame();
		gotoxy(22, 13); printf("<<메뉴를 선택하세요>>");
		gotoxy(22, 14);  printf("1.  게임시작\n");
		gotoxy(22, 15);  printf("2.  랭킹\n");
		gotoxy(22, 16);  printf("3.  종료\n");
		gotoxy(44, 13);  scanf_s("%d", &num);
		system("cls");
		printFrame();
		frameMove();
		system("cls");

		switch (num) {
			case 1:
				gameStart();
				frameMove();
				system("cls");
				break;
			case 2:
				rank();
				break;
			case 3:
				return ;
		}//switch
	}//while
}

void gameStart() {
	struct _bullet* bullet = malloc(sizeof(struct _bullet)*THE_NUMBER_OF_BULLETS);
	struct _bullet bu[THE_NUMBER_OF_BULLETS];
	*bullet = bu[THE_NUMBER_OF_BULLETS];

	printFrame();

	createValue(bullet); // user와 bullet값 초기화
	firstPrintUser();
	gotoxy(15, 10);  printf("<< 시작하려면 아무키나 누르세요 >>");
	system("pause>nul");
	gotoxy(15, 10); printf("                                  ");
	start = clock();		//게임시작시간

	while (1) {
		if (checkCrush(bullet) == 1) { // user와 bullet들 중 하나라도 부딪히면 break;
			gotoxy(24, 10);  printf("충돌하였습니다.");
			temp = 0;
			system("pause>nul");
			break;
		}
			
		if (disappearBullets(bullet) == 1) {  // bullet들이 모두 소멸되면 break;
			gotoxy(15, 10);  printf("모든 총알을 피했습니다!");
			temp = 0;
			system("pause>nul");
			break;
		}

		end = clock();						//지금까지 흐른 시간으로 총알들 출발,이동
		int rtime = end - start;
		if (rtime % UPDATE_SPEED_OF_BULLET == 1) {	//UPDATE_SPEED_OF_BULLET 초마다
			updateBullets(bullet);
			printBullets(bullet);
		}//if

		updateUser();
	}//while
}

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

 void firstPrintUser() {
	gotoxy(user.x, user.y); 	printf("★");
}

void printBullets(struct _bullet* bullet) {
	for (int i = 0; i < THE_NUMBER_OF_BULLETS; i++) {
		if (bullet[i].isPrint == 1) {
			switch (bullet[i].direction) {			//현재 총알위치로 이동하여 지우고 다시 프린트
			case 1:
				if (bullet[i].x == 2 || bullet[i].y == 29) {				//벽에 닿으면
					gotoxy(bullet[i].x, bullet[i].y);
					printf("  ");
					bullet[i].isPrint = 2;										//총알 소멸
					break;
				}
				else {
					gotoxy(bullet[i].x, bullet[i].y); printf("  ");		//원래총알지우고
					bullet[i].x -= 2;
					bullet[i].y++;
					gotoxy(bullet[i].x, bullet[i].y); printf("●");		//이동해서 프린트
					break;
				}
			case 2:
				if (bullet[i].y == 29) {
					gotoxy(bullet[i].x, bullet[i].y);
					printf("  ");
					bullet[i].isPrint = 2;
					break;
				}
				else {
					gotoxy(bullet[i].x, bullet[i].y); printf("  ");
					bullet[i].y++;
					gotoxy(bullet[i].x, bullet[i].y); printf("●");
					break;
				}
			case 3:
				if (bullet[i].x == 58 || bullet[i].y == 29) {
					gotoxy(bullet[i].x, bullet[i].y);
					printf("  ");
					bullet[i].isPrint = 2;
					break;
				}
				else {
					gotoxy(bullet[i].x, bullet[i].y); printf("  ");
					bullet[i].x += 2;
					bullet[i].y++;
					gotoxy(bullet[i].x, bullet[i].y); printf("●");
					break;
				}
			case 4:
				if (bullet[i].x == 2) {
					gotoxy(bullet[i].x, bullet[i].y);
					printf("  ");
					bullet[i].isPrint = 2;
					break;
				}
				else {
					gotoxy(bullet[i].x, bullet[i].y); printf("  ");
					bullet[i].x -= 2;
					gotoxy(bullet[i].x, bullet[i].y); printf("●");
					break;
				}
			case 6:
				if (bullet[i].x == 58) {
					gotoxy(bullet[i].x, bullet[i].y);
					printf("  ");
					bullet[i].isPrint = 2;
					break;
				}
				else {
					gotoxy(bullet[i].x, bullet[i].y); printf("  ");
					bullet[i].x += 2;
					gotoxy(bullet[i].x, bullet[i].y); printf("●");
					break;
				}
			case 7:
				if (bullet[i].x == 2 || bullet[i].y == 1) {
					gotoxy(bullet[i].x, bullet[i].y);
					printf("  ");
					bullet[i].isPrint = 2;
					break;
				}
				else {
					gotoxy(bullet[i].x, bullet[i].y); printf("  ");
					bullet[i].x -= 2;
					bullet[i].y--;
					gotoxy(bullet[i].x, bullet[i].y); printf("●");
					break;
				}
			case 8:
				if (bullet[i].y == 1) {
					gotoxy(bullet[i].x, bullet[i].y);
					printf("  ");
					bullet[i].isPrint = 2;
					break;
				}
				else {
					gotoxy(bullet[i].x, bullet[i].y); printf("  ");
					bullet[i].y--;
					gotoxy(bullet[i].x, bullet[i].y); printf("●");
					break;
				}
			case 9:
				if (bullet[i].x == 58 || bullet[i].y == 1) {
					gotoxy(bullet[i].x, bullet[i].y);
					printf("  ");
					bullet[i].isPrint = 2;
					break;
				}
				else {
					gotoxy(bullet[i].x, bullet[i].y); printf("  ");
					bullet[i].x += 2;
					bullet[i].y--;
					gotoxy(bullet[i].x, bullet[i].y); printf("●");
					break;
				}
			}//switch
		}//if
	}//for
}

void updateUser() {
	if (_kbhit()) {
		int key = _getch();

		switch (key) {
		case 224:
			key = _getch();
			if (key == 72) {	//상
				if (user.y == 1)
					user.y;
				else {
					gotoxy(user.x, user.y); printf("  ");
					user.y--;
				}
			}
			else if (key == 80) { //하
				if (user.y == 29)
					user.y;
				else {
					gotoxy(user.x, user.y); printf("  ");
					user.y++;
				}
			}
			else if (key == 75) { //좌
				if (user.x == 2)
					user.x;
				else {
					gotoxy(user.x, user.y); printf("  ");
					user.x -= 2;
				}
			}
			else if (key == 77) { //우
				if (user.x == 58)
					user.x;
				else {
					gotoxy(user.x, user.y); printf("  ");
					user.x += 2;
				}
			}
		}//switch

		gotoxy(user.x, user.y); printf("★");
	}//kbhit
}

void updateBullets(struct _bullet* bullet) {
	if (temp < THE_NUMBER_OF_BULLETS) {		//while문 한번 돌째마다 총알 하나 진행시키고 THE_NUMBER_OF_BULLETS와 temp가 같아지면(총알이 모두 진행하면) 더이상 총알 생성x
		bullet[temp].isPrint = 1;
		temp++;
	}
}

void createValue(struct _bullet* bullet){
	user.x = 30;
	user.y = 15;

	srand((unsigned int)time(NULL));
	for (int i = 0; i < THE_NUMBER_OF_BULLETS; i++) {
		bullet[i].isPrint = 0;

		bullet[i].startingLocation = rand() % 4; // 상하좌우 중 하나 배정
		switch (bullet[i].startingLocation) {
		case 0: // 상
			bullet[i].x = (rand() % 29) * 2 + 2; // 2 ~ 58 중에서 짝수
			bullet[i].y = 1;
			bullet[i].direction = rand() % 3 + 1; // 방향 1, 2, 3중에 할당
			break;
		case 1: // 하
			bullet[i].x = (rand() % 29) * 2 + 2; // 2 ~ 58 중에서 짝수
			bullet[i].y = 29;
			bullet[i].direction = rand() % 3 + 7; // 방향 7, 8 ,9 중에 할당
			break;
		case 2: // 좌
			bullet[i].x = 2;
			bullet[i].y = rand() % 29 + 1; // 1 ~ 29
			bullet[i].direction = (rand() % 3 + 1) * 3; // 방향 3, 6, 9 중에 할당
			break;
		case 3: // 우
			bullet[i].x = 58;
			bullet[i].y = rand() % 29 + 1; // 1 ~ 29
			bullet[i].direction = (rand() % 3 + 1) * 3 - 2; // 방향 1, 4, 7 중에 할당
			break;
		}//switch
	}//for
}

int checkCrush(struct _bullet* bullet) {
	int count = 0; // x, y 겹치면 각각 +1해서 +2되면 완전 겹침

	for (int i = 0; i < THE_NUMBER_OF_BULLETS; i++) {
		if ((user.x == bullet[i].x) && (bullet[i].isPrint == 1)) {
			count++;
		}
		if (user.y == bullet[i].y && (bullet[i].isPrint == 1)) {
			count++;
		}

		if (count == 2) {
			break;
		}
		else {
			count = 0;
		}
	}//for
	
	if (count == 2) {
		return 1;
	}
	else {
		return 0;
	}
}

int disappearBullets(struct _bullet* bullet) {
	int count = 0;
	
	for (int i = 0; i < THE_NUMBER_OF_BULLETS; i++) {
		if (bullet[i].isPrint == 2) {
			count++;
		}
	}

	if (count == THE_NUMBER_OF_BULLETS) {
		return 1;
	}
	else {
		return 0;
	}
}

void rank() {

}

void frameMove() {
	int upY = 1;
	int downY = 29;
	int leftX = 2;
	int rightX = 58;
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
	}
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
	}
}

