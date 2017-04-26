#include <gb/gb.h> 
#include <stdio.h>

#include "ball.c"
#include "paddle.c"

//boolean implementation
typedef int bool;
#define true 1
#define false 0

//functions
void checkControls();
void loadSprites();
void startBall();
void updateSprite(char pad, signed char cuanto);
void moveBall();

//paddle 1 position on Y axis
unsigned char PosPad1=70;

//paddle 2 position on Y axis
unsigned char PosPad2=70;

unsigned char countPad=0;

//ball
unsigned char xBall=80;
unsigned char yBall=72;
signed char xVel;
signed char yVel;
bool newBall;
int count=0;//Delays the ball without halt the whole system

int i;
//Extra
unsigned char score1=0;
unsigned char score2=0;
//pointer to memory address for random number generation 
unsigned char *ptr_div_reg = 0xFF04;
unsigned char randy = *(ptr_div_reg); 

void main(){
	loadSprites();
	restart:
	startBall();
	while(newBall==false){
		checkControls();
		
	}
	goto restart;

}

void loadSprites(){
	SPRITES_8x8;
	//Starting at zero, loads paddle array to memory twice and loads the ball as well
	set_sprite_data(0,2,paddle);
	set_sprite_data(2,4,paddle);
	set_sprite_data(4,4,ball);
	//Setting that sprite we just loaded to tile mem
	set_sprite_tile(0,0);
	set_sprite_tile(1,1);
	set_sprite_tile(2,2);
	set_sprite_tile(3,3);
	//this one is the ball
	set_sprite_tile(4,4);
	//sets pad1(right paddle)
	move_sprite(0, 150, PosPad1);
	move_sprite(1, 150, PosPad1+8);

	//sets pad2(left paddle)
	move_sprite(2, 20, PosPad2);
	move_sprite(3, 20, PosPad2+8);

	//sets ball
	move_sprite(4, xBall, yBall); 
	
	DISPLAY_ON;
	SHOW_SPRITES;
}
void updateSprite(char pad, signed char cuanto){

	if(pad==1){
	PosPad1+=cuanto;
	move_sprite(0, 150, PosPad1);
	move_sprite(1, 150, PosPad1+8);
	}
	if(pad==2){
	PosPad2+=cuanto;
	move_sprite(2, 20, PosPad2);
	move_sprite(3, 20, PosPad2+8);
	}
	return;
}

void moveBall(){
	if(yBall==144||yBall==0){
		yVel=yVel*-1;
	}
	
	if(xBall==0){
		score1++;
		newBall=true;
	}
	if(xBall==160){
		score2++;
		newBall=true;
	}
	count++;
	if(count==40){
	xBall=xBall+xVel;
	yBall=yBall+yVel;
	move_sprite(4, xBall, yBall);
	count=0;
	}
	//collision check
	if(xBall==150 || xBall==151){
		if(yBall>=PosPad1 && yBall<=PosPad1+16){
			xVel=xVel*-1;
		}
		
	}
	  
	
}
void startBall(){
	xBall=80;
	yBall=72;
	move_sprite(4, 80, 72);
	while(count!=8000){
		count++;
	}
	count=0;
	if(score1>=score2){
		xVel=1;
		yVel=0;
	}else {
		xVel=-1;
		yVel=0;
	}
	newBall=false;
}
void checkControls(){
	countPad++;
	if(countPad==30){
			if(joypad()==J_UP ){
			if(PosPad1<=16){
				//delay(5);	
			}else{
				updateSprite(1, -1);
				//delay(5);
			}
		}
			
		
		if(joypad()==J_DOWN){
			if(PosPad1>=144){
				//delay(5);	
			}else{
				updateSprite(1, 1);
				//delay(5);
			}
		}
			
		
		if(joypad()==J_A){
		if(PosPad2>=144){
		//delay(5);	
			}else{
				updateSprite(2, 1);
				//delay(5);
			}
		}

		if(joypad()==J_B){
			if(PosPad2<=16){
				//delay(5);	
			}else{
				updateSprite(2, -1);
				//delay(5);
			}
			
		}
		countPad=0;
	
	}


			moveBall();
			return;
}

		
