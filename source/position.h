

void set_dir_var(elev_motor_direction_t dir);
elev_motor_direction_t get_dir_var();

/**
* Polls order buttons and inserts orders into the queue.
*/
void position_check_buttons();

/**
* checks and updades floor_var.
*/
void position_update_floor();

/**
* sets floor lights
*/
