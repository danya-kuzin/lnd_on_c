#include <stdlib.h>
#include <stdbool.h>
#include "game.h"

void game_init(struct GameState *game, int num_of_players)
{
    game->num_of_players = num_of_players;
    game->cur_cnt_units = 0;
    game->cur_round = 0;

    for (int i = 0; i < game->num_of_players; i++) {
        game->players[i].id = i + 1;
        game->players[i].gold = 20;
        game->players[i].turn = NOT_TURN_YET;
    }

    // заполняем карту равнинами и пропусками
    for (int i = 0; i <  MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
                game->map[i][j].x = j + 1;
                game->map[i][j].y = MAP_HEIGHT - i;
                game->map[i][j].owner_player_id = 0;
                game->map[i][j].is_discovered = false;
            if ((i + j) % 2) {
                game->map[i][j].terrain = NOT_EXISTS;
            } else {
                game->map[i][j].terrain = TERRAIN_PLAIN;
            }
        }
    }

    // заполняем середину карты деревнями
    int random_village_type;
    bool make_village;
    for (int i = MAP_HEIGHT / 4 - 1; i <=  MAP_HEIGHT * 3 / 4; i++) {
        for (int j = MAP_WIDTH / 4 - 1; j <= MAP_WIDTH * 3 / 4; j++) {
            make_village = (rand() % 5) < 3;
            if ((game->map[i][j].terrain == TERRAIN_PLAIN) && make_village) {
                random_village_type = rand() % 3 + 1;
                switch (random_village_type) {
                    case 1:
                        game->map[i][j].terrain = TERRAIN_VILLAGE_1;
                        break;
                    case 2:
                        game->map[i][j].terrain = TERRAIN_VILLAGE_2;
                        break;
                    case 3:
                        game->map[i][j].terrain = TERRAIN_VILLAGE_3;
                        break;
                }
            }
        }
    }

    // в начале игры еще не все игроки походили
    game->all_players_end_turns = false;

    // игру начинает первый игрок
    game->cur_player_id_turn = game->players[0].id;
    game->players[0].turn = TURN_NOW;
    game->next_unit_id = 1;

    // распределение по замкам
    game->players[0].castle_x = 2;
    game->players[0].castle_y = 1;

    game->players[1].castle_x = 16;
    game->players[1].castle_y = 7;

    game->players[2].castle_x = 16;
    game->players[2].castle_y = 1;

    game->players[3].castle_x = 1;
    game->players[3].castle_y = 8;
}