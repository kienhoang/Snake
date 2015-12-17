#include <stdio.h>
#include <conio.h>
#include "Snake.h"

int main(void){
	POINT p;
	int i;
	char c;
	HANDLE thr[1];
	DWORD thrid;

	makeBorder();
	initSnake();
	makeFood();
	thr[0] = CreateThread(NULL,0,snakeRun,NULL,NULL,&thrid);
	
	while (1)
	{
		c = getch();
		fflush(stdin);
		switch(c){
		case KEY_TOP:
			if(dir != MOVE_BOTTOM && done){
				dir = MOVE_TOP;
				done = FALSE;
			}
			break;
		case KEY_BOTTOM:
			if (dir != MOVE_TOP && done && !pause){
				dir = MOVE_BOTTOM;
				done = FALSE;
			}
			break;
		case KEY_LEFT:
			if (dir != MOVE_RIGHT && done && !pause){
				dir = MOVE_LEFT;
				done = FALSE;
			}
			break;
		case KEY_RIGHT:
			if (dir != MOVE_LEFT && done  && !pause){
				dir = MOVE_RIGHT;
				done = FALSE;
			}
			break;
		case KEY_SPACE:
			if (pause){
				running = TRUE;
				thr[0] = CreateThread(NULL,0,snakeRun,NULL,NULL,&thrid);
				pause = FALSE;
			} else {
				running = FALSE;
				CloseHandle(thr[0]);
				pause = TRUE;
			}
			break;
		case KEY_ESC:
			if(!pause){
				CloseHandle(thr[0]);
			}
			exit(0);
		}
	}
	return 0;
}