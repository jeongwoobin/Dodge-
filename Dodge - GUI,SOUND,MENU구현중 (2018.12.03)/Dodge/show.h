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
//PlaySound(TEXT("파일이름.wav"), NULL, 옵션(SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT));		sound함수 쓰는방법(현재 옵션은 배경음 옵션)



#define THE_NUMBER_OF_BULLETS 10			//총알 갯수
#define UPDATE_SPEED_OF_BULLET 70					//총알속도-낮을수록 빠름
#define SIZE_OF_RANK 21								//랭크배열 크기

struct _menu {
	int x, y;
}menuXY;

struct _user {
	int x, y;
	int isCrush; // 충돌하면 1, 아니면 0
	int score;
} user;

struct _bullet {
	int x, y;
	int isPrint; // 출발 전 0, 진행 중 1, 소멸 2
	int startingLocation; // 출발 위치 // 상 0, 하 1, 좌 2, 우 3
	int direction; // 진행 방향(키패드 숫자 방향대로!)
};

struct _rank {
	char name[4];
	int end;
};

void menu();

//gameStart에 사용되는 함수들
void gameStart();
void createValue(struct _bullet* bullet); // 유저 값 최초 초기화하는 함수
int checkCrush(struct _bullet* bullet); // 총알과 유저 충돌시 게임오버 함수
int disappearBullets(struct _bullet* bullet); // 총알을 모두 피할 시 게임오버 함수
void printFrame(); // 테두리 출력 함수 
void firstPrintUser(); //최초 유저캐릭터 출력 함수
void printBullets(struct _bullet* bullet); // 총알 출력 함수
void updateUser(); // 방향키 누를 때 유저캐릭터 움직임 함수
void updateBullets(struct _bullet* bullet); // 총알 움직임 함수
boolean gameOver(struct _bullet* bullet);	//게임종료조건 충족시 게임오버함수

//랭킹함수
void inputRank();		//랭킹 파일에 저장
void outputRank();			//랭킹 파일에서 불러오기
void printRank();		//랭킹 출력
void rankSort();			//랭킹 정렬
void addRank();			//

//GUI
void frameMove();	//화면 GUI업데이트
void printGameName();	//게임이름
void printGameOver();
void printEnd();

void delay(clock_t n);

#endif