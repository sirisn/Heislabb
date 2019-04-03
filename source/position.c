#include "position.h"
#include "queue.h"
#include "elev.h"
#include "io.h"


void position_check_buttons() {
	for (int i = 0; i < N_FLOORS; i++) {
		//fiks etterpå
		for (int j = 0; j < 3; j++) {
			if (! ((i == 3) & (j == 0))) {
				if (! ((i == 0) & (j == 1))) {
					if (elev_get_button_signal(j,i)) {
						queue_insert_order(j,i);					}
				}
			}
		}
	}
}


void position_update_floor(int *floor_p) {

	if (elev_get_floor_sensor_signal() == -1) {
		return;
	}
	*floor_p = elev_get_floor_sensor_signal();
	elev_set_floor_indicator(*floor_p);
}
