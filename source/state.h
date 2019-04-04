
typedef enum tag_state_elevator_states {
    EMERGENCY_STOP = 0,
    DRIVING = 1,
    ORDER_STOP = 2,
	IDLE = 3
} state_elevator_states_t;


void elevator_state();
void state_set_state();
