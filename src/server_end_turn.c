#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "unit.h"
#include "net_common.h"
#include "server_end_turn.h"

void server_end_turn(struct GameState *game, int client_fd) {
    
    // передаем unit_id, target_x, target_y в ядро игры
    enum GameError error;
    error = game_end_turn(game);

    const char *message = NULL;
    switch (error) {
        case GAME_OK:
            message = "Turn ended\n";
            send_all(client_fd, message, strlen(message));
            break;

        default:
            message = "Error: unknown error type \n";
            send_all(client_fd, message, strlen(message));
            break;
    }
}