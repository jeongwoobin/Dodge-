#include "show.h"
//메뉴(화살표이동으로(?))
//랭킹(입출력)시스템---->>>>@@@@@@@@@@@@@랭킹 기록할지 말지
//사운드(충돌시, 게임시작카운트)
//게임이름출력, 게임종료출력시 나오는 ■들 애니메이션효과(?)
//GUI, 사운드 함수들 따로 소스파일로 모아놓기
//개발자 setting메뉴(총알속도, 갯수)

//@@@@@@@@@@@@@@@@@@메뉴 화살표이동 구현중@@@@@@@@@22
//@@@@@@@@@@@@@@@@@@위화살표 입력하면 전에 입력했던 값들이 나옴--오류(?)    , 이니셜입력배열크기넘게 입력하면 밀림@@@@@@@@@@@@@@@@2

struct _rank rank[SIZE_OF_RANK] = { " ", 0 };		//랭킹구조체 선언, 초기화
int start, timeEnd, bulletTimeEnd;		//시간변수
int temp = 0;		//while문 반복횟수
char num2 = 0;	//개행문자 가져가는변수

//void selectMenu() {
//	menuXY.x = 21;
//	menuXY.y = 17;		//menuXY 초기화
//	gotoxy(menuXY.x, menuXY.y); printf("★");
//	if(_kbhit()) {
//		int key = _getch();
//		switch (key) {			//72상 80하 75좌 77우
//			case 224:
//				key = _getch();
//				if (key == 72) {
//					if (menuXY.y == 17) {
//						menuXY.y;
//					}
//					else {
//						if (menuXY.y == 18) {
//							gotoxy(menuXY.x, menuXY.y); printf("2 ");
//							menuXY.y--;
//						}
//						else {
//							gotoxy(menuXY.x, menuXY.y); printf("3 ");
//							menuXY.y--;
//						}
//					}
//				}
//		}
//	}
//}




void menu() {
	//게임이름 ■로 쓰기
	outputRank();
	while (1) {
		int num = 0;		//메뉴선택
		printFrame();
		printGameName();
		gotoxy(21, 16); printf("<<메뉴를 선택하세요>>");
		gotoxy(21, 17);  printf("1  게임시작");	 
		gotoxy(21, 18);  printf("2  랭킹");
		gotoxy(21, 19);  printf("3  종료");

		gotoxy(44, 16);  
		scanf_s("%d", &num, sizeof(num));
		scanf_s("%c", &num2, sizeof(num2));
		
		frameMove();
		system("cls");

		switch (num) {
		case 1:
			gameStart();
			system("cls");
			frameMove();
			break;
		case 2:
			printRank();
			system("cls");
			frameMove();
			break;
		case 3:
			printEnd();
			return;
		default:
			printf("잘못입력하셨습니다.");
			system("pause>nul");
			system("cls");
			break;
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
		addRank();
		temp = 0;
		return TRUE;
	}
	return FALSE;
}

void addRank() {
	char save;
	
	timeEnd = clock();
	rank[SIZE_OF_RANK-1].end = timeEnd - start;
	while(1) {
		system("cls");
		printFrame();
		//gotoxy(26, 10);  printf("GAME SET");
		printGameOver();
		gotoxy(12, 19);  printf("랭킹을 저장하시겠습니까? (Y/N)>>"); 	scanf_s("%c", &save, sizeof(save));
		scanf("%*c");
		if ( save == 'Y' || save=='y' ) {	
			gotoxy(12, 21);  printf("랭킹을 저장할 이니셜을 입력하세요");
			gotoxy(12, 22); printf("영어, 3글자까지 가능) >> ");
			//scanf_s("%[^/n]s", rank[SIZE_OF_RANK - 1].name, sizeof(rank[SIZE_OF_RANK - 1].name));
			fgets(rank[SIZE_OF_RANK - 1].name, sizeof(rank[SIZE_OF_RANK - 1].name), stdin);
			if (strlen(rank[SIZE_OF_RANK - 1].name) > 0 && strlen(rank[SIZE_OF_RANK - 1].name) < 4) {
				gotoxy(20, 20); printf("랭킹을 저장하였습니다.");
				break;
			}
			else {
				gotoxy(20, 20); printf("3글자까지 가능합니다.");
			}
		}
		else if (save == 'N' || save == 'n') {
			gotoxy(20, 20);  printf("랭킹을 저장하지 않습니다.");
			delay(500);
			rank[SIZE_OF_RANK - 1].end = 0;
			break;
		}
		else {
			gotoxy(20, 20);  printf("Y나 N을 입력하셔야합니다.");		//다른문자 입력하면 다시랭킹저장 물어봄
		}
		delay(500);
	}
	rankSort();			//랭킹정렬
	inputRank();
}

void inputRank() {
	FILE *file_pointer;
	file_pointer = fopen("Ranking.txt", "wt");
	for (int i = 0; i < sizeof(rank)/sizeof(rank[0]); i++) {
		if (rank[i].end == 0) {
			fprintf(file_pointer, "--- 0 \n");
		}
		else {
			fprintf(file_pointer, "%4s%d \n", rank[i].name, rank[i].end);
		}
	}
	fclose(file_pointer);
}

void outputRank() {				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@쓰레기값
	FILE *file_pointer;

	file_pointer = fopen("Ranking.txt", "rt");

	if (file_pointer == NULL) {								//오류 or 파일 없을시 새로 생성 
		file_pointer = fopen("Ranking.txt", "a");
		fclose(file_pointer);
		return;
	}
	for (int i = 0; i < sizeof(rank) / sizeof(rank[0]); i++) {
		fscanf(file_pointer, "%[^\n]4s%d\n", &rank[i].name, &rank[i].end);
	}
	fclose(file_pointer);
}

void rankSort() {
	struct _rank temp = { NULL, 0 };
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
			gotoxy(12, i + 5); printf("%2d위   %4s %6d초\n", i + 1, &rank[i].name, rank[i].end);
		}
		else if (rank[i].end != 0) {
			gotoxy(12, i + 5); printf("%2d위   %4s %6d초         + %4d \n", i + 1, &rank[i].name, rank[i].end, rank[i - 1].end - rank[i].end);
		}
		else {
			gotoxy(12, i + 5); printf("%2d위   %4s %6d초\n", i + 1, &rank[i].name, rank[i].end);
		}
	}
	gotoxy(4, 25);  printf("-------------------------------------------------------\n");
	system("pause>nul");
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
	//gotoxy(18, 7); printf("■");
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


	gotoxy(2, 26);
}








void delay(clock_t n)					//printframe 딜레이
{
	clock_t start = clock();
	while (clock() - start < n);
}
