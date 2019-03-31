#include "queue.h"
#include "elev.h"

void queue_insert_order(elev_button_type_t button, int floor){
	orderqueue[floor][button]=1;
}

void delete_queue(){
	for(int i=0, i<N_FLOORS, i++){
		for(int j=0, j<N_BUTTONS, j++){
			orderqueue[i][j]=0;
		}
	}
}
//litt scetchy at floor er blå
void queue_order_done(elev_button_type_t button, int floor){
	orderqueue[floor][button];
}

void queue_check_floor(int floor, elev_motor_direction_t dir){
	if(dir==DIRN_UP){
		if(orderqueue[floor][BUTTON_CALL_UP] || orderqueue[floor][BUTTON_COMMAND]){
			//her kaller vi stopp funksjonen vår!!
		}
		int sum=0;
		for(int i=floor+1, i<N_FLOORS, i++){
			if(orderqueue[i][BUTTON_CALL_UP] || orderqueue[i][BUTTON_COMMAND] || orderqueue[i][BUTTON_CALL_DOWN]){
				sum+=1;
			}
		}
		if (sum==0){
			elev_set_motor_direction(DIRN_STOP);
		}
	}
	if(dir==DIRN_DOWN){
		if(orderqueue[floor][BUTTON_CALL_UP] || orderqueue[floor][BUTTON_COMMAND]){
			elev_set_motor_direction(DIRN_STOP);
		}
		int sum=0;
		for(int i=floor-1, i>0, i--){
			if(orderqueue[i][BUTTON_CALL_UP] || orderqueue[i][BUTTON_COMMAND] || orderqueue[i][BUTTON_CALL_DOWN]){
				sum+=1;
			}
		}
		if (sum==0){
			elev_set_motor_direction(DIRN_STOP);
		}

	}
	if(dir==DIRN_STOP){
		elev_set_motor_direction(DIRN_STOP);
		int sum=0;
		for(int i=floor+1, i<N_FLOORS, i++){
			if(orderqueue[i][BUTTON_CALL_UP]|| orderqueue[i][BUTTON_COMMAND] || orderqueue[i][BUTTON_CALL_DOWN]){
				sum+=1;
			}
		}
		if(sum>0){
			elev_set_motor_direction(DIRN_UP);
			return;
		}

		for(int i=floor-1, i>0_FLOORS, i--){
			if(orderqueue[i][BUTTON_CALL_DOWN]|| orderqueue[i][BUTTON_COMMAND] || orderqueue[i][BUTTON_CALL_DOWN]){
				sum+=1;
			}
		}
		if(sum>0){
			elev_set_motor_direction(DIRN_DOWN);

			return;
		}
	}
}
void queue_set_button_lights(){
	for(int i=0, i<N_FLOORS, i++){
		for(int j=0, i<N_BUTTONS, j++){
			elev_set_button_lamp(j, i, order_queue[i][j]);
		}
	}
}
