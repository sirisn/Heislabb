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

void state_check_emergency_stop(){///denne er ny
	if(elev_get_stop_signal()) {
		state_set_state(EMERGENCY_STOP);
	}
}

void elevator_state(){
	switch (current_state) {
		case EMERGENCY_STOP:
		elev_set_motor_direction(DIRN_STOP);
		queue_delete_all();
		while(elev_get_stop_signal()){

		};
		state_set_state(IDLE);



		break;

		case DRIVING:
		printf("DRIVING\n");
		state_check_emergency_stop();
		position_check_buttons();
		queue_set_button_lights();
		position_update_floor();
		queue_check_floor(position_get_floor(), position_get_dir());
		break;

		case ORDER_STOP:
		printf("ORDER_STOP\n");
		state_check_emergency_stop();
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
		state_check_emergency_stop();
		printf("IDLE\n");
		position_update_floor();
	    if(elev_get_floor_sensor_signal()==-1){
	        elev_set_motor_direction(DIRN_DOWN);///syns dette er litt sketshy
			while(elev_get_floor_sensor_signal()==-1){

			}

		}
		elev_set_motor_direction(DIRN_STOP);
		position_check_buttons();
		queue_set_button_lights();
		position_update_floor();//kanskje kalle position_update_floor() her?????? Kan eventuelt flyttes til queue_check_orderqueue
		//position_set_floor(elev_get_floor_sensor_signal());//tror vi trenger dette så vi vet hvor vi er i starten siri
		queue_check_orderqueue(position_get_floor());
		break;
	}
}
