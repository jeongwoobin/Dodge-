#include "show.h"
//�޴�(ȭ��ǥ�̵�����(?))
//��ŷ(�����)�ý���---->>>>@@@@@@@@@@@@@��ŷ ������� ����
//����(�浹��, ���ӽ���ī��Ʈ)
//�����̸����, ����������½� ������ ��� �ִϸ��̼�ȿ��(?)
//GUI, ���� �Լ��� ���� �ҽ����Ϸ� ��Ƴ���
//������ setting�޴�(�Ѿ˼ӵ�, ����)

//@@@@@@@@@@@@@@@@@@�޴� ȭ��ǥ�̵� ������@@@@@@@@@22
//@@@@@@@@@@@@@@@@@@��ȭ��ǥ �Է��ϸ� ���� �Է��ߴ� ������ ����--����(?)    , �̴ϼ��Է¹迭ũ��Ѱ� �Է��ϸ� �и�@@@@@@@@@@@@@@@@2

struct _rank rank[SIZE_OF_RANK] = { " ", 0 };		//��ŷ����ü ����, �ʱ�ȭ
int start, timeEnd, bulletTimeEnd;		//�ð�����
int temp = 0;		//while�� �ݺ�Ƚ��
char num2 = 0;	//���๮�� �������º���

//void selectMenu() {
//	menuXY.x = 21;
//	menuXY.y = 17;		//menuXY �ʱ�ȭ
//	gotoxy(menuXY.x, menuXY.y); printf("��");
//	if(_kbhit()) {
//		int key = _getch();
//		switch (key) {			//72�� 80�� 75�� 77��
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
	//�����̸� ��� ����
	outputRank();
	while (1) {
		int num = 0;		//�޴�����
		printFrame();
		printGameName();
		gotoxy(21, 16); printf("<<�޴��� �����ϼ���>>");
		gotoxy(21, 17);  printf("1  ���ӽ���");	 
		gotoxy(21, 18);  printf("2  ��ŷ");
		gotoxy(21, 19);  printf("3  ����");

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
			printf("�߸��Է��ϼ̽��ϴ�.");
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

	createValue(bullet); // user�� bullet�� �ʱ�ȭ
	firstPrintUser();
	gotoxy(15, 10);  printf("<< �����Ϸ��� �ƹ�Ű�� �������� >>");
	system("pause>nul");
	gotoxy(15, 10); printf("                                  ");
	start = clock();		//���ӽ��۽ð�

	while (1) {
		if (gameOver(bullet) == TRUE) {			//�浹�ϰų� ��� ���ϰų�
			break;
		}

		bulletTimeEnd = clock();						//���ݱ��� �帥 �ð����� �Ѿ˵� ���,�̵�
		int bulletTime = bulletTimeEnd - start;
		if (bulletTime % UPDATE_SPEED_OF_BULLET == 1) {	//UPDATE_SPEED_OF_BULLET �ʸ���
			updateBullets(bullet);
			printBullets(bullet);
		}//if

		updateUser();
	}//while
}

void printFrame() {
	for (int i = 2; i < 60; i++) {		//2~58
		gotoxy(i++, 0);
		printf("��");
	}
	for (int i = 1; i < 30; i++) {		//1~29
		gotoxy(0, i);
		printf("��");
	}
	for (int i = 2; i < 60; i++) {
		gotoxy(i++, 30);
		printf("��");
	}
	for (int i = 1; i < 30; i++) {
		gotoxy(60, i);
		printf("��");
	}
}

void firstPrintUser() {
	gotoxy(user.x, user.y); 	printf("��");
}

void printBullets(struct _bullet* bullet) {
	for (int i = 0; i < THE_NUMBER_OF_BULLETS; i++) {
		if (bullet[i].isPrint == 1) {
			switch (bullet[i].direction) {			//���� �Ѿ���ġ�� �̵��Ͽ� ����� �ٽ� ����Ʈ
			case 1:
				if (bullet[i].x == 2 || bullet[i].y == 29) {				//���� ������
					gotoxy(bullet[i].x, bullet[i].y);
					printf("  ");
					bullet[i].isPrint = 2;										//�Ѿ� �Ҹ�
					break;
				}
				else {
					gotoxy(bullet[i].x, bullet[i].y); printf("  ");		//�����Ѿ������
					bullet[i].x -= 2;
					bullet[i].y++;
					gotoxy(bullet[i].x, bullet[i].y); printf("��");		//�̵��ؼ� ����Ʈ
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
					gotoxy(bullet[i].x, bullet[i].y); printf("��");
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
					gotoxy(bullet[i].x, bullet[i].y); printf("��");
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
					gotoxy(bullet[i].x, bullet[i].y); printf("��");
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
					gotoxy(bullet[i].x, bullet[i].y); printf("��");
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
					gotoxy(bullet[i].x, bullet[i].y); printf("��");
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
					gotoxy(bullet[i].x, bullet[i].y); printf("��");
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
					gotoxy(bullet[i].x, bullet[i].y); printf("��");
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
			if (key == 72) {	//��
				if (user.y == 1)
					user.y;
				else {
					gotoxy(user.x, user.y); printf("  ");
					user.y--;
				}
			}
			else if (key == 80) { //��
				if (user.y == 29)
					user.y;
				else {
					gotoxy(user.x, user.y); printf("  ");
					user.y++;
				}
			}
			else if (key == 75) { //��
				if (user.x == 2)
					user.x;
				else {
					gotoxy(user.x, user.y); printf("  ");
					user.x -= 2;
				}
			}
			else if (key == 77) { //��
				if (user.x == 58)
					user.x;
				else {
					gotoxy(user.x, user.y); printf("  ");
					user.x += 2;
				}
			}
		}//switch

		gotoxy(user.x, user.y); printf("��");
	}//kbhit
}

void updateBullets(struct _bullet* bullet) {
	if (temp < THE_NUMBER_OF_BULLETS) {		//while�� �ѹ� ��°���� �Ѿ� �ϳ� �����Ű�� THE_NUMBER_OF_BULLETS�� temp�� ��������(�Ѿ��� ��� �����ϸ�) ���̻� �Ѿ� ����x
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

		bullet[i].startingLocation = rand() % 4; // �����¿� �� �ϳ� ����
		switch (bullet[i].startingLocation) {
		case 0: // ��
			bullet[i].x = (rand() % 29) * 2 + 2; // 2 ~ 58 �߿��� ¦��
			bullet[i].y = 1;
			bullet[i].direction = rand() % 3 + 1; // ���� 1, 2, 3�߿� �Ҵ�
			break;
		case 1: // ��
			bullet[i].x = (rand() % 29) * 2 + 2; // 2 ~ 58 �߿��� ¦��
			bullet[i].y = 29;
			bullet[i].direction = rand() % 3 + 7; // ���� 7, 8 ,9 �߿� �Ҵ�
			break;
		case 2: // ��
			bullet[i].x = 2;
			bullet[i].y = rand() % 29 + 1; // 1 ~ 29
			bullet[i].direction = (rand() % 3 + 1) * 3; // ���� 3, 6, 9 �߿� �Ҵ�
			break;
		case 3: // ��
			bullet[i].x = 58;
			bullet[i].y = rand() % 29 + 1; // 1 ~ 29
			bullet[i].direction = (rand() % 3 + 1) * 3 - 2; // ���� 1, 4, 7 �߿� �Ҵ�
			break;
		}//switch
	}//for
}

int checkCrush(struct _bullet* bullet) {
	int count = 0; // x, y ��ġ�� ���� +1�ؼ� +2�Ǹ� ���� ��ħ

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
	if (checkCrush(bullet) == 1 || disappearBullets(bullet) == 1 ) { // user�� bullet�� �� �ϳ��� �ε����� break;, bullet���� ��� ���ϸ� break;
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
		gotoxy(12, 19);  printf("��ŷ�� �����Ͻðڽ��ϱ�? (Y/N)>>"); 	scanf_s("%c", &save, sizeof(save));
		scanf("%*c");
		if ( save == 'Y' || save=='y' ) {	
			gotoxy(12, 21);  printf("��ŷ�� ������ �̴ϼ��� �Է��ϼ���");
			gotoxy(12, 22); printf("����, 3���ڱ��� ����) >> ");
			//scanf_s("%[^/n]s", rank[SIZE_OF_RANK - 1].name, sizeof(rank[SIZE_OF_RANK - 1].name));
			fgets(rank[SIZE_OF_RANK - 1].name, sizeof(rank[SIZE_OF_RANK - 1].name), stdin);
			if (strlen(rank[SIZE_OF_RANK - 1].name) > 0 && strlen(rank[SIZE_OF_RANK - 1].name) < 4) {
				gotoxy(20, 20); printf("��ŷ�� �����Ͽ����ϴ�.");
				break;
			}
			else {
				gotoxy(20, 20); printf("3���ڱ��� �����մϴ�.");
			}
		}
		else if (save == 'N' || save == 'n') {
			gotoxy(20, 20);  printf("��ŷ�� �������� �ʽ��ϴ�.");
			delay(500);
			rank[SIZE_OF_RANK - 1].end = 0;
			break;
		}
		else {
			gotoxy(20, 20);  printf("Y�� N�� �Է��ϼž��մϴ�.");		//�ٸ����� �Է��ϸ� �ٽ÷�ŷ���� ���
		}
		delay(500);
	}
	rankSort();			//��ŷ����
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

void outputRank() {				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@�����Ⱚ
	FILE *file_pointer;

	file_pointer = fopen("Ranking.txt", "rt");

	if (file_pointer == NULL) {								//���� or ���� ������ ���� ���� 
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
	for (int i = 0; i < sizeof(rank)/sizeof(rank[0]); i++) {				//�����Ʈ
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
	gotoxy(4, 4);  printf("-------------------------��ŷ-------------------------");
	for (int i = 0; i < sizeof(rank) / sizeof(rank[0]) - 1; i++) {
		if (rank[i].name == NULL)
			break;
		if (i == 0) {
			gotoxy(12, i + 5); printf("%2d��   %4s %6d��\n", i + 1, &rank[i].name, rank[i].end);
		}
		else if (rank[i].end != 0) {
			gotoxy(12, i + 5); printf("%2d��   %4s %6d��         + %4d \n", i + 1, &rank[i].name, rank[i].end, rank[i - 1].end - rank[i].end);
		}
		else {
			gotoxy(12, i + 5); printf("%2d��   %4s %6d��\n", i + 1, &rank[i].name, rank[i].end);
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
	for (int i = 0; i < 15; i++) {			//�׳� �ݺ�		0~62    0~31			��� 30,15
		for (int x = (i * 2) + 4; x < 58 - (i * 2); x++) {		//��
			gotoxy(x++, upY);
			printf("��");
		}
		for (int y = i + 2; y < 29 - i; y++) {		//����
			gotoxy(leftX, y);
			printf("��");
		}
		for (int x = (i * 2) + 4; x < 58 - (i * 2); x++) {		//�Ʒ�
			gotoxy(x++, downY);
			printf("��");
		}
		for (int y = i + 2; y < 29 - i; y++) {		//������
			gotoxy(rightX, y);
			printf("��");
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
	for (int i = 0; i < 15; i++) {			//�׳� �ݺ�		0~62    0~31			��� 30,15
		for (int x = 30 - (i * 2); x < (i * 2) + 32; x++) {		//��
			gotoxy(x++, upY);
			printf("   ");
		}
		for (int y = 15 - i; y < 16 + i; y++) {		//����
			gotoxy(leftX, y);
			printf(" ");
		}
		for (int x = 30 - (i * 2); x < (i * 2) + 32; x++) {		//�Ʒ�
			gotoxy(x++, downY);
			printf("  ");
		}
		for (int y = 15 - i; y < 16 + i; y++) {		//������
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
	gotoxy(8, 5); printf("��");
	gotoxy(10, 5); printf("��");
	gotoxy(12, 5); printf("��");
	gotoxy(8, 6); printf("��");
	gotoxy(14, 6); printf("��");
	gotoxy(8, 7); printf("��");
	gotoxy(14, 7); printf("��");
	gotoxy(8, 8); printf("��");
	gotoxy(14, 8); printf("��");
	gotoxy(8, 9); printf("��");
	gotoxy(10, 9); printf("��");
	gotoxy(12, 9); printf("��");		//D

	gotoxy(20, 5); printf("��");
	gotoxy(22, 5); printf("��");
	gotoxy(18, 6); printf("��");
	gotoxy(24, 6); printf("��");
	gotoxy(18, 7); printf("��");
	gotoxy(24, 7); printf("��");
	gotoxy(18, 8); printf("��");
	gotoxy(24, 8); printf("��");
	gotoxy(20, 9); printf("��");
	gotoxy(22, 9); printf("��");		//O

	gotoxy(28, 5); printf("��");
	gotoxy(30, 5); printf("��");
	gotoxy(32, 5); printf("��");
	gotoxy(28, 6); printf("��");
	gotoxy(34, 6); printf("��");
	gotoxy(28, 7); printf("��");
	gotoxy(34, 7); printf("��");
	gotoxy(28, 8); printf("��");
	gotoxy(34, 8); printf("��");
	gotoxy(28, 9); printf("��");
	gotoxy(30, 9); printf("��");
	gotoxy(32, 9); printf("��");		//D

	gotoxy(40, 5); printf("��");
	gotoxy(42, 5); printf("��");
	gotoxy(38, 6); printf("��");
	gotoxy(38, 7); printf("��");
	gotoxy(42, 7); printf("��");
	gotoxy(44, 7); printf("��");
	gotoxy(38, 8); printf("��");
	gotoxy(44, 8); printf("��");
	gotoxy(40, 9); printf("��");
	gotoxy(42, 9); printf("��");		//G

	gotoxy(48, 5); printf("��");
	gotoxy(50, 5); printf("��");
	gotoxy(52, 5); printf("��");
	gotoxy(48, 6); printf("��");
	gotoxy(48, 7); printf("��");
	gotoxy(50, 7); printf("��");
	gotoxy(52, 7); printf("��");
	gotoxy(48, 8); printf("��");
	gotoxy(48, 9); printf("��");
	gotoxy(50, 9); printf("��");
	gotoxy(52, 9); printf("��");		//E
	
}

void printGameOver() {
	gotoxy(7, 5); printf("��");
	gotoxy(9, 5); printf("��");
	gotoxy(5, 6); printf("��");
	gotoxy(5, 7); printf("��");
	gotoxy(9, 7); printf("��");
	gotoxy(11, 7); printf("��");
	gotoxy(5, 8); printf("��");
	gotoxy(11, 8); printf("��");
	gotoxy(7, 9); printf("��");
	gotoxy(9, 9); printf("��");		//G

	gotoxy(18, 5); printf("��");
	gotoxy(17, 6); printf("��");
	gotoxy(19, 6); printf("��");
	gotoxy(16, 7); printf("��");
	//gotoxy(18, 7); printf("��");
	gotoxy(20, 7); printf("��");
	gotoxy(15, 8); printf("��");
	gotoxy(21, 8); printf("��");
	gotoxy(15, 9); printf("��");
	gotoxy(21, 9); printf("��");		//A

	gotoxy(25, 5); printf("��");
	gotoxy(31, 5); printf("��");
	gotoxy(25, 6); printf("��");
	gotoxy(27, 6); printf("��");
	gotoxy(29, 6); printf("��");
	gotoxy(31, 6); printf("��");
	gotoxy(25, 7); printf("��");
	gotoxy(28, 7); printf("��");
	gotoxy(31, 7); printf("��");
	gotoxy(25, 8); printf("��");
	gotoxy(31, 8); printf("��");
	gotoxy(25, 9); printf("��");
	gotoxy(31, 9); printf("��");		//M

	gotoxy(35, 5); printf("��");
	gotoxy(37, 5); printf("��");
	gotoxy(39, 5); printf("��");
	gotoxy(35, 6); printf("��");
	gotoxy(35, 7); printf("��");
	gotoxy(37, 7); printf("��");
	gotoxy(39, 7); printf("��");
	gotoxy(35, 8); printf("��");
	gotoxy(35, 9); printf("��");
	gotoxy(37, 9); printf("��");
	gotoxy(39, 9); printf("��");		//E

	gotoxy(24, 12); printf("��");
	gotoxy(26, 12); printf("��");
	gotoxy(22, 13); printf("��");
	gotoxy(28, 13); printf("��");
	gotoxy(22, 14); printf("��");
	gotoxy(28, 14); printf("��");
	gotoxy(22, 15); printf("��");
	gotoxy(28, 15); printf("��");
	gotoxy(24, 16); printf("��");
	gotoxy(26, 16); printf("��");		//O

	gotoxy(32, 12); printf("��");
	gotoxy(38, 12); printf("��");
	gotoxy(32, 13); printf("��");
	gotoxy(38, 13); printf("��");
	gotoxy(33, 14); printf("��");
	gotoxy(37, 14); printf("��");
	gotoxy(34, 15); printf("��");
	gotoxy(36, 15); printf("��");
	gotoxy(35, 16); printf("��");		//V

	gotoxy(42, 12); printf("��");
	gotoxy(44, 12); printf("��");
	gotoxy(46, 12); printf("��");
	gotoxy(42, 13); printf("��");
	gotoxy(42, 14); printf("��");
	gotoxy(44, 14); printf("��");
	gotoxy(46, 14); printf("��");
	gotoxy(42, 15); printf("��");
	gotoxy(42, 16); printf("��");
	gotoxy(44, 16); printf("��");
	gotoxy(46, 16); printf("��");		//E

	gotoxy(50, 12); printf("��");
	gotoxy(52, 12); printf("��");
	gotoxy(54, 12); printf("��");
	gotoxy(50, 13); printf("��");
	gotoxy(55, 13); printf("��");
	gotoxy(50, 14); printf("��");
	gotoxy(52, 14); printf("��");
	gotoxy(54, 14); printf("��");
	gotoxy(50, 15); printf("��");
	gotoxy(55, 15); printf("��");
	gotoxy(50, 16); printf("��");
	gotoxy(55, 16); printf("��");		//R
}

void printEnd() {
	gotoxy(20, 13); printf("��");
	gotoxy(22, 13); printf("��");
	gotoxy(24, 13); printf("��");
	gotoxy(20, 14); printf("��");
	gotoxy(20, 15); printf("��");
	gotoxy(22, 15); printf("��");
	gotoxy(24, 15); printf("��");
	gotoxy(20, 16); printf("��");
	gotoxy(20, 17); printf("��");
	gotoxy(22, 17); printf("��");
	gotoxy(24, 17); printf("��");		//E

	gotoxy(28, 13); printf("��");
	gotoxy(34, 13); printf("��");
	gotoxy(28, 14); printf("��");
	gotoxy(30, 14); printf("��");
	gotoxy(34, 14); printf("��");
	gotoxy(28, 15); printf("��");
	gotoxy(31, 15); printf("��");
	gotoxy(34, 15); printf("��");
	gotoxy(28, 16); printf("��");
	gotoxy(32, 16); printf("��");
	gotoxy(34, 16); printf("��");
	gotoxy(28, 17); printf("��");
	gotoxy(34, 17); printf("��");		//N

	gotoxy(38, 13); printf("��");
	gotoxy(40, 13); printf("��");
	gotoxy(42, 13); printf("��");
	gotoxy(38, 14); printf("��");
	gotoxy(44, 14); printf("��");
	gotoxy(38, 15); printf("��");
	gotoxy(44, 15); printf("��");
	gotoxy(38, 16); printf("��");
	gotoxy(44, 16); printf("��");
	gotoxy(38, 17); printf("��");
	gotoxy(40, 17); printf("��");
	gotoxy(42, 17); printf("��");		//D


	gotoxy(2, 26);
}








void delay(clock_t n)					//printframe ������
{
	clock_t start = clock();
	while (clock() - start < n);
}
