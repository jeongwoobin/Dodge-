#include "show.h"
//�޴�
//��ŷ(�����)�ý���
//����(�浹��, ���ӽ���ī��Ʈ)
//��������� ��� END

//@@@@@@@@@@@@@@@@@@@���� : ���� �ϴٺ��� �Ѿ����Ѱ�������->��������


int start, end;		//�ð�����
int temp = 0;		//while�� �ݺ�Ƚ��

void menu() {
	//�����̸� ��� ����
	while (1) {
		int num = 0;		//�޴�����

		printFrame();
		gotoxy(22, 13); printf("<<�޴��� �����ϼ���>>");
		gotoxy(22, 14);  printf("1.  ���ӽ���\n");
		gotoxy(22, 15);  printf("2.  ��ŷ\n");
		gotoxy(22, 16);  printf("3.  ����\n");
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

	createValue(bullet); // user�� bullet�� �ʱ�ȭ
	firstPrintUser();
	gotoxy(15, 10);  printf("<< �����Ϸ��� �ƹ�Ű�� �������� >>");
	system("pause>nul");
	gotoxy(15, 10); printf("                                  ");
	start = clock();		//���ӽ��۽ð�

	while (1) {
		if (checkCrush(bullet) == 1) { // user�� bullet�� �� �ϳ��� �ε����� break;
			gotoxy(24, 10);  printf("�浹�Ͽ����ϴ�.");
			temp = 0;
			system("pause>nul");
			break;
		}
			
		if (disappearBullets(bullet) == 1) {  // bullet���� ��� �Ҹ�Ǹ� break;
			gotoxy(15, 10);  printf("��� �Ѿ��� ���߽��ϴ�!");
			temp = 0;
			system("pause>nul");
			break;
		}

		end = clock();						//���ݱ��� �帥 �ð����� �Ѿ˵� ���,�̵�
		int rtime = end - start;
		if (rtime % UPDATE_SPEED_OF_BULLET == 1) {	//UPDATE_SPEED_OF_BULLET �ʸ���
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

void createValue(struct _bullet* bullet){
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

void rank() {

}

void frameMove() {
	int upY = 1;
	int downY = 29;
	int leftX = 2;
	int rightX = 58;
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
	}
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
	}
}

