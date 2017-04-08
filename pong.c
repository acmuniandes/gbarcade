#include <gb/gb.h> 
#include "ball.c"
#include "paddle.c"



//paddle 1 cords
unsigned char PosPad1;

//paddle 2 cords
unsigned char PosPad2;

//ball
unsigned char xBall;
unsigned char yBall;
unsigned char xVel;
unsigned char yVel;

//Extra
unsigned char score1=0;
unsigned char score2=0;

void pong(){
	while(1) {

	switch(joypad()) {
		
		case J_RIGHT :
			delay(100);
			break;
		case J_LEFT : 
            delay(100);
			break;
		case J_UP :
		
			if(xPad1<=0){
				delay(100);
			break;	
			}else{
				delay(100);
				PosPad1++;
				break;
			}
		
		case J_DOWN :
			if(xPad1>=160){
				delay(100);
			break;	
			}else{
				delay(100);
				PosPad1--;
				break;
			}
			
		case J_START : 
			delay(100);
			break;
		case J_SELECT : 
			printf("Select!\n");
			delay(100);
			break;
		case J_A : 
		if(xPad2<=0){
		delay(100);
			break;	
			}else{
				delay(100);
				PosPad2++;
				break;
			}

		case J_B : 
			if(xPad2>=160){
				delay(100);
			break;	
			}else{
				delay(100);
				PosPad2--;
				break;
			}
			
		default :
			break;
			}
		}
}