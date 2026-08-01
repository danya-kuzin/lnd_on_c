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
        // и флаг атаки
        for (int i = 0; i < game->cur_cnt_units; i++) {
            if (game->all_units[i].player_id == game->cur_player_id_turn) {
                game->all_units[i].movement_left = game->all_units[i].speed;
                game->all_units[i].attack_flag = false;
            }
        }
        
        return GAME_OK;
    } else {
        game->all_players_end_turns = true;

        // все игроки получают золото от деревень
        for (int i = 0; i < MAP_HEIGHT; i++) {
            for (int j = 0; j < MAP_WIDTH; j++) {
                int plus_gold;

                switch (game->map[i][j].terrain) {
                    case TERRAIN_VILLAGE_1:
                        plus_gold = 1; 
                        break;

                    case TERRAIN_VILLAGE_2:
                        plus_gold = 2; 
                        break;

                    case TERRAIN_VILLAGE_3:
                        plus_gold = 3; 
                        break;
                    
                    default:
                        plus_gold = 0;
                }

                int owner_id = game->map[i][j].owner_player_id - 1;
                if (owner_id >= 1 && owner_id <= game->num_of_players) {
                    game->players[owner_id].gold += plus_gold;
                }
            }
        }

        // приведение подсчета ходов к изначальным значениям
        for (int i = 0; i < game->num_of_players; i++) {
            game->players[i].turn = NOT_TURN_YET;
        }
        game->players[0].turn = TURN_NOW;
        game->cur_player_id_turn = game->players[0].id;
        
        // все юниты этого игрока обновляют свое макс. перемещение
        // и флаг атаки
        for (int i = 0; i < game->cur_cnt_units; i++) {
            if (game->all_units[i].player_id == game->cur_player_id_turn) {
                game->all_units[i].movement_left = game->all_units[i].speed;
                game->all_units[i].attack_flag = false;
            }
        }

        return GAME_OK;
    }

    return GAME_OK;
}