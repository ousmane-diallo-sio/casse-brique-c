#include "../common.h"
#include "../services/clean_stdin.h"
#include "../maps/map.h"
#include "../game/play.h"

int init_server();

void send_input(int remote_socket);

void wait_for_input(int remote_socket, char* buffer, Map *map);