#include <gb/gb.h> 
#include "ball.c"
#include "paddle.c"
#include "title.c"
#include "titles.c"

void main(){
	SPRITES_8x16;
	set_sprite_data(0, 8, paddle);
	set_sprite_tile(0, 0);
	move_sprite(0, 75, 75);
	SHOW_SPRITES;
}