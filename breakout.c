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

//functions
//void checkControls();

UINT8 char balls[4];//ball[0]X position// ball[1]Y position //ball[2]X velocity// ball[3]ball[2]Y velocity//
unsigned char player=50; //player's X position
UINT8 score=0;//players score
bool playing=true;

unsigned char countPad=0;

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

void updateSprite(signed char cuanto){

	player+=cuanto;
	move_sprite(0, player, 140);
	move_sprite(1, player+8, 140);
	return;
}

void checkControls(){
	countPad++;
	
	if(countPad==40){
		
        if(joypad()==J_RIGHT ){
			if(player<=144){
                updateSprite(1);
			}else{
			} 
		}
        if(joypad()==J_LEFT ){
			if(player>=14){
                updateSprite(-1);
			}else{
			}
		}
		//moveBall();
		countPad=0;
	
	}
		return;
	
}