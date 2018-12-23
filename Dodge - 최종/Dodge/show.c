#include "show.h"

struct _rank rank[SIZE_OF_RANK] = { "", 0 };		//��ŷ����ü ����, �ʱ�ȭ
struct _select menuXY;		//�޴����� ����ü
struct _select yesnoXY;		//��ŷ���� Y N ���� ����ü
struct _select alphaXY;		//�г��Ӽ��ñ���ü
int start, timeEnd, bulletTimeEnd;		//�ð�����
int temp = 0;		//while�� �ݺ�Ƚ��
int save = 0;			//��ŷ���庯�� 0->����  1->�������


//���ӽ���
void menu() {
	outputRank();
	playMain();
	menuXY.x = 22;
	menuXY.y = 17;
	while (1) {
		int num = 0;		//�޴�����

		printFrame();
		printGameName();
		gotoxy(22, 16); printf("<<�޴��� �����ϼ���>>");
		gotoxy(22, 17);  printf("1");
		gotoxy(26, 17);  printf("���ӽ���");
		gotoxy(22, 18);  printf("2");
		gotoxy(26, 18);  printf("��ŷ");
		gotoxy(22, 19);  printf("3");
		gotoxy(26, 19);  printf("����");

		gotoxy(4, 31); printf("<< ���� 1��    %3s  %6d >>", rank[0].name, rank[0].end);
		selectMenu();
	}//while
}

void selectMenu() {
	gotoxy(menuXY.x, menuXY.y);  printf("��");
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
				gotoxy(menuXY.x, menuXY.y);  printf("��");
			}		//����Ű ��
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
				gotoxy(menuXY.x, menuXY.y);	 printf("��");
			}	  //����Ű ��
		}	//if ����Ű �Ʒ� ��
		if (key == 13) {
			key = _getch();
			frameMove();
			system("cls");
			if (menuXY.y == 17) {
				gameStart();
				system("cls");
				frameMove();
				playMain();
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
		}		//if �����Է�
	}	//if Ű�� �Է�������
}

void gameStart() {
	struct _bullet* bullet = malloc(sizeof(struct _bullet)*THE_NUMBER_OF_BULLETS);
	struct _bullet bu[THE_NUMBER_OF_BULLETS];
	*bullet = bu[THE_NUMBER_OF_BULLETS];

	printFrame();
	playBgm();
	gotoxy(4, 31); printf("<< ���� 1��    %3s  %6d�� >>", rank[0].name, rank[0].end);
	createValue(bullet); // user�� bullet�� �ʱ�ȭ
	firstPrintUser();
	save = 0;		//save�� �ʱ�ȭ
	gotoxy(14, 9); printf("<<����Ű�� ����Ͽ� �Ѿ��� ���ϼ���>>");
	gotoxy(15, 11);  printf("<< �����Ϸ��� �ƹ�Ű�� �������� >>");
	system("pause>null");
	gotoxy(14, 9); printf("                                     ");
	gotoxy(15, 11); printf("                                  ");					//���� ���� �����
	start = clock();		//���ӽ��۽ð�

	while (1) {
		if (clock() - start == rank[0].end) {
			gotoxy(4, 31); printf("                           ");
			gotoxy(4, 31); printf("NEW RECORD!!");
		}

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
	free(bullet);
}


//���ӱ���
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
		playDestroy();
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
		playClear();
		return 1;
	}
	else {
		return 0;
	}
}

boolean gameOver(struct _bullet* bullet) {
	if (checkCrush(bullet) == 1 || disappearBullets(bullet) == 1 ) { // user�� bullet�� �� �ϳ��� �ε����� break;, bullet���� ��� ���ϸ� break;
		addRank(bullet);
		temp = 0;
		return TRUE;
	}
	return FALSE;
}


//��ŷ
void addRank(struct _bullet* bullet) {
	
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

		selectYesNo();

		if (save == 0) {
			selectName();
			gotoxy(34,28); printf("��ŷ����Ϸ�");
			gotoxy(38, 31); printf("�ƹ�Ű�� ��������");
			_getch();
			break;
		}

		else {
			gotoxy(34, 28);  printf("��ŷ�� �������� �ʽ��ϴ�.");
			gotoxy(38, 31); printf("�ƹ�Ű�� ��������");
			rank[SIZE_OF_RANK - 1].end = 0;
			_getch();
			break;
		}//else
	}//while
	rankSort();			//��ŷ����
	inputRank();
}

void inputRank() {
#pragma pack(push, 1)		//1����Ʈũ��� ����
	FILE *file_pointer;

	file_pointer = fopen("Ranking.txt", "wt");
	for (int i = 0; i < sizeof(rank) / sizeof(rank[0]); i++) {
		if (rank[i].end == 0) {
			continue;
		}
		fwrite(&rank[i], sizeof(rank) / sizeof(rank[0]), 1 , file_pointer);
	}
	fclose(file_pointer);
#pragma pack(pop)			//�⺻������ ����
}	

void outputRank() {
#pragma pack(push, 1)
	FILE *file_pointer;

	file_pointer = fopen("Ranking.txt", "rt");
	if (file_pointer == NULL) {								//���� or ���� ������ ���� ���� 
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
	for (int i = 0; i < sizeof(rank)/sizeof(rank[0]); i++) {				//�����Ʈ
		for (int j = 0; (unsigned)j < (sizeof(rank) / sizeof(rank[0]))-i-1; j++) {
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
			gotoxy(12, i + 5); printf("%2d��    %3s      %6d��", i + 1, &rank[i].name, rank[i].end);
		}
		else if (rank[i].end != 0) {
			gotoxy(12, i + 5); printf("%2d��    %3s      %6d��    + %6d��", i + 1, &rank[i].name, rank[i].end, rank[i - 1].end - rank[i].end);
		}
		else {
			gotoxy(12, i + 5); printf("%2d��    %3s      %6d��", i + 1, &rank[i].name, rank[i].end);
		}
	}
	gotoxy(4, 25);  printf("-------------------------------------------------------\n");
	gotoxy(38, 31); printf("�ƹ�Ű�� ��������");
	system("pause>nul");
}

void selectYesNo() {
	gotoxy(4, 31); printf("<< ���� 1��    %3s  %6d�� >>", rank[0].name, rank[0].end);
	gotoxy(20, 18); printf(" ���� ����   %6d�� ", rank[20].end);
	gotoxy(20, 19);  printf("��ŷ�� �����Ͻðڽ��ϱ�?");
	gotoxy(25, 20); printf("Y  ");
	gotoxy(28, 20); printf("��");
	gotoxy(30, 20); printf("   N");
	yesnoXY.x = 28;
	yesnoXY.y = 20;
	while (1) {
		if (_kbhit()) {
			int key = _getch();
			if (key == 224) {
				key = _getch();
				if (key == 75) { //��
					if (yesnoXY.x == 28)
						alphaXY.x;
					else {
						gotoxy(yesnoXY.x, yesnoXY.y); printf("  ");
						yesnoXY.x -= 2;
					}
					gotoxy(yesnoXY.x, yesnoXY.y); printf("��");
				}
				else if (key == 77) { //��
					if (yesnoXY.x == 30)
						yesnoXY.x;
					else {
						gotoxy(yesnoXY.x, yesnoXY.y); printf("  ");
						yesnoXY.x += 2;
					}
					gotoxy(yesnoXY.x, yesnoXY.y); printf("��");
				}
				playEnter();
			}		//if ����Ű
			if (key == 13) {
				key = _getch();
				if (yesnoXY.x == 28) {
					save;
					break;
				}
				else {
					save++;
					break;
				}
			}		//if ����
		}		//if kbhit()
	}//while
}

void selectName() {
	alphaXY.x = 9;
	alphaXY.y = 21;
	char saveName[4] = "";			//�г��ӹ迭 ����, �ʱ�ȭ
	int saveNameLen = 0;
	
	//���ĺ� ���
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 9; j++) {
			gotoxy(9 + (j * 5), 21 + (i * 2)); printf("��%c", 'A' + (i * 9) + j);
			if (i == 2 && j == 8) {
				gotoxy(9 + (j * 5), 21 + (i * 2)); printf("��DEL");		//Z���� ����ϰ� ���� �� DEL
			}
		}
	}
	gotoxy(9, 27); printf("�г���>> ");
	gotoxy(alphaXY.x, alphaXY.y); printf("��");

	while (1) {
		if (_kbhit()) {
			int key = _getch();
			if (key == 224) {
				key = _getch();
				if (key == 72) {	//��
					if (alphaXY.y == 21)
						alphaXY.y;
					else {
						gotoxy(alphaXY.x, alphaXY.y); printf("��");
						alphaXY.y -= 2;
					}
				}
				else if (key == 80) { //��
					if (alphaXY.y == 25)
						alphaXY.y;
					else {
						gotoxy(alphaXY.x, alphaXY.y); printf("��");
						alphaXY.y += 2;
					}
				}
				else if (key == 75) { //��
					if (alphaXY.x == 9)
						alphaXY.x;
					else {
						gotoxy(alphaXY.x, alphaXY.y); printf("��");
						alphaXY.x -= 5;
					}
				}
				else if (key == 77) { //��
					if (alphaXY.x == 49)
						alphaXY.x;
					else {
						gotoxy(alphaXY.x, alphaXY.y); printf("��");
						alphaXY.x += 5;
					}
				}
				gotoxy(alphaXY.x, alphaXY.y); printf("��");
				playEnter();
			}	//if ����Ű �Է�

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
				}	//del���� ����
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
						strcpy(rank[SIZE_OF_RANK - 1].name, saveName);		//��ŷ �������� �̸�����
						break;
					}
					saveNameLen++;
				}
			}//if �����Է�
		}//if _kbhit()
	}//while
}