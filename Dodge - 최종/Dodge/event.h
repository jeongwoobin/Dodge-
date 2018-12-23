#ifndef __EVENT_H__
#define __EVENT_H__
//GUI, SOUND, delay�Լ�

#include "show.h"
#include <time.h>
#include <Windows.h>
#include <MMSystem.h>
#pragma comment (lib, "winmm.lib")


//GUI
void printFrame();				// �׵θ� ����Լ� 
void frameMove();				//�׵θ� �̵� ����Լ�
void printGameName();		//�����̸� ���
void printGameOver();		//���ӿ��� ���
void printGameSet();			//���Ӽ� ���
void printEnd();					//���� ���

//SOUND
void playDestroy();
void playClear();
void playBgm();
void playMain();
void playEnter();

void delay(clock_t n);			//����

#endif