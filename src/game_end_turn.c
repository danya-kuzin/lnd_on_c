#include <stdio.h>
#include <stdlib.h>
#include "game.h"

enum GameError game_end_turn(struct GameState *game) {
    int cur_i = game->cur_player_id_turn - 1;

    // текущий игрок делается ALREADY_TURN
    game->players[cur_i].turn = ALREADY_TURN;

    // если текущий игрок не последний в массиве
    if (cur_i + 1 < game->num_of_players) {
        game->players[cur_i + 1].turn = TURN_NOW;
        game->cur_player_id_turn = game->players[cur_i + 1].id;

        // все юниты этого игрока обновляют свое макс. перемещение
        for (int i = 0; i < game->cur_cnt_units; i++) {
            if (game->all_units[i].player_id == game->cur_player_id_turn) {
                game->all_units[i].movement_left = game->all_units[i].speed;
            }
        }
        
        return GAME_OK;
    } else {
        game->all_players_end_turns = true;

        // приведение подсчета ходов к изначальным значениям
        for (int i = 0; i < game->num_of_players; i++) {
            game->players[i].turn = NOT_TURN_YET;
        }
        game->players[0].turn = TURN_NOW;
        game->cur_player_id_turn = game->players[0].id;
        
        // все юниты этого игрока обновляют свое макс. перемещение
        for (int i = 0; i < game->cur_cnt_units; i++) {
            if (game->all_units[i].player_id == game->cur_player_id_turn) {
                game->all_units[i].movement_left = game->all_units[i].speed;
            }
        }

        return GAME_OK;
    }

    return GAME_OK;
}