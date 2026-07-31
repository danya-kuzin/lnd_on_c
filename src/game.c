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

    // в начале игры еще не все игроки походили
    game->all_players_end_turns = false;

    // игру начинает первый игрок
    game->cur_player_id_turn = game->players[0].id;
    game->players[0].turn = TURN_NOW;
    game->next_unit_id = 1;

    // распределение по замкам
    game->players[0].castle_x = 2;
    game->players[0].castle_y = 1;

    game->players[1].castle_x = 8;
    game->players[1].castle_y = 3;

    game->players[2].castle_x = 1;
    game->players[2].castle_y = 4;

    game->players[3].castle_x = 8;
    game->players[3].castle_y = 1;
}