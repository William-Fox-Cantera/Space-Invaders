#include "project.h"

float get_gyro_data(pi_i2c_t* gyro){
	coordinate_t data;
	getMagData(gyro,&data);
	return data.y;
}

int get_joystick_data(pi_joystick_t *joystick, void (*callback)(unsigned int code), int timeout) {
	pollJoystick(joystick, callback, timeout);
}
