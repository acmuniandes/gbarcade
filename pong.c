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
bool collisionCheck(unsigned char x1, unsigned char y1, unsigned char w1, unsigned char h1, unsigned char x2, unsigned char y2, unsigned char w2, unsigned char h2);

//paddle 1 position on Y axis
unsigned char yPad1=70;

//paddle 2 position on Y axis
unsigned char yPad2=70;

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
UINT8 score1=0;
UINT8 score2=0;
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
	move_sprite(0, 150, yPad1);
	move_sprite(1, 150, yPad1+8);

	//sets pad2(left paddle)
	move_sprite(2, 20, yPad2);
	move_sprite(3, 20, yPad2+8);

	//sets ball
	move_sprite(4, xBall, yBall); 
	
	DISPLAY_ON;
	SHOW_SPRITES;
}

bool collisionCheck(unsigned char x1, unsigned char y1, unsigned char w1, unsigned char h1, unsigned char x2, unsigned char y2, unsigned char w2, unsigned char h2){
		if ((x1 < (x2+w2)) && ((x1+w1) > x2) && (y1 < (h2+y2)) && ((y1+h1) > y2)) {
		
		return true;
	
	}else {
		
		return false;
	
}
}

void updateSprite(char pad, signed char cuanto){

	if(pad==1){
	yPad1+=cuanto;
	move_sprite(0, 150, yPad1);
	move_sprite(1, 150, yPad1+8);
	}
	if(pad==2){
	yPad2+=cuanto;
	move_sprite(2, 20, yPad2);
	move_sprite(3, 20, yPad2+8);
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
	if(collisionCheck(150, yPad1, 8,16, xBall, yBall, 8,8)==true || collisionCheck(20, yPad2, 8,16, xBall, yBall, 8,8)==true){
	xVel=xVel*-1;
		if(collisionCheck(150, yPad1, 8,2, xBall, yBall, 8,8)==true|| collisionCheck(20, yPad2, 8,2, xBall, yBall, 8,8)==true){
			if(yVel==0){
				yVel=1;
			}else{
				yVel=yVel*-1;
			}
		}
		
	}

	count++;
	if(countPad==40){
		up:
		countPad++;
		if(countPad!=80){
			goto up;
		}
	xBall=xBall+xVel;
	yBall=yBall+yVel;
	move_sprite(4, xBall, yBall);
	count=0;
	}
	  
	
}
void startBall(){
	xBall=80;
	yBall=72;
	move_sprite(4, 80, 72);
	printf("    ""%i", score1,"    ""%i", score2);
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
	
	if(countPad==40){
		if(joypad()==J_UP ){
			if(yPad1<=16){
			}else{
				updateSprite(1, -1);
			 } 
		}
			
		
		if(joypad()==J_DOWN){
			if(yPad1>=144){
			}else{
				updateSprite(1, 1);
			 }
		}
			
		
		if(joypad()==J_A){
			if(yPad2>=144){	
			}else{
				updateSprite(2, 1);
			 }
			}

		if(joypad()==J_B){
			if(yPad2<=16){
			}else{
				updateSprite(2, -1);
			 }
			
		}
		moveBall();
		countPad=0;
	
	}
		return;
}

		
