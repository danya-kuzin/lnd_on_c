#include "game.h"

#ifndef SERVER_ATTACK_H
#define SERVER_ATTACK_H

void server_attack(char param2[], char param3[], 
                    struct GameState *game, int client_fd);

#endif