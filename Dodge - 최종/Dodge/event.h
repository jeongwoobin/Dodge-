#ifndef __EVENT_H__
#define __EVENT_H__
//GUI, SOUND, delay함수

#include "show.h"
#include <time.h>
#include <Windows.h>
#include <MMSystem.h>
#pragma comment (lib, "winmm.lib")


//GUI
void printFrame();				// 테두리 출력함수 
void frameMove();				//테두리 이동 출력함수
void printGameName();		//게임이름 출력
void printGameOver();		//게임오버 출력
void printGameSet();			//게임셋 출력
void printEnd();					//종료 출력

//SOUND
void playDestroy();
void playClear();
void playBgm();
void playMain();
void playEnter();

void delay(clock_t n);			//지연

#endif