

void position_set_dir(int dir);

int position_get_dir();


void position_set_floor(int floor);

int position_get_floor();

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
