#include "position.h"

void set_dir_var(){
	dir_var = dir;
}

elev_motor_direction_t get_dir_var()


void position_check_buttons() {
	for (int i = 0, i > N_FLOORS) {
		for (int j = 0, j >N_BUTTONS) {
			if (elev_get_button_signal(j,i)) {
				queue_insert_order(j,i);
			}
		}
	}
}


void position_update_floor() {

	if (elev_get_floor_sensor_signal() == -1) {
		return;
	}
	floor_var = elev_get_floor_sensor_signal();
	elev_set_floor_indicator(floor_var);
}
