#include <gb/gb.h> 
#include <stdio.h>

#include "ball.c"
#include "paddle.c"

void loadPong();
void loadSprites();
void updateSprite(char pad, signed char cuanto);

//paddle 1 cords
unsigned char PosPad1=70;

//paddle 2 cords
unsigned char PosPad2=70;

//ball
unsigned char xBall;
unsigned char yBall;
unsigned char xVel;
unsigned char yVel;

//Extra
unsigned char score1=0;
unsigned char score2=0;

void main(){
loadPong();
}
void loadSprites(){
	SPRITES_8x16;
	//pad 1
	set_sprite_data(0,4,paddle);
	set_sprite_tile(0,0);
	move_sprite(0, 150, PosPad1);
	//pad 2
	move_sprite(2, 20, PosPad2);
	DISPLAY_ON;
	SHOW_SPRITES;
}
void updateSprite(char pad, signed char cuanto){
	if(pad==1){
	PosPad1+=cuanto;
	move_sprite(0, 150, PosPad1);
	}
	if(pad==2){
	PosPad2+=cuanto;
	move_sprite(2, 20, PosPad2);
	}
	return;
}

void loadPong(){
	loadSprites();
	while(1) {

	switch(joypad()) {
		
		case J_RIGHT :
			delay(5);
			break;
			
		case J_LEFT : 
            delay(5);
			break;
			
		case J_UP :
			if(PosPad1<=16){
				
				delay(5);
				break;	
			}else{
				updateSprite(1, -1);
				delay(5);
				break;
			}
		
		case J_DOWN :
			if(PosPad1>=144){
				delay(5);
				break;	
			}else{
				updateSprite(1, 1);
				delay(5);
				break;
			}
			
		case J_START : 
			break;
			
		case J_SELECT :
			break;
			
		case J_A : 
		if(PosPad2>=144){
		delay(5);
			break;	
			}else{
				updateSprite(2, 1);
				delay(5);
				break;
			}

		case J_B : 
			if(PosPad2<=16){
				delay(5);
			break;	
			}else{
				updateSprite(2, -1);
				delay(5);
				break;
			}
			
		default :
			break;
			
			}
		}
}