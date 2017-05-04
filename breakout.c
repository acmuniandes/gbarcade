#include <stdio.h>
#include <gb/gb.h>

#include "ball.c"
#include "paddleB.c"

//boolean implementation
typedef int bool;
#define true 1
#define false 0

//functions
void loadSprites();
void checkControls();
void startBall();
void updateSprite(signed char cuanto);
void moveBall();
bool collisionCheck(unsigned char x1, unsigned char y1, unsigned char w1, unsigned char h1, unsigned char x2, unsigned char y2, unsigned char w2, unsigned char h2);


UINT8 char ballInfo[4] = {80,72,0,0};//ball[0]X position// ball[1]Y position //ball[2]X velocity// ball[3]ball[2]Y velocity//
unsigned char player=50; //player's X position
UINT8 score=0;//players score
bool playing=true; // this will be usefull later for delaying the start...
//ball
unsigned char xBall=80;
unsigned char yBall=72;
signed char xVel;
signed char yVel;
bool newBall=true;
//counter for delay -> this must be changed later
unsigned char countPad=0;
int count=0;//Delays the ball without halt the whole system

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
	set_sprite_data(0,2,paddle);
	set_sprite_data(2,2,ball);
    //paddle
	set_sprite_tile(0,0);
	set_sprite_tile(1,1);
    //ball 
	set_sprite_tile(2,2);
	
	//sets paddle 
	move_sprite(0, player, 140);
	move_sprite(1, player+8, 140);
    
    //sets ball
	move_sprite(2, xBall, yBall); 
	DISPLAY_ON;
	SHOW_SPRITES;
}

bool collisionCheck(unsigned char x1, unsigned char y1, unsigned char w1, unsigned char h1, unsigned char x2, unsigned char y2, unsigned char w2, unsigned char h2){
    // x1 = xPad , y1 = yPad = 20 (?), w1 = ancho, h1 = alto, x2 = xBall, y2 = yBall, w2 = 8, h2 = 8  
	if ((x1 < (x2+w2)) && ((x1+w1) > x2) && (y1 < (h2+y2)) && ((y1+h1) > y2)) {
		return true; 
	} else {
		return false;
    }
}

void updateSprite(signed char cuanto){

	player+=cuanto;
	move_sprite(0, player, 140);
	move_sprite(1, player+8, 140);
	return;
}

void moveBall(){ 
    if(xBall==0 || xBall==160){
		xVel=xVel*-1;
	}

	if(yBall==0){
		yVel=yVel*-1;
	}
    if(yBall>140){
        score++;
        newBall = true;
    }
    
	if(collisionCheck(player, 140, 8,16, xBall, yBall, 8,8)==true){
        yVel=yVel*-1;
		if(collisionCheck(player, 140, 8,2, xBall, yBall, 8,8)==true){
			if(xVel==0){
				xVel=1;
			}else{
				xVel=xVel*-1;
			}
		}
		
	}

	count++;
	if(countPad==60){
		up:
		countPad++;
		if(countPad!=120){
			goto up;
		}
        xBall=xBall+xVel;
        yBall=yBall+yVel;
        move_sprite(2, xBall, yBall);
        count=0;
	}
	  
	
}

void startBall(){
	xBall=80; // later on we'll change this in order to make the ball start over the paddle
	yBall=20;
	move_sprite(2, 80, 20);
	//printf("PAUSE");
	pause:
        if(joypad()==J_START){
            xVel=1;
            yVel=1;
            newBall=false;
        }else{
            goto pause;
        }
	
}

void checkControls(){
	countPad++;
	
	if(countPad==60){ // set originally at 40 but seems way too fast
		
        if(joypad()==J_RIGHT ){
			if(player<=144){
                updateSprite(1);
			}else{ // he-he 
			} 
		}
        if(joypad()==J_LEFT ){
			if(player>=14){
                updateSprite(-1);
			}else{ // he-he
			}
		}
		moveBall();
		countPad=0;
	
	}
		return;
	
}