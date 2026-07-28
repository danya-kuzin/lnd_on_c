#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "unit.h"
#include "cli_move.h"

void cli_end_turn(struct GameState *game) {
    
    // передаем unit_id, target_x, target_y в ядро игры
    enum GameError error;
    error = game_end_turn(game);
    
    switch (error) {
        case GAME_OK:
            printf("Turn ended\n");
            break;

        default:
            printf("Error: unknown error type \n");
            break;
    }
}