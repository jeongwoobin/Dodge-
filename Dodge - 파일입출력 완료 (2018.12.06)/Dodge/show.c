#include "show.h"

//사운드(충돌시, 게임시작카운트)
//GUI, 사운드 함수들 따로 소스파일로 모아놓기
//개발자 setting메뉴(총알속도, 갯수)


struct _rank rank[SIZE_OF_RANK] = { "", 0 };		//랭킹구조체 선언, 초기화
struct _select menuXY;		//메뉴선택 구조체
struct _select alphaXY;		//닉네임선택구조체
int start, timeEnd, bulletTimeEnd;		//시간변수
int temp = 0;		//while문 반복횟수
char num2 = 0;	//개행문자 가져가는변수
int num3;			//개행문자 가져가는변수

void menu() {
	outputRank();
	menuXY.x = 22;
	menuXY.y = 17;
	while (1) {
		int num = 0;		//메뉴선택

		printFrame();
		printGameName();	
		gotoxy(22, 16); printf("<<메뉴를 선택하세요>>");
		gotoxy(22, 17);  printf("1");
		gotoxy(26, 17);  printf("게임시작");
		gotoxy(22, 18);  printf("2");
		gotoxy(26, 18);  printf("랭킹");
		gotoxy(22, 19);  printf("3");
		gotoxy(26, 19);  printf("종료");

		selectMenu();
	}//while
}

void selectMenu() {
	gotoxy(menuXY.x, menuXY.y);  printf("▶");
	if (_kbhit()) {
		int key = _getch();
		if (key == 224) {
			key = _getch();
			if (key == 72) {
				if (menuXY.y == 17) {
					menuXY.y;
				}
				else {
					if (menuXY.y == 18) {
						gotoxy(menuXY.x, menuXY.y); printf("2 ");
						menuXY.y--;
					}
					else {
						gotoxy(menuXY.x, menuXY.y); printf("3 ");
						menuXY.y--;
					}
				}
				gotoxy(menuXY.x, menuXY.y);  printf("▶");
			}		//방향키 상
			if (key == 80) {
				if (menuXY.y == 19) {
					menuXY.y;
				}
				else {
					if (menuXY.y == 18) {
						gotoxy(menuXY.x, menuXY.y); printf("2 ");
						menuXY.y++;
					}
					else {
						gotoxy(menuXY.x, menuXY.y); printf("1 ");
						menuXY.y++;
					}
				}
				gotoxy(menuXY.x, menuXY.y);	 printf("▶");
			}	  //방향키 하
		}	//if 방향키 아래 위
		if (key == 13) {
			key = _getch();
			frameMove();
			system("cls");
			if (menuXY.y == 17) {
				gameStart();
				system("cls");
				frameMove();
			}
			if (menuXY.y == 18) {
				printRank();
				system("cls");
				frameMove();
			}
			if (menuXY.y == 19) {
				system("cls");
				printFrame();
				printEnd();
				exit(0);
			}
		}		//if 엔터입력
	}	//if 키를 입력했을때
}

void gameStart() {
	struct _bullet* bullet = malloc(sizeof(struct _bullet)*THE_NUMBER_OF_BULLETS);
	struct _bullet bu[THE_NUMBER_OF_BULLETS];
	*bullet = bu[THE_NUMBER_OF_BULLETS];

	printFrame();

	createValue(bullet); // user와 bullet값 초기화
	firstPrintUser();
	gotoxy(15, 10);  printf("<< 시작하려면 아무키나 누르세요 >>");
	num3 = _getch();
	gotoxy(15, 10); printf("                                  ");					//위에 글자 지우기
	start = clock();		//게임시작시간

	while (1) {
		if (gameOver(bullet) == TRUE) {			//충돌하거나 모두 피하거나
			break;
		}

		bulletTimeEnd = clock();						//지금까지 흐른 시간으로 총알들 출발,이동
		int bulletTime = bulletTimeEnd - start;
		if (bulletTime % UPDATE_SPEED_OF_BULLET == 1) {	//UPDATE_SPEED_OF_BULLET 초마다
			updateBullets(bullet);
			printBullets(bullet);
		}//if

		updateUser();
	}//while
	free(bullet);
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

void createValue(struct _bullet* bullet) {
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

boolean gameOver(struct _bullet* bullet) {
	if (checkCrush(bullet) == 1 || disappearBullets(bullet) == 1 ) { // user와 bullet들 중 하나라도 부딪히면 break;, bullet들을 모두 피하면 break;
		addRank(bullet);
		temp = 0;
		return TRUE;
	}
	return FALSE;
}

void addRank(struct _bullet* bullet) {
	char save;
	
	timeEnd = clock();
	rank[SIZE_OF_RANK-1].end = timeEnd - start;
	while(1) {
		system("cls");
		printFrame();
		if (checkCrush(bullet) == 1) {
			printGameOver();
		}
		if (disappearBullets(bullet) == 1) {
			printGameSet();
		}
		gotoxy(12, 19);  printf("랭킹을 저장하시겠습니까? (Y/N)>>"); 	scanf_s("%c", &save, sizeof(save));
		scanf("%*c");

		if (save == 'Y' || save == 'y') {
			selectName();
			gotoxy(34,28); printf("랭킹저장완료");
			delay(500);
			break;
		}

		else if (save == 'N' || save == 'n') {
			gotoxy(34, 28);  printf("랭킹을 저장하지 않습니다.");
			rank[SIZE_OF_RANK - 1].end = 0;
			delay(500);
			break;
		}//else if

		else {
			gotoxy(34, 28);  printf("Y나 N을 입력하셔야합니다.");		//다른문자 입력하면 다시랭킹저장 물어봄
			delay(500);
		}//else
	}//while
	rankSort();			//랭킹정렬
	inputRank();
}

void inputRank() {
#pragma pack(push, 1)		//1바이트크기로 정렬
	FILE *file_pointer;

	file_pointer = fopen("Ranking.txt", "wt");
	for (int i = 0; i < sizeof(rank) / sizeof(rank[0]); i++) {
		if (rank[i].end == 0) {
			continue;
		}
		fwrite(&rank[i], sizeof(rank) / sizeof(rank[0]), 1 , file_pointer);
	}
	fclose(file_pointer);
#pragma pack(pop)			//기본값으로 정렬
}	

void outputRank() {
#pragma pack(push, 1)
	FILE *file_pointer;

	file_pointer = fopen("Ranking.txt", "rt");
	if (file_pointer == NULL) {								//오류 or 파일 없을시 새로 생성 
		file_pointer = fopen("Ranking.txt", "at");
		fclose(file_pointer);
		return;
	}
	for (int i = 0; i < (sizeof(rank) / sizeof(rank[0]))-1; i++) {
		fread(&rank[i], sizeof(rank) / sizeof(rank[0]), 1, file_pointer);
	}
	fclose(file_pointer);
#pragma pack(pop)
}

void rankSort() {
	struct _rank temp = { "", 0 };
	for (int i = 0; i < sizeof(rank)/sizeof(rank[0]); i++) {				//버블소트
		for (int j = 0; j < sizeof(rank)/sizeof(rank[0])-i-1; j++) {
			if (rank[j].end < rank[j + 1].end) {
				temp = rank[j];
				rank[j] = rank[j + 1];
				rank[j + 1] = temp;
			}
		}
	}
}

void printRank() {
	printFrame();
	outputRank();
	rankSort();	
	gotoxy(4, 4);  printf("-------------------------랭킹-------------------------");
	for (int i = 0; i < sizeof(rank) / sizeof(rank[0]) - 1; i++) {
		if (rank[i].name == NULL)
			break;
		if (i == 0) {
			gotoxy(12, i + 5); printf("%2d위    %3s %6d초", i + 1, &rank[i].name, rank[i].end);
		}
		else if (rank[i].end != 0) {
			gotoxy(12, i + 5); printf("%2d위    %3s %6d초         + %5d", i + 1, &rank[i].name, rank[i].end, rank[i - 1].end - rank[i].end);
		}
		else {
			gotoxy(12, i + 5); printf("%2d위    %3s %6d초", i + 1, &rank[i].name, rank[i].end);
		}
	}
	gotoxy(4, 25);  printf("-------------------------------------------------------\n");
	system("pause>nul");
}

void selectName() {
	alphaXY.x = 9;
	alphaXY.y = 21;
	char saveName[4] = "";			//닉네임배열 선언, 초기화
	int saveNameLen = 0;
	
	//알파벳 출력
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 9; j++) {
			gotoxy(9 + (j * 5), 21 + (i * 2)); printf("○%c", 'A' + (i * 9) + j);
			if (i == 2 && j == 8) {
				gotoxy(9 + (j * 5), 21 + (i * 2)); printf("○DEL");		//Z까지 출력하고 다음 값 DEL
			}
		}
	}
	gotoxy(9, 27); printf("닉네임>> ");
	gotoxy(alphaXY.x, alphaXY.y); printf("●");

	while (1) {
		if (_kbhit()) {
			int key = _getch();
			if (key == 224) {
				key = _getch();
				if (key == 72) {	//상
					if (alphaXY.y == 21)
						alphaXY.y;
					else {
						gotoxy(alphaXY.x, alphaXY.y); printf("○");
						alphaXY.y -= 2;
					}
				}
				else if (key == 80) { //하
					if (alphaXY.y == 25)
						alphaXY.y;
					else {
						gotoxy(alphaXY.x, alphaXY.y); printf("○");
						alphaXY.y += 2;
					}
				}
				else if (key == 75) { //좌
					if (alphaXY.x == 9)
						alphaXY.x;
					else {
						gotoxy(alphaXY.x, alphaXY.y); printf("○");
						alphaXY.x -= 5;
					}
				}
				else if (key == 77) { //우
					if (alphaXY.x == 49)
						alphaXY.x;
					else {
						gotoxy(alphaXY.x, alphaXY.y); printf("○");
						alphaXY.x += 5;
					}
				}
				gotoxy(alphaXY.x, alphaXY.y); printf("●");
			}	//if 방향키 입력

			if (key == 13) {
				key = _getch();
				if (alphaXY.x == 49 && alphaXY.y == 25) {
					if (saveNameLen == 0) {
						continue;
					}
					else {
						saveName[saveNameLen - 1] = '\0';
						gotoxy(18, 27); printf("      ");
						gotoxy(18, 27); printf("%s", saveName);
						saveNameLen--;
					}
				}	//del에서 엔터
				else {
					saveName[saveNameLen] = 'A' + (((alphaXY.x - 9) / 5) + (9 * (alphaXY.y - 21) / 2));
					gotoxy(18, 27);
					if (saveNameLen == 0) {
						saveName[saveNameLen + 1] = '\0';
						printf("%s", saveName);
					}
					else if (saveNameLen == 1) {
						saveName[saveNameLen + 1] = '\0';
						printf("%s", saveName);
					}
					else {
						saveName[saveNameLen + 1] = '\0';
						printf("%s", saveName);
						strcpy(rank[SIZE_OF_RANK - 1].name, saveName);		//랭킹 마지막에 이름복사
						break;
					}
					saveNameLen++;
				}
			}//if 엔터입력
		}//if _kbhit()
	}//while
}