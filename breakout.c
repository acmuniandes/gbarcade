#include <stdio.h>
#include <gb/gb.h>

#include "ball.c"
#include "paddleB.c"
#include "block.c"
//boolean implementation
typedef int bool;
#define true 1
#define false 0

//functions
void loadSprites();
void checkControls();
void startBall();
void updatePaddleSprite(signed char cuanto);
void moveBall();
bool collisionCheck(unsigned char x1, unsigned char y1, unsigned char w1, unsigned char h1, unsigned char x2, unsigned char y2, unsigned char w2, unsigned char h2);

UINT8 bricks[3][50];
// Player
unsigned char player=80; // X position
UINT8 score=0;// score
bool playing=true; // this will be useful later for delaying the start...
//ball
UINT8 char ballInfo[4] = {54,132,-1,0};//ball[0]X position// ball[1]Y position //ball[2]X velocity// ball[3]Y velocity//
bool newBall=true;
//counter for delay -> this must be changed later
unsigned char countPad=0;
int count=0;//Delays the ball without halt the whole system
int i, ten;

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
	set_sprite_data(3,4,block);
    //paddle
	set_sprite_tile(0,0);
	set_sprite_tile(1,1);
    //ball 
	set_sprite_tile(2,2);
	
	//sets paddle 
	move_sprite(0, player, 140);
	move_sprite(1, player+8, 140);
    
    //sets ball
	move_sprite(2, ballInfo[0], ballInfo[1]); 
    ten=0;//each row can contain 10 blocks(160px/16px), so this counts when to change the row value
    for(i=0;i<30;i++){ // 50 is too much
        if(ten==9){
            ten=0;}else{
                ten++;}
         //sets it to true	
         bricks[0][i]=1;
         //sets x
         bricks[1][i]=ten*16;
         //sets  y
         bricks[2][i]=(i/10)*8;
    }
	DISPLAY_ON;
	SHOW_SPRITES;
}

bool collisionCheck(unsigned char x1, unsigned char y1, unsigned char w1, unsigned char h1, unsigned char x2, unsigned char y2, unsigned char w2, unsigned char h2){
    // x1 = xPad , y1 = yPad = 20 (?), w1 = ancho, h1 = alto, x2 = ballInfo[0], y2 = ballInfo[1], w2 = 8, h2 = 8  
	if ((x1 < (x2+w2)) && ((x1+w1) > x2) && (y1 < (h2+y2)) && ((y1+h1) > y2)) {
		return true; 
	} else {
		return false;
    }
}

void updatePaddleSprite(signed char cuanto){
    // Moves the paddle
	player+=cuanto;
	move_sprite(0, player, 140);
	move_sprite(1, player+8, 140);
	return;
}

void moveBall(){ 
    if(ballInfo[0]==0 || ballInfo[0]==160){
		ballInfo[2]=ballInfo[2]*-1;
	}

	if(ballInfo[1]==0){
		ballInfo[3]=ballInfo[3]*-1;
	}
    if(ballInfo[1]>=144){
        score++;
        newBall = true;
    }
    
	if(collisionCheck(player, 140, 8,16, ballInfo[0], ballInfo[1], 8,8)==true){
        ballInfo[3]=ballInfo[3]*-1;
		if(collisionCheck(player, 140, 8,2, ballInfo[0], ballInfo[1], 8,8)==true){
			ballInfo[2]=ballInfo[2]*-1;
		}
		
	}

	count++;
	if(countPad==60){
		up:
		countPad++;
		if(countPad!=120){
			goto up;
		}
        ballInfo[0]=ballInfo[0]+ballInfo[2];
        ballInfo[1]=ballInfo[1]+ballInfo[3];
        move_sprite(2, ballInfo[0], ballInfo[1]);
        count=0;
	}
}

void startBall(){
    ballInfo[0] = player + 4;
    ballInfo[1] = 132;
	move_sprite(0, player, 140);
	move_sprite(1, player+8, 140);
	move_sprite(2, ballInfo[0], ballInfo[1]);
	//printf("PAUSE");
	pause:
        if(joypad()==J_START){
            ballInfo[2]=ballInfo[2]*(-1);
            ballInfo[3]=-1;
            newBall=false;
        }else{
            checkControls();
            goto pause;
        }
	
}

void checkControls(){ // Controls which moves the paddle
	countPad++;
	if(countPad==60){ // set originally at 40 but seems way too fast
        if(joypad()==J_RIGHT ){
            if(player<=144){
                updatePaddleSprite(1);
                if(newBall==true){ // 
                    ballInfo[0]=ballInfo[0]+1;
                    move_sprite(2, ballInfo[0], ballInfo[1]);
                }else{
                    moveBall();
                }
            }else{ // he-he 
            } 
		}
        else{ 
            if(joypad()==J_LEFT ){
                if(player>=14){
                    updatePaddleSprite(-1);
                    if(newBall==true){ // 
                        ballInfo[0]=ballInfo[0]-1;
                        move_sprite(2, ballInfo[0], ballInfo[1]);
                    }else{//
                        moveBall();
                    }
                }else{ // he - he
                }
            }else{
                if(newBall==false) {
                    moveBall();
                }else{
                }
            }
        }
		countPad=0;
	}
	return;
}