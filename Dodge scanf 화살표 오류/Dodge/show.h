#ifndef __SHOW_H__
#define __SHOW_H__

#define _CRT_SECURE_NO_WARNINGS

#include "console.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

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

struct _rank {
	char name[10];
	int end;
};

void menu();
void gameStart();
void inputRank();
void outputRank();

//gameStart�� ���Ǵ� �Լ���
void createValue(struct _bullet* bullet); // ���� �� ���� �ʱ�ȭ�ϴ� �Լ�
int checkCrush(struct _bullet* bullet); // �Ѿ˰� ���� �浹�� ���ӿ��� �Լ�
int disappearBullets(struct _bullet* bullet); // �Ѿ��� ��� ���� �� ���ӿ��� �Լ�
void printFrame(); // �׵θ� ��� �Լ� 
void firstPrintUser(); //���� ����ĳ���� ��� �Լ�
void printBullets(struct _bullet* bullet); // �Ѿ� ��� �Լ�
void updateUser(); // ����Ű ���� �� ����ĳ���� ������ �Լ�
void updateBullets(struct _bullet* bullet); // �Ѿ� ������ �Լ�
boolean gameOver(struct _bullet* bullet);
void rankSort();
void addRank();

void frameMove();	//ȭ�� GUI������Ʈ
void delay(clock_t n);

void Flush_buffer(void);		//��������� �Լ�
#endif