#ifndef __EVENT_H__
#define __EVENT_H__

#include "show.h"
#include <time.h>
#include <mmsystem.h>							//sound
#pragma comment(lib,"winmm.lib")		//sound
//PlaySound(TEXT("�����̸�.wav"), NULL, �ɼ�(SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT));		sound�Լ� ���¹��(���� �ɼ��� ����� �ɼ�)


//GUI
void printFrame();				// �׵θ� ����Լ� 
void frameMove();				//�׵θ� �̵� ����Լ�
void printGameName();		//�����̸� ���
void printGameOver();		//���ӿ��� ���
void printGameSet();			//���Ӽ� ���
void printEnd();					//���� ���


void delay(clock_t n);			//����

#endif