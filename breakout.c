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
// Bricks
UINT8 bricks[3][8]; // [3][30]
// Player
unsigned char player=80; // X position
UINT8 score=0;// score
bool playing=true; // this will be useful later for delaying the start...
//ball
UINT8 char ballInfo[4] = {54,132,-1,0};//ball[0]X position// ball[1]Y position //ball[2]X velocity// ball[3]Y velocity//
bool newBall=true;
//current delay system 
unsigned char countPad=0;
int count=0;//Delays the ball without halt the whole system
int i, idx;//, ten;//, row;

void main(){
	loadSprites();
	restart:
        startBall();
		while(newBall==false){
            delay(2); // ---------------------------------------------------------------------------
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
    //ten=0;//each row can contain 10 blocks(160px/16px), so this tell us when to change the row value
    //row=2;// idk but works for setting the y, tried with a sum but did not work...
    for(i=0;i<8;i++){ // 3 lines
         bricks[0][i]=true; //sets it to true
         bricks[1][i]=(i*20 + 10);//(ten*20); // sets x
         bricks[2][i]=16;//row*8; // sets y
         set_sprite_tile(i+3,3);
         set_sprite_tile(i+33,4);
         move_sprite(i+3, bricks[1][i], bricks[2][i]);
         move_sprite(i+33, bricks[1][i] + 8, bricks[2][i]);
         //if(ten==4){ ten=0; row++; }else{ ten++; }
    }
	DISPLAY_ON;
	SHOW_SPRITES;
}

bool collisionCheck(unsigned char x1, unsigned char y1, unsigned char w1, unsigned char h1, unsigned char x2, unsigned char y2, unsigned char w2, unsigned char h2){
    // x1 = xPad , y1 = yPad = 140, w1 = alto, h1 = ancho, x2 = ballInfo[0], y2 = ballInfo[1], w2 = 8, h2 = 8  
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
	if(ballInfo[1]<=28 && ballInfo[0]>=10){ // i*20+10, 
        //Here we check possible collision with a brick 
        idx = (ballInfo[0]-9)/20;
        if(ballInfo[1]==28 && bricks[0][idx]==1 && ballInfo[3]==-1){
            ballInfo[3]=ballInfo[3]*-1;
            bricks[0][idx]=0;// sets into false 
            bricks[1][idx]=0;
            bricks[2][idx]=0; // hide it (dont know what else can I do...)
            move_sprite(idx+3, bricks[1][idx], bricks[2][idx]);
            move_sprite(idx+33, bricks[1][idx] + 8, bricks[2][idx]);
            // next: make game over after all bricks are gone!
        } else if(ballInfo[0]%20==10 && bricks[0][idx]==1 && ballInfo[2]>0){ // Hits the left side of a brick 
            ballInfo[2]=ballInfo[2]*-1;
            bricks[0][idx]=0;// sets into false 
            bricks[1][idx]=0;
            bricks[2][idx]=0; // hide it (dont know what else can I do...)
            move_sprite(idx+3, bricks[1][idx], bricks[2][idx]);
            move_sprite(idx+33, bricks[1][idx] + 8, bricks[2][idx]);
        } else if(ballInfo[0]%20==6 && bricks[0][idx]==1 && ballInfo[2]<0){ // Hits the right side of a brick
            ballInfo[2]=ballInfo[2]*-1;
            bricks[0][idx]=0;// sets into false 
            bricks[1][idx]=0;
            bricks[2][idx]=0; // hide it (dont know what else can I do...)
            move_sprite(idx+3, bricks[1][idx], bricks[2][idx]);
            move_sprite(idx+33, bricks[1][idx] + 8, bricks[2][idx]);
        }
    }
    /*else*/ if(ballInfo[1]==10){
		ballInfo[3]=ballInfo[3]*-1;
	}
    
    if(ballInfo[1]>=144){
        score++;
        newBall = true;
    }
    
	if(collisionCheck(player, 140, 8,16, ballInfo[0], ballInfo[1], 8,8)==true){
        ballInfo[3]=ballInfo[3]*-1;
		if(collisionCheck(player, 140, 8,2, ballInfo[0], ballInfo[1], 8,4)==true){
			ballInfo[2]=ballInfo[2]*-1;
		}
		
	}

	//count++;
	//if(countPad==60){
        /*up:
		countPad++;
		if(countPad!=120){
			goto up;
		}*/
        delay(2); // put a bigger argument (10 is a good one) to see everything in slow motion
        ballInfo[0]=ballInfo[0]+ballInfo[2];
        ballInfo[1]=ballInfo[1]+ballInfo[3];
        move_sprite(2, ballInfo[0], ballInfo[1]);
        //count=0;
	//}
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
            delay(2);
            checkControls();
            goto pause;
        }
	
}

void checkControls(){ // Controls which moves the paddle
	//countPad++;
	//if(countPad==60){
        if(joypad()==J_RIGHT  && player<=144){
            updatePaddleSprite(1);
            if(newBall==true){ // 
                ballInfo[0]=ballInfo[0]+1;
                move_sprite(2, ballInfo[0], ballInfo[1]);
            }else{
                moveBall();
            }
             
		}
        else if(joypad()==J_LEFT && player>=14){
            updatePaddleSprite(-1);
            if(newBall==true){ // 
                ballInfo[0]=ballInfo[0]-1;
                move_sprite(2, ballInfo[0], ballInfo[1]);
            }else{//
                moveBall();
            }
        }else{
            if(newBall==false) {
                moveBall();
            }else{
            }
        }
		//countPad=0;
	//}
	return;
}