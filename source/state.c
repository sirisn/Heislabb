#include "elev.h"
#include "position.h"
#include "io.h"
#include "queue.h"
#include "state.h"
#include "timer.h"
#include <stdio.h>

state_elevator_states_t current_state;

void state_set_state(state_elevator_states_t state){
	current_state = state;
}

void elevator_state(){
	switch (current_state) {
		case EMERGENCY_STOP:
		break;

		case DRIVING:
		printf("DRIVING\n");
		position_check_buttons();
		queue_set_button_lights();
		position_update_floor();
		queue_check_floor(position_get_floor(), position_get_dir());
		break;

		case ORDER_STOP:
		printf("ORDER_STOP\n");
		elev_set_motor_direction(DIRN_STOP);
		queue_order_done(BUTTON_CALL_UP, position_get_floor());
		queue_order_done(BUTTON_COMMAND, position_get_floor());
		queue_order_done(BUTTON_CALL_DOWN, position_get_floor());
		elev_set_door_open_lamp(1);
		timer_start_timer();
		elev_set_motor_direction(DIRN_STOP);
		while (!timer_timeout()){
		// 	int isTimeout = timer_timeout();
		// 	printf("isTimeout: %d", isTimeout);
			position_check_buttons();
			queue_set_button_lights();
		}
		elev_set_door_open_lamp(0);
		if (position_get_dir() == DIRN_STOP){
			state_set_state(IDLE);
		}
		else {
			state_set_state(DRIVING);
			elev_set_motor_direction(position_get_dir());
		}
		break;

		case IDLE:
		printf("IDLE\n");
		elev_set_motor_direction(DIRN_STOP);
		position_check_buttons();
		queue_set_button_lights();
		queue_check_orderqueue(position_get_floor());
		break;
	}
}
