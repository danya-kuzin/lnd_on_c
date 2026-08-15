#include "game.h"

#ifndef SERVER_END_TURN_H
#define SERVER_END_TURN_H

void server_end_turn(struct GameState *game, int client_fd);

#endif