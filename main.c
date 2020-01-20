#include "project.h"

//Define Gyrometer
pi_i2c_t* gyro=NULL;
int shooting = 0;
int running = 1;

void update_game(int game_state[8][8], int player_x, int player_y, int bullet, int alien) {

	//Get rid of current player in game state
	for(int i = 0; i < 8 ; i++) {
		for(int j = 0; j < 8; j++) {
			if(game_state[i][j] == 1) game_state[i][j] = 0;

			//Have bullet kill aliens
			if(game_state[i][j] == 3 && game_state[i][j-1] == 2) {
				game_state[i][j-1] = 0;
				game_state[i][j] = 0;
				//score++;
			}

			//Motion for bullets
			else if(game_state[i][j] == 3 && bullet == 1) {
				if(j > 0) {
					game_state[i][j-1] = 3;
					game_state[i][j] = 0;
				} else {
					game_state[i][j] = 0;
				}
			}
		}
	}

	//Motion for alien 
	for(int i = 0; i < 8; i++) {
		for(int j = 8; j > 0; j--) {
			
			if(game_state[i][j] == 2 && alien == 1) {
				//If alien has not reached bottom
				if(j < 7) {
					game_state[i][j+1] = 2;
					game_state[i][j] = 0;
				}else{
					//Game over script goes here
					game_state[i][j] = 0;
					running = 0;
				}
			}
		}
	}
	

	//Create new player at argument location
	game_state[player_x][player_y] = 1;
}

void shoot_bullet(int game_state[8][8], int player_x, int player_y) {
	game_state[player_x][player_y - 1] = 3;
}

void create_alien(int game_state[8][8], int x) {
	game_state[x][1] = 2;
}

void callbackFunc(unsigned int code) {
	shooting = 1;
}

int main(void) {
	/*Key for game_state
	 *1: player
	 *2: alien
	 *3: bullet
	 */

	//Create screen buffer
	pi_framebuffer_t *dev=getFBDevice();

	//Create joystick
	pi_joystick_t* joystick=getJoystickDevice();

	//Create gyrometer
	gyro=geti2cDevice();
	configureAccelGyro(gyro);

	//Create array to store the game
	int game_state[8][8];

	//Variable for player location
	int player_x = 4;
	int player_y = 7;

	//For gyrometer
	int player_movement = 0;
	int alien = 0;
	int bullet = 0;

	//Update rates for main loop
	int time_rate = 50000;
	int player_rate = 370000;
	int bullet_rate = 100000;
	int alien_rate = 200000;
	int alienFall_rate = 700000;

	int player_count = 0;
	int bullet_count = 0;
	int alien_count = 0;
	int alienFall_count = 0;
	
	//SCORE
	int score = 2;

	//Game Loop
	while(running) {
		
		//Update the player on the screen at player rate
		if(player_count*time_rate >= player_rate) {

			float temp_gyro_data = get_gyro_data(gyro);

			if(temp_gyro_data > 16) player_movement = -1;
			else if(temp_gyro_data < -16) player_movement = 1;
			else player_movement = 0;                                                                 	
			if(player_x == 7 && player_movement != 1) {
				player_x += player_movement;
			}else if(player_x == 0 && player_movement != -1) {
				player_x += player_movement;
			}else if(player_x != 0 && player_x != 7) {
				player_x += player_movement;
			}

			player_count = 0;
		}

		//Update the bullet on the screen at bullet rate
		if(bullet_count*time_rate >= bullet_rate) {
			//For updating bullet on the screen
			bullet = 1;

			bullet_count = 0;
		}

		//Update the alien on the screen
		if(alien_count*time_rate >= alien_rate) {
			int n = rand() % 100 + 1;
			if(n > 95) {
				int place = rand() % 7 + 1;
				create_alien(game_state, place);
			}

			alien_count = 0;
		}
		//Make aliens fall with activation variable
		if(alienFall_count*time_rate >= alienFall_rate) {
			alien = 1;
			alienFall_count = 0;
		}

		//Check Joystick
		get_joystick_data(joystick, callbackFunc, 10);

		if(shooting ==  1) {
			shoot_bullet(game_state, player_x, player_y);
			shooting = 0;
		}

		//Updates the game state through time
		update_game(game_state, player_x, player_y, bullet, alien);

		//Diplay the current state of the game
		display_game(game_state, dev);

		//If the position of the bullet was updated then switch it off until the next bullet count
		if(bullet == 1) bullet = 0;

		//If position of the alien was updated don't update it again
		if(alien == 1) alien = 0;
		
		//Igf alien hits bottom display end
		if(running == 0) {
			display_end(score, dev);
		}

		//Wait for update rate
		usleep(time_rate);

		//Iterate for each objects speed through time
		player_count++;
		bullet_count++;
		alien_count++;
		alienFall_count++;
	}

	freeJoystick(joystick);
	return 1;
}
