#include <stdio.h>
#include <stdlib.h>
#include "unit.h"
#include "game.h"
#include "cli_print_units.h"
#include "cli_status.h"

// функция для печати буквы перед индексом
char unit_type_letter(enum UnitType type) {
    switch (type) {
        case SWORDSMAN:
            return 'm';
            break;
        case SPEARMAN:
            return 'k';
            break;
        case ARCHER:
            return 'a';
            break;
        case CAVALRY:
            return 'c';
            break;
        case SCOUT:
            return 's';
            break;
        default:
            return '#';
            break;
    }
}

// функция для распределения игроков по цветам
const char *cli_player_color(int player_id)
{
    switch (player_id) {
        case 1:
            return COLOR_RED;
            break;
        case 2:
            return COLOR_GREEN;
            break;
        case 3:
            return COLOR_YELLOW;
            break;
        case 4:
            return COLOR_BLUE;
            break;
        default:
            return COLOR_RESET;
            break;
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

    for (int i = 0; i < MAP_HEIGHT; i++) {
        printf("|   %d ", cur_map_height);

        for (int j = 0; j < MAP_WIDTH; j++) {
            flag_no_unit = 1;

            // печать гекса/пропуска/юнита
            for (int i = 0; i < game->cur_cnt_units; i++) {
                if (game->all_units[i].hex_x == cur_map_width &&
                    game->all_units[i].hex_y == cur_map_height) {

                    printf("%s", cli_player_color(game->all_units[i].player_id));
                    printf("%c%d", unit_type_letter(game->all_units[i].type), game->all_units[i].id);
                    printf("%s", COLOR_RESET);

                    if (game->all_units[i].id < 10) {
                        printf(" ");
                    }

                    flag_no_unit = 0;

                }
            }

            if (flag_no_unit == 1) {
                if ((game->map[i][j].is_discovered == false) &&
                    (game->map[i][j].terrain != NOT_EXISTS)) {
                    printf(" ? ");
                }

                else {
                    switch (game->map[i][j].terrain) {
                        case NOT_EXISTS:
                            printf("   ");
                            break;
                        case TERRAIN_PLAIN:
                            printf(" P ");
                            break;
                        case TERRAIN_FOREST:
                            printf(" F ");
                            break;
                        case TERRAIN_HILL:
                            printf(" H ");
                            break;
                        case TERRAIN_MOUNTAIN:
                            printf(" M ");
                            break;

                        // деревни цвета владельца деревни
                        case TERRAIN_VILLAGE_1:
                            printf("%s", cli_player_color(game->map[i][j].owner_player_id));
                            printf(" V1");
                            printf("%s", COLOR_RESET);
                            break;
                        case TERRAIN_VILLAGE_2:
                            printf("%s", cli_player_color(game->map[i][j].owner_player_id));
                            printf(" V2");
                            printf("%s", COLOR_RESET);
                            break;
                        case TERRAIN_VILLAGE_3:
                            printf("%s", cli_player_color(game->map[i][j].owner_player_id));
                            printf(" V3");
                            printf("%s", COLOR_RESET);
                            break;
                    }
                }
            }
        

            cur_map_width++;
        }

        // переход на новую строку
        printf("  |\n| ");
        for (int i = 1; i <= (MAP_WIDTH + 2) * 3; i++) {
            printf(" ");
        }
        printf("|\n");
        cur_map_height--;
        cur_map_width = 1;
    }

    // блок чисто форматирования
    printf("|      ");
    for (int i = 1; i <= MAP_WIDTH; i++) {
        if (i < 10) {
            printf("%d  ", i);
        }
        else if (i < 100) {
            printf("%d ", i);
        }
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