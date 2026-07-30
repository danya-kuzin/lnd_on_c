#include <stdio.h>
#include <stdlib.h>
#include "unit.h"
#include "game.h"
#include "cli_print_units.h"
#include "cli_status.h"


// функция для распределения игроков по цветам
const char *cli_player_color(int player_id)
{
    switch (player_id) {
        case 1:
            return COLOR_RED;
        case 2:
            return COLOR_GREEN;
        case 3:
            return COLOR_YELLOW;
        case 4:
            return COLOR_BLUE;
        default:
            return COLOR_RESET;
    }
}


void cli_status(struct GameState *game){
    
    // блок чисто форматирования
    printf("\n\n\n ");
    for (int i = 1; i <= (MAP_WIDTH + 2) * 3 + 1; i++) {
        printf("_");
    }
    printf("\n|");
    for (int i = 1; i <= (MAP_WIDTH + 2) * 3; i++) {
        printf(" ");
    }
    printf(" |\n");


    // блок форматирования + генерация карты
    int cur_map_width = 1;
    int cur_map_height = MAP_HEIGHT;
    int flag_no_unit;

    for (int i = 1; i <= MAP_WIDTH * MAP_HEIGHT; i++) {
        flag_no_unit = 1;

        if ((i - 1) % MAP_WIDTH == 0) {
            printf("|   %d  ", cur_map_height);
        }


        // печать гекса/пропуска/юнита
        if (abs(cur_map_height - cur_map_width) % 2 == 0) {
            printf("   ");
        } 
        else {
            for (int i = 0; i < game->cur_cnt_units; i++) {
                if (game->all_units[i].hex_x == cur_map_width &&
                    game->all_units[i].hex_y == cur_map_height) {
                    
                    printf("%s", cli_player_color(game->all_units[i].player_id));
                    printf("%d", game->all_units[i].id);
                    printf("%s", COLOR_RESET);

                    flag_no_unit = 0;

                    if (game->all_units[i].id > 9) {
                        printf(" ");
                    }
                    else {
                        printf("  ");
                    }
                }
            }
            if (flag_no_unit == 1) {
                printf("X  ");
            }
        }

        cur_map_width++;

        if (i % MAP_WIDTH == 0) {
            printf(" |\n| ");
            for (int i = 1; i <= (MAP_WIDTH + 2) * 3; i++) {
                printf(" ");
            }
            printf("|\n");
            cur_map_height--;
            cur_map_width = 1;
        }
    }

    // блок чисто форматирования
    printf("|      ");
    for (int i = 1; i <= MAP_WIDTH; i++) {
        printf("%d  ", i);
    }
    printf(" |\n|");
    for (int i = 1; i <= (MAP_WIDTH + 2) * 3 + 1; i++) {
        printf("_");
    }
    printf("|\n\n");

    // блок вывода золота игроков
    for (int i = 0; i < game->num_of_players; i++) {
        printf("player %d: %dG\n", game->players[i].id, game->players[i].gold);
    }

    // блок вывода всех юнитов
    cli_print_units(game);
}