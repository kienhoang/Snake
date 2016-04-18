#include "Snake.h"

POINT * snakeArray = (POINT *)calloc(COLLUMNS*ROWS,sizeof(POINT));
int dir = MOVE_LEFT; 
int leng = 1;
DWORD speed = 200;
POINT food;
BOOL running = TRUE;
BOOL done = TRUE;
BOOL pause = FALSE;
BOOL dead = FALSE;

HANDLE * thr = (HANDLE *)calloc(1, sizeof(HANDLE)); 
DWORD thrid;

void makeFood(void){
	POINT p;
	do{
		p.x = rand() % (COLLUMNS - 2) + 1;
		p.y = rand() % (ROWS - 2) + 1;
	} while(getcharAt(p) !=' ');
	putCharAt(p,FOOD);
	food = p;
}

void makeBorder(void){
	// Draw border
	POINT p;
	int i;
	p.y = 0;
	for (i = 1; i < COLLUMNS - 1; i++){
		p.x = i;
		putCharAt(p,'-', BORDERATT);
	}
	p.y = ROWS - 1;
	for (i = 1; i < COLLUMNS - 1; i++){
		p.x = i;
		putCharAt(p,'-', BORDERATT);
	}
	p.x = 0;
	for (i = 1; i < ROWS - 1; i++){
		p.y = i;
		putCharAt(p,'|',BORDERATT);
	}
	p.x = COLLUMNS - 1;
	for (i = 1; i < ROWS - 1; i++){
		p.y = i;
		putCharAt(p,'|', BORDERATT);
	}

	p.x = 0; p.y = 0;
	putCharAt(p,'+', BORDERATT);
	p.x = 0; p.y = ROWS - 1;
	putCharAt(p,'+', BORDERATT);
	p.x = COLLUMNS - 1; p.y = 0;
	putCharAt(p,'+', BORDERATT);
	p.x = COLLUMNS - 1; p.y = ROWS - 1;
	putCharAt(p,'+', BORDERATT);
}

void moveSnake(void){
	POINT p;
	int i;
	switch(dir){
	case MOVE_TOP:
		{
			// On Move Top
			p.x = snakeArray[0].x;
			p.y = snakeArray[0].y - 1;
			if (getcharAt(p) == FOOD){
				leng++;
				for (i = leng - 1; i > 0; i--){
					snakeArray[i] = snakeArray[i - 1];
					putCharAt(snakeArray[i],BODY);
				}
				snakeArray[0] = p;
				putCharAt(snakeArray[0],HEAD);
				makeFood();
			}else{
				putCharAt(snakeArray[leng -1],' ');
				for (i = leng - 1; i > 0; i--){
					snakeArray[i] = snakeArray[i - 1];
					putCharAt(snakeArray[i],BODY);
				}
				snakeArray[0].y--;
				if (getcharAt(p) == BODY || p.y == 0){
					running = FALSE;
					onDead();
				}
				putCharAt(snakeArray[0],HEAD);
			}
		}
		break;
	case MOVE_BOTTOM: 
		{
			// On Move Bottom
			p.x = snakeArray[0].x;
			p.y = snakeArray[0].y + 1;
			if (getcharAt(p) == FOOD){
				leng++;
				for (i = leng - 1; i > 0; i--){
					snakeArray[i] = snakeArray[i - 1];
					putCharAt(snakeArray[i],BODY);
				}
				snakeArray[0] = p;
				putCharAt(snakeArray[0],HEAD);
				makeFood();
			} else {
				putCharAt(snakeArray[leng -1],' ');
				for (i = leng - 1; i > 0; i--){
					snakeArray[i] = snakeArray[i - 1];
					putCharAt(snakeArray[i],BODY);
				}
				snakeArray[0].y++;
				if (getcharAt(p) == BODY || p.y == ROWS - 1){
					running = FALSE;
					onDead();
				}
				putCharAt(snakeArray[0],HEAD);
			}
		}
		break;
	case MOVE_LEFT:
		{
			// On Move Left
			p.x = snakeArray[0].x - 1;
			p.y = snakeArray[0].y;
			if (getcharAt(p) == FOOD){
				leng++;
				for (i = leng - 1; i > 0; i--){
					snakeArray[i] = snakeArray[i - 1];
					putCharAt(snakeArray[i],BODY);
				}
				snakeArray[0] = p;
				putCharAt(snakeArray[0],HEAD);
				makeFood();
			} else {
				putCharAt(snakeArray[leng -1],' ');
				for (i = leng - 1; i > 0; i--){
					snakeArray[i] = snakeArray[i - 1];
					putCharAt(snakeArray[i],BODY);
				}
				snakeArray[0].x--;
				if (getcharAt(p) == BODY || p.x == 0){
					running = FALSE;
					onDead();
				}
				putCharAt(snakeArray[0],HEAD);
			}
		}
		break;
	case MOVE_RIGHT:
		{
			//On Move Right
			p.x = snakeArray[0].x + 1;
			p.y = snakeArray[0].y;
			if (getcharAt(p) == FOOD){
				leng++;
				for (i = leng - 1; i > 0; i--){
					snakeArray[i] = snakeArray[i - 1];
					putCharAt(snakeArray[i],BODY);
				}
				snakeArray[0] = p;
				putCharAt(snakeArray[0],HEAD);
				makeFood();
			} else {
				putCharAt(snakeArray[leng -1],' ');
				for (i = leng - 1; i > 0; i--){
					snakeArray[i] = snakeArray[i - 1];
					putCharAt(snakeArray[i],BODY);
				}
				snakeArray[0].x++;
				if (getcharAt(p) == BODY|| p.x == COLLUMNS - 1 ){
					running = FALSE;
					onDead();
				}
				putCharAt(snakeArray[0],HEAD);
			}
		}
		break;
	}
}

void initSnake(void){
	POINT p;
	p.x = COLLUMNS/2;
	p.y = ROWS/2;

	putCharAt(p,HEAD);
	snakeArray[0] = p;

	p.x++;
	leng++;
	putCharAt(p,BODY);
	snakeArray[1] = p;

	p.x++;
	leng++;
	putCharAt(p,BODY);
	snakeArray[2] = p;
	//speed = 100;

}

DWORD WINAPI snakeRun(LPVOID){
	while (running && !dead){
		moveSnake();
		Sleep(speed);
		done = TRUE;
	}
	return 0;
}

BOOL HandleKeyEvent(void){
	char c = getKey();
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
		return FALSE;
	}
	return TRUE;
}

void onDead(void){
	dead = TRUE;
	POINT p;
	p.x = (COLLUMNS - strlen("GAME OVER"))/2 - 1;
	p.y = 4*ROWS/5;
	putStrAt(p,"GAME OVER", BORDERATT);
}