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
	for (int i = 0; i < N_FLOORS; i++) {
		//fiks etterpå
		for (int j = 0; j < 3; j++) {
			if (! ((i == 3) & (j == 0))) {
				if (! ((i == 0) & (j == 1))) {
					if (elev_get_button_signal(j,i)) {
						queue_insert_order(j,i);
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
