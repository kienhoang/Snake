#ifndef _CONSOLE_H
#define _CONSOLE_H

#include <Windows.h>
#include <conio.h>
const HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

void initConsoleInfo();
void setCursorPoint(POINT p);
POINT getCursorPoint(void);
void moveCursor(int hor, int ver);
int getKey(void);
char getcharAt(POINT p);
void putCharAt(POINT p, char c);

#endif //_CONSOLE_H