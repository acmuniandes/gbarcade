#include <gb/gb.h> 
#include "pong.c"
#include "breakout.c"
#include "asteroids.c"
#include "titlescreen.c"


void game();
void clearScreen();


void main(){
	loadTitle();
}


void clearScreen(){
	int i;
     		for (i = 0; i < 32; i++){
				printf("\n");
			}
}