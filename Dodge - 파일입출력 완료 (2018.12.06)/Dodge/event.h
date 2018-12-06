#ifndef __EVENT_H__
#define __EVENT_H__

#include "show.h"
#include <time.h>
#include <mmsystem.h>							//sound
#pragma comment(lib,"winmm.lib")		//sound
//PlaySound(TEXT("파일이름.wav"), NULL, 옵션(SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT));		sound함수 쓰는방법(현재 옵션은 배경음 옵션)


//GUI
void printFrame();				// 테두리 출력함수 
void frameMove();				//테두리 이동 출력함수
void printGameName();		//게임이름 출력
void printGameOver();		//게임오버 출력
void printGameSet();			//게임셋 출력
void printEnd();					//종료 출력


void delay(clock_t n);			//지연

#endif