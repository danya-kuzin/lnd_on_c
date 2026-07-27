#include <stdio.h>
#include "game.h"

void cli_print_units(struct GameState *game)
{
    for (int i = 0; i < game->cur_cnt_units; i++) {
        printf(
            "unit %d: type=%d pos=(%d, %d) hp=%d atk=%d def=%d speed=%d cost=%d id=%d\n",
            i + 1,
            game->all_units[i].type,
            game->all_units[i].hex_x,
            game->all_units[i].hex_y,
            game->all_units[i].health,
            game->all_units[i].attack,
            game->all_units[i].defence,
            game->all_units[i].speed,
            game->all_units[i].cost,
            game->all_units[i].id
        );
    }
}

