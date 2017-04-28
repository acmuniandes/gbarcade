#include <stdio.h>
#include <gb/gb.h>

#include "ball.c"
#include "paddleB.c"

void loadSprites();
void checkControls();

//boolean implementation
typedef int bool;
#define true 1
#define false 0

UINT8 char balls[4];//ball[0]X position// ball[1]Y position //ball[2]X velocity// ball[3]ball[2]Y velocity//
unsigned char player=50; //players X position
UINT8 score=0;//players score
bool playing=true;

void main(){
	loadSprites();
	restart:
		while(playing==true){
			checkControls();
		}
		goto restart;
}
void loadSprites(){
	SPRITES_8x8;
	set_sprite_data(0,2,paddle);
	set_sprite_data(2,2,ball);
	set_sprite_tile(0,0);
	set_sprite_tile(1,1);
	set_sprite_tile(2,2);
	
	
	move_sprite(0, player, 140);
	move_sprite(1, player+8, 140);
	DISPLAY_ON;
	SHOW_SPRITES;
}
void checkControls(){
	
	
}