#include <stdio.h>
#include <conio.h>
#include "Snake.h"

int main(void){
	POINT p;
	int i;
	char c;
	
	makeBorder();
	initSnake();
	makeFood();
	thr[0] = CreateThread(NULL,0,snakeRun,NULL,NULL,&thrid);
	while (HandleKeyEvent());
	return 0;
}