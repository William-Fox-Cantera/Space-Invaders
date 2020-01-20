#include "project.h"

void display_game(int game_state[8][8], pi_framebuffer_t *dev) {
	int current;

	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j++) {
			current = game_state[i][j];
			//player
			if(current == 1) {
				dev->bitmap->pixel[i][j]=getColor(0,0,240);
			}//Alien
			else if(current == 2) {
				dev->bitmap->pixel[i][j]=getColor(0,240,0);
			}//Bullet
			else if(current == 3) {
				dev->bitmap->pixel[i][j]=getColor(240,0,0);
			}//Clear anything else
			else {
				dev->bitmap->pixel[i][j]=getColor(0,0,0);
			}
		}
	}
}


void display_end(int score, pi_framebuffer_t *dev) {
	uint16_t r=getColor(255,0,60);
	uint16_t g=getColor(0,255,0);
	uint16_t b=getColor(0,0,255);
	uint16_t x=getColor(90,15,70);
	uint16_t s=getColor(200,0,255);

	int gameOver[8][8] = {
		{0,b,b,s,0,r,0,r},
		{0,0,0,s,r,r,r,r},
		{0,b,b,b,x,0,x,x},
		{0,0,g,g,x,x,0,x},
		{0,0,g,g,0,0,g,g},
		{r,r,0,0,0,0,g,g},
		{0,0,r,r,0,0,0,x},
		{r,r,0,0,x,x,x,x},
	};

	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j++) {
			dev->bitmap->pixel[i][j]=gameOver[i][j];
		}
	}
}
