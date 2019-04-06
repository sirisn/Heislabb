#include "position.h"
#include "queue.h"
#include "elev.h"
#include "io.h"


int current_floor;
elev_motor_direction_t direction;

void position_set_dir(int dir){
	direction = dir;
}

elev_motor_direction_t position_get_dir(){
	return direction;
}

void position_set_floor(int floor){
	current_floor = floor;
}

int position_get_floor(){
	return current_floor;
}

void position_check_buttons() {
	for (int floor = 0; floor < N_FLOORS; floor++) {
		//fiks etterpå
		for (int button = 0; button < 3; button++) {
			if (! ((floor == 3) & (button == 0))) {
				if (! ((floor == 0) & (button == 1))) {
					if (elev_get_button_signal(button,floor)) {
						queue_insert_order(button,floor);
					}
				}
			}
		}
	}
}


void position_update_floor() {
	int floor = elev_get_floor_sensor_signal();
	if (floor == -1) {
		return;
	}
	position_set_floor(floor);
	elev_set_floor_indicator(floor);
}
