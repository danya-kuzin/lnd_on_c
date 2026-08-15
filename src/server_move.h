#include "game.h"

#ifndef SERVER_MOVE_H
#define SERVER_MOVE_H

void server_move(char param2[], char param3[], char param4[],
                int client_fd, struct GameState *game);

#endif