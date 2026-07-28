#include <stdio.h>
#include <stdlib.h>
#include "game.h"

enum GameError game_end_turn(struct GameState *game) {
// выяснить кто сейча хоит, поставить ему turn = 2, а следующему(не прибавлять 1?) выставить 1, а потом все обнулить и первому дать единицу
    // сама команда move
    int i = 0;

    while (i <= game->num_of_players) {
        if (game->players[i % game->num_of_players].turn == TURN_NOW) {
            game->players[i % game->num_of_players].turn = ALREADY_TURN; 
        }

        i++;

        if (game->players[i % game->num_of_players].turn == NOT_TURN_YET) {
            game->players[i % game->num_of_players].turn = TURN_NOW;
            game->cur_player_id_turn = (i % game->num_of_players) + 1;
            return GAME_OK;
        } else {
            game->all_players_end_turns = true;

            // приведение подсчета ходов к изначальным значениям
            for (int i = 0; i < game->num_of_players; i++) {
                game->players[i].turn = NOT_TURN_YET;
            }
            game->players[0].turn = TURN_NOW;
            game->cur_player_id_turn = game->players[0].id;
            
            return GAME_OK;
        }

    }

    return GAME_OK;
}