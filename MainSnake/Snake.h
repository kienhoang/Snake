#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <Windows.h>
#include "Console.h"

#define COLLUMNS 30
#define ROWS 20
#define MOVE_TOP 1
#define MOVE_BOTTOM 2
#define MOVE_LEFT 3
#define MOVE_RIGHT 4
#define KEY_TOP 72
#define KEY_BOTTOM 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27
#define KEY_SPACE 32 
#define HEAD 'O'
#define BODY '*'
#define FOOD '0'
#define BORDERATT 0x0002

extern POINT * snakeArray;
extern int dir; 
extern int leng;
extern DWORD speed ;
extern POINT food;
extern BOOL running;
extern BOOL done;
extern BOOL pause;
extern BOOL dead;
extern HANDLE *thr;
extern DWORD thrid;

void makeFood(void);
void makeBorder(void);
void moveSnake(void);
void initSnake(void);
BOOL HandleKeyEvent(void);
void onDead(void);

DWORD WINAPI snakeRun(LPVOID);

#endif // _SNAKE_H_