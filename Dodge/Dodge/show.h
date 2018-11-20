#ifndef __SHOW_H__
#define __SHOW_H__

#include "console.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define THE_NUMBER_OF_BULLETS 10			//�Ѿ� ����
#define UPDATE_SPEED_OF_BULLET 70					//�Ѿ˼ӵ�-�������� ����

struct _user {
	int x, y;
	int isCrush; // �浹�ϸ� 1, �ƴϸ� 0
	int score;
} user;

struct _bullet {
	int x, y;
	int isPrint; // ��� �� 0, ���� �� 1, �Ҹ� 2
	int startingLocation; // ��� ��ġ // �� 0, �� 1, �� 2, �� 3
	int direction; // ���� ����(Ű�е� ���� ������!)
};

void menu();
void gameStart();
void rank();

//gameStart�� ���Ǵ� �Լ���
void createValue(struct _bullet* bullet); // ���� �� ���� �ʱ�ȭ�ϴ� �Լ�
int checkCrush(struct _bullet* bullet); // �Ѿ˰� ���� �浹�� ���ӿ��� �Լ�
int disappearBullets(struct _bullet* bullet); // �Ѿ��� ��� ���� �� ���ӿ��� �Լ�
void printFrame(); // �׵θ� ��� �Լ� 
void firstPrintUser(); //���� ����ĳ���� ��� �Լ�
void printBullets(struct _bullet* bullet); // �Ѿ� ��� �Լ�
void updateUser(); // ����Ű ���� �� ����ĳ���� ������ �Լ�
void updateBullets(struct _bullet* bullet); // �Ѿ� ������ �Լ�

void frameMove();	//ȭ�� GUI������Ʈ
#endif