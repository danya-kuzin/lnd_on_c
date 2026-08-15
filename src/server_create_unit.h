#include "unit.h"
#include "game.h"

#ifndef SERVER_CREATE_UNIT_H
#define SERVER_CREATE_UNIT_H

void server_create_unit(struct GameState *game, char unit_name[], int client_fd);

#endif