#include <stdio.h>
#include "project.h"
#include <unistd.h>

void callbackFunc(unsigned int code) {
	if(code == KEY_UP) {
		printf("up");
	} else if (code == KEY_DOWN) {
		printf("down");
	} else if (code == KEY_RIGHT) {
		printf("right");
	} else if (code == KEY_LEFT) {
		printf("left");
	} else if (code == KEY_ENTER) {
		printf("enter");
	}
	printf("\n");	
}

int main() {

	pi_i2c_t *gyro=NULL;
	gyro=geti2cDevice();
	configureAccelGyro(gyro);

	pi_joystick_t *joystick=getJoystickDevice();

	int msg = 1;
	printf("Thank you for testing inputs, press 'j' to test the joystick or 'g' to test the gyro\n");
	char input = 'a';
	scanf("%c", &input);
	while(1) {
		if(input == 'g') {
			float gyro_data = get_gyro_data(gyro);
			printf("Gyro Data: %f\n", gyro_data);
			sleep(1);
		}
		if(input == 'j') {
			if(msg) {
				printf("Press any direction on the joystick and the system will tell you which direction you pushed.\n");
				msg = 0;
			}
			pollJoystick(joystick, callbackFunc, 1000);
		}
	}
	freeJoystick(joystick);
	return 0;
}
