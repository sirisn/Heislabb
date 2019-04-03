#include "queue.h"
#include "elev.h"
#include "position.h"
#include "io.h"

#define N_BUTTONS 3

int orderqueue[N_FLOORS][N_BUTTONS] = {{0}};

void queue_insert_order(int button, int floor){
	orderqueue[floor][button]=1;
}

// void delete_queue(){
// 	for(int i=0; i<N_FLOORS; i++){
// 		for(int j=0; j<N_BUTTONS; j++){
// 			orderqueue[i][j]=0;
// 		}
// 	}
// }
// //litt scetchy at floor er blå
// void queue_order_done(int button, int floor){
// 	orderqueue[floor][button];
// }
//
// void queue_check_floor(int* floor, int* dir){
// 	if (*floor == -1) {
// 		return;
// 	}
// 	if(*dir==DIRN_UP){
// 		if(orderqueue[*floor][BUTTON_CALL_UP] || orderqueue[*floor][BUTTON_COMMAND]){
// 			//her kaller vi stopp funksjonen vår!!
// 		}
// 		int sum=0;
// 		for(int i=*floor+1; i<N_FLOORS; i++){
// 			if(orderqueue[i][BUTTON_CALL_UP] || orderqueue[i][BUTTON_COMMAND] || orderqueue[i][BUTTON_CALL_DOWN]){
// 				sum+=1;
// 			}
// 		}
// 		if (sum==0){
// 			elev_set_motor_direction(DIRN_STOP);
// 		}
// 	}
// 	if(*dir==DIRN_DOWN){
// 		if(orderqueue[*floor][BUTTON_CALL_UP] || orderqueue[*floor][BUTTON_COMMAND]){
// 			elev_set_motor_direction(DIRN_STOP);
// 		}
// 		int sum=0;
// 		for(int i=*floor-1; i>0; i--){
// 			if(orderqueue[i][BUTTON_CALL_UP] || orderqueue[i][BUTTON_COMMAND] || orderqueue[i][BUTTON_CALL_DOWN]){
// 				sum+=1;
// 			}
// 		}
// 		if (sum==0){
// 			elev_set_motor_direction(DIRN_STOP);
// 		}
//
// 	}
// 	if(*dir==DIRN_STOP){
// 		elev_set_motor_direction(DIRN_STOP);
// 		int sum=0;
// 		for(int i=*floor+1, i<N_FLOORS, i++){
// 			if(orderqueue[i][BUTTON_CALL_UP]|| orderqueue[i][BUTTON_COMMAND] || orderqueue[i][BUTTON_CALL_DOWN]){
// 				sum+=1;
// 			}
// 		}
// 		if(sum>0){
// 			elev_set_motor_direction(DIRN_UP);
// 			return;
// 		}
//
// 		for(int i=*floor-1, i>0_FLOORS, i--){
// 			if(orderqueue[i][BUTTON_CALL_DOWN]|| orderqueue[i][BUTTON_COMMAND] || orderqueue[i][BUTTON_CALL_DOWN]){
// 				sum+=1;
// 			}
// 		}
// 		if(sum>0){
// 			elev_set_motor_direction(DIRN_DOWN);
//
// 			return;
// 		}
// 	}
// }

void queue_set_button_lights(){
	for(int i=0; i<N_FLOORS; i++){
		for(int j=0; j<N_BUTTONS; j++){
			if (! ((i == 3) & (j == 0))) {
				if (! ((i == 0) & (j == 1))) {
					elev_set_button_lamp(j, i, orderqueue[i][j]);
				}
			}
		}
	}
}
