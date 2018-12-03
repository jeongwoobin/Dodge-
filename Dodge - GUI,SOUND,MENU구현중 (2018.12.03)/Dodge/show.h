#ifndef __SHOW_H__
#define __SHOW_H__

#define _CRT_SECURE_NO_WARNINGS

#include "console.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include <mmsystem.h>							//sound
#pragma comment(lib,"winmm.lib")		//sound
//PlaySound(TEXT("�����̸�.wav"), NULL, �ɼ�(SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT));		sound�Լ� ���¹��(���� �ɼ��� ����� �ɼ�)



#define THE_NUMBER_OF_BULLETS 10			//�Ѿ� ����
#define UPDATE_SPEED_OF_BULLET 70					//�Ѿ˼ӵ�-�������� ����
#define SIZE_OF_RANK 21								//��ũ�迭 ũ��

struct _menu {
	int x, y;
}menuXY;

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
	char name[4];
	int end;
};

void menu();

//gameStart�� ���Ǵ� �Լ���
void gameStart();
void createValue(struct _bullet* bullet); // ���� �� ���� �ʱ�ȭ�ϴ� �Լ�
int checkCrush(struct _bullet* bullet); // �Ѿ˰� ���� �浹�� ���ӿ��� �Լ�
int disappearBullets(struct _bullet* bullet); // �Ѿ��� ��� ���� �� ���ӿ��� �Լ�
void printFrame(); // �׵θ� ��� �Լ� 
void firstPrintUser(); //���� ����ĳ���� ��� �Լ�
void printBullets(struct _bullet* bullet); // �Ѿ� ��� �Լ�
void updateUser(); // ����Ű ���� �� ����ĳ���� ������ �Լ�
void updateBullets(struct _bullet* bullet); // �Ѿ� ������ �Լ�
boolean gameOver(struct _bullet* bullet);	//������������ ������ ���ӿ����Լ�

//��ŷ�Լ�
void inputRank();		//��ŷ ���Ͽ� ����
void outputRank();			//��ŷ ���Ͽ��� �ҷ�����
void printRank();		//��ŷ ���
void rankSort();			//��ŷ ����
void addRank();			//

//GUI
void frameMove();	//ȭ�� GUI������Ʈ
void printGameName();	//�����̸�
void printGameOver();
void printEnd();

void delay(clock_t n);

#endif