#include <stdio.h>
#include <stdlib.h>
#include "unit.h"
#include "game.h"
#include "cli_status.h"

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
            for (int i = 0; i <= game->cur_cnt_units; i++) {
                if (game->all_units[i].hex_x == cur_map_width &&
                    game->all_units[i].hex_y == cur_map_height) {
                    printf("%d", game->all_units[i].id);
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
}