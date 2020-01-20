#include <stdlib.h>
#include <stdio.h>
#include <linux/input.h>
#include "sense.h"
#include "framebuffer.h"
#include <unistd.h>
#include <string.h>

//prototype functions here
float get_gyro_data(pi_i2c_t* gyro);
int get_joystick_data(pi_joystick_t *joystick, void (*callback)(unsigned int code), int timeout);
void display_game(int game_state[8][8], pi_framebuffer_t *dev);
void display_end(int score, pi_framebuffer_t *dev);
