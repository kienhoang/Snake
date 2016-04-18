#include "Console.h"

void initConsoleInfo(){
	int i;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	//COLLUMNS = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	//ROWS = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	/*
	consoleArray = (char**)calloc(COLLUMNS,sizeof(char*));
	for (i = 0; i < COLLUMNS; i++){
		consoleArray[i] = (char *)calloc(ROWS,sizeof(char));
	}
	*/
} 

void setCursorPoint(POINT p){
	// Define for Windows
	COORD _p = { p.x, p.y };
	SetConsoleCursorPosition(hOutput,_p);
}

POINT getCursorPoint(void){
	// Define for windows
	POINT p;
	CONSOLE_SCREEN_BUFFER_INFO _p;
	GetConsoleScreenBufferInfo(hOutput,&_p);
	p.x = (LONG)_p.dwCursorPosition.X;
	p.y = (LONG)_p.dwCursorPosition.Y;
	return p;
}

void moveCursor(int hor, int ver){
	POINT p = getCursorPoint();
	if ((p.x + hor) > 0 && (p.y + ver)>0)
	{
		p.x += hor;
		p.y += ver;
	}
	setCursorPoint(p);
}

int getKey(void){
	// Define for Windows
	int key = getch();
	fflush(stdin);
	return key;
}

char getcharAt(POINT p){
	// Define for Windows

	int x = p.x;
	int y = p.y;
	CHAR_INFO ci;
	COORD xy = { 0, 0 }, size = {1, 1};
	SMALL_RECT rect = { x, y, x, y };
	return ReadConsoleOutput(hOutput, &ci, size, xy, &rect )? 
		ci.Char.AsciiChar : '\0';

	//return consoleArray[p.x][p.y];
}

void putCharAt(POINT p, char c, WORD Attributes){
	CHAR_INFO ci;
	ci.Char.AsciiChar = c;
	ci.Char.UnicodeChar = c;
	ci.Attributes = Attributes;
	int x = p.x, y = p.y;
	COORD xy = { 0, 0 }, 
		size = {1, 1};
	SMALL_RECT rect = { x, y, x, y };
	WriteConsoleOutput(hOutput,&ci,size,xy,&rect);
	//consoleArray[p.x][p.y] = c;
}

void putStrAt(POINT p, const char *c, WORD Attributes){
	int i;
	int len = strlen(c);
	for (i = 0; i < len; i++){
		p.x++;
		putCharAt(p,c[i], Attributes);
	}
}