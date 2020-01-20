#include <stdio.h>
#include "project.h"

int main() {
	printf("Test display_game()? Type: 1, or Test display_end()? Type: 2\n");
	int testNumber = 0;
	scanf("%d", &testNumber);

	int game_state[8][8] = {
		{0,0,0,0,0,0,0,0},
		{0,0,0,2,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,2,0},
		{0,0,0,0,0,0,0,0},
		{0,2,3,0,3,0,0,1},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,2,0,0},
	};
	
	pi_framebuffer_t *dev=getFBDevice();
	
	if(testNumber == 1) {
		display_game(game_state, dev);
	}
	if(testNumber == 2) {
		display_end(15, dev);
	}
	return 0;
}
