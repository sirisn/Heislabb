


int orderqueue[N_FLOORS][N_BUTTONS] = {0};

void insert_order(elev_button_type_t button, int floor);

void delete_queue();

void queue_logic(int floor, elev_motor_direction_t dir);

void order_done(elev_button_type_t button, int floor);
