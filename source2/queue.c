#include "queue.h"
#include "elev.h"
#include "position.h"
#include "io.h"
#include "state.h"

#include <stdio.h>

#define N_BUTTONS 3

int orderqueue[N_FLOORS][N_BUTTONS] = {{0}};

void queue_insert_order(int button, int floor){
	orderqueue[floor][button] = 1;
}
void queue_delete_all(){
	for(int floor=0; floor<N_FLOORS; floor++){
		for(int button=0; button<N_BUTTONS; button++){
			orderqueue[floor][button]=0;

		}
	}
	queue_set_button_lights();
}

// //litt scetchy at floor er blå
void queue_order_done(int button, int floor){
	orderqueue[floor][button] = 0;
}
//
void queue_check_floor(int floor_var, elev_motor_direction_t dir){
	if (floor_var == -1) {
		return;
	}
	if(dir==DIRN_UP){
		if(orderqueue[floor_var][BUTTON_CALL_UP] || orderqueue[floor_var][BUTTON_COMMAND]){
			state_set_state(ORDER_STOP);
			return;
		}
		int sum=0;
		for(int floor=(floor_var+1); floor<N_FLOORS; floor++){
			if(orderqueue[floor][BUTTON_CALL_UP] || orderqueue[floor][BUTTON_COMMAND] || orderqueue[floor][BUTTON_CALL_DOWN]){
				sum+=1;
			}
		}
		if (sum==0){
			printf("running down and hit order\n");
			state_set_state(ORDER_STOP);
			position_set_dir(DIRN_STOP);
		}
	}
	if(dir==DIRN_DOWN){

		if(orderqueue[floor_var][BUTTON_CALL_DOWN] || orderqueue[floor_var][BUTTON_COMMAND]){
			printf("running down and hit order\n");
			state_set_state(ORDER_STOP);
		 }
		int sum=0;
		for(int floor=(floor_var-1); floor>=0; floor--){
			if(orderqueue[floor][BUTTON_CALL_UP] || orderqueue[floor][BUTTON_COMMAND] || orderqueue[floor][BUTTON_CALL_DOWN]){
				sum+=1;
			}
		}
		if (sum==0){
			printf("running down and hit order\n");
			state_set_state(ORDER_STOP);
			position_set_dir(DIRN_STOP);
		}

	}

}

void queue_check_orderqueue(int current_floor){
		int sum=0;
		for(int floor=current_floor+1; floor<N_FLOORS; floor++){

			if(orderqueue[floor][BUTTON_CALL_UP]|| orderqueue[floor][BUTTON_COMMAND] || orderqueue[floor][BUTTON_CALL_DOWN]){
				sum+=1;
			}
		}
		if(sum>0){
			elev_set_motor_direction(DIRN_UP);
			position_set_dir(DIRN_UP);
			state_set_state(DRIVING);
			return;
		}
		for(int floor=0; floor<current_floor; floor++){
			if(orderqueue[floor][BUTTON_CALL_UP]|| orderqueue[floor][BUTTON_COMMAND] || orderqueue[floor][BUTTON_CALL_DOWN]){
				sum+=1;
			}
		}
		if(sum>0){
			elev_set_motor_direction(DIRN_DOWN);
			position_set_dir(DIRN_DOWN);
			state_set_state(DRIVING);
			return;
		}
		state_set_state(IDLE);
}

void queue_set_button_lights(){
	for(int floor=0; floor<N_FLOORS; floor++){
		for(int button=0; button<N_BUTTONS; button++){
			if (! ((floor == 3) & (button == 0))) {
				if (! ((floor == 0) & (button == 1))) {
					elev_set_button_lamp(button, floor, orderqueue[floor][button]);
				}
			}
		}
	}
}




// void queue_check_floor(int floor, elev_motor_direction_t dir){
// 	if (floor == -1) {
// 		return;
// 	}
// 	if(dir==DIRN_UP){
// 		if(orderqueue[floor][BUTTON_CALL_UP] || orderqueue[floor][BUTTON_COMMAND]){
// 			//her kaller vi stopp funksjonen vår!!
// 			printf("running up and hit order\n");
// 			queue_order_done(BUTTON_CALL_UP, floor);
// 			queue_order_done(BUTTON_COMMAND, floor);
// 			queue_order_done(BUTTON_CALL_DOWN, floor);
// 		}
// 		int sum=0;
// 		for(int i=floor+1; i<N_FLOORS; i++){
// 			if(orderqueue[i][BUTTON_CALL_UP] || orderqueue[i][BUTTON_COMMAND] || orderqueue[i][BUTTON_CALL_DOWN]){
// 				sum+=1;
// 			}
// 		}
// 		if (sum==0){
// 			printf("running down and hit order\n");
// 			queue_order_done(BUTTON_CALL_DOWN, floor);
// 			queue_order_done(BUTTON_COMMAND, floor);
// 			queue_order_done(BUTTON_CALL_DOWN, floor);
// 			elev_set_motor_direction(DIRN_STOP);
// 			position_set_dir(DIRN_STOP);
// 		}
// 	}
// 	if(dir==DIRN_DOWN){
//
// 		if(orderqueue[floor][BUTTON_CALL_DOWN] || orderqueue[floor][BUTTON_COMMAND]){
// 			printf("running down and hit order\n");
// 			queue_order_done(BUTTON_CALL_DOWN, floor);
// 			queue_order_done(BUTTON_COMMAND, floor);
// 			queue_order_done(BUTTON_CALL_DOWN, floor);
// 		 }
// 		int sum=0;
// 		for(int i=floor-1; i>=0; i--){
// 			if(orderqueue[i][BUTTON_CALL_UP] || orderqueue[i][BUTTON_COMMAND] || orderqueue[i][BUTTON_CALL_DOWN]){
// 				sum+=1;
// 			}
// 		}
// 		if (sum==0){
// 			printf("running down and hit order\n");
// 			queue_order_done(BUTTON_CALL_DOWN, floor);
// 			queue_order_done(BUTTON_COMMAND, floor);
// 			queue_order_done(BUTTON_CALL_DOWN, floor);
// 			elev_set_motor_direction(DIRN_STOP);
// 			position_set_dir(DIRN_STOP);
// 		}
//
// 	}
// 	if(dir==DIRN_STOP){
// 		int sum=0;
// 		for(int i=floor+1; i<N_FLOORS; i++){
//
// 			if(orderqueue[i][BUTTON_CALL_UP]|| orderqueue[i][BUTTON_COMMAND] || orderqueue[i][BUTTON_CALL_DOWN]){
// 				sum+=1;
// 			}
// 		}
// 		if(sum>0){
// 			elev_set_motor_direction(DIRN_UP);
// 			position_set_dir(DIRN_UP);
// 			return;
// 		}
// 		for(int i=0; i<floor; i++){
// 			if(orderqueue[i][BUTTON_CALL_UP]|| orderqueue[i][BUTTON_COMMAND] || orderqueue[i][BUTTON_CALL_DOWN]){
// 				sum+=1;
// 			}
// 		}
// 		if(sum>0){
// 			elev_set_motor_direction(DIRN_DOWN);
// 			position_set_dir(DIRN_DOWN);
//
// 			return;
// 		}
// 	}
// }
