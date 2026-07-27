// дабл ю дабл ю
    // Красный текст
    //printf("\x1b[31m");
    //printf("Этот текст красный");
    //printf("\x1b[0m"); // Сброс

// системные заголовки
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// мои заголовки
#include "cli_parsing.h"
#include "unit.h"
#include "cli_print_units.h"
#include "cli_create_unit.h"
#include "cli_help.h"
#include "cli_move.h"
#include "game.h"

#define LENGTH_INPUT_STR 20

void com_status(struct Unit all_units[], int cur_cnt_units, 
            int map_width, int map_height){
    
    // блок чисто форматирования
    printf("\n\n\n ");
    for (int i = 1; i <= (map_width + 2) * 3 + 1; i++) {
        printf("_");
    }
    printf("\n|");
    for (int i = 1; i <= (map_width + 2) * 3; i++) {
        printf(" ");
    }
    printf(" |\n");


    // блок форматирования + генерация карты
    int cur_map_width = 1;
    int cur_map_height = map_height;
    int flag_no_unit;

    for (int i = 1; i <= map_width * map_height; i++) {
        flag_no_unit = 1;

        if ((i - 1) % map_width == 0) {
            printf("|   %d  ", cur_map_height);
        }


        // печать гекса/пропуска/юнита
        if (abs(cur_map_height - cur_map_width) % 2 == 0) {
            printf("   ");
        } 
        else {
            for (int i = 0; i <= cur_cnt_units; i++) {
                if (all_units[i].hex_x == cur_map_width &&
                    all_units[i].hex_y == cur_map_height) {
                    printf("%d", all_units[i].id);
                    flag_no_unit = 0;

                    if (all_units[i].id > 9) {
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

        if (i % map_width == 0) {
            printf(" |\n| ");
            for (int i = 1; i <= (map_width + 2) * 3; i++) {
                printf(" ");
            }
            printf("|\n");
            cur_map_height--;
            cur_map_width = 1;
        }
    }

    // блок чисто форматирования
    printf("|      ");
    for (int i = 1; i <= map_width; i++) {
        printf("%d  ", i);
    }
    printf(" |\n|");
    for (int i = 1; i <= (map_width + 2) * 3 + 1; i++) {
        printf("_");
    }
    printf("|\n\n");
}

int main()
{

    // переменные для старта игры
    char start_input[10];   

    // инициализация игры
    struct GameState game;
    game_init(&game);

    // переменные для парсинга команды
    char input[LENGTH_INPUT_STR];
    char param1[LENGTH_INPUT_STR];
    char param2[LENGTH_INPUT_STR];
    char param3[LENGTH_INPUT_STR];
    char param4[LENGTH_INPUT_STR];
    bool not_finish = true;

    // вход в игру
    while (true) {

        printf("Print 'start' to start the LnD game: ");
        fgets(start_input, sizeof(start_input), stdin);

        if (strcmp(start_input, "start\n") == 0) {
            printf("Good luck! (to view the list of commands write 'help')\n\n");
            break;
        } else
            printf("Try again\n\n");

    }

    // основной цикл
    while (not_finish) {

        // очищаем парамеры
        param1[0] = '\0';
        param2[0] = '\0';
        param3[0] = '\0';
        param4[0] = '\0';

        // читаем строку и парсим параметры
        str_read_and_parsing(LENGTH_INPUT_STR, input, param1, param2, param3, param4);
        printf("param1: %s \n", param1);
        printf("param2: %s \n", param2);
        printf("param3: %s \n", param3);
        printf("param4: %s \n", param4);
        
        // проверка введенных команд на корректность
        if (strcmp(param1, "create") == 0) {
            cli_create_unit(&game, param2);
            
            cli_print_units(game.all_units, game.cur_cnt_units);
        }

        else if (strcmp(param1, "help") == 0) {
            cli_help();
        }

        else if (strcmp(param1, "move") == 0) {
            cli_move(param2, param3, param4, &game);
        }

        else if (strcmp(param1, "status") == 0) {
            com_status(game.all_units, game.cur_cnt_units, MAP_WIDTH, MAP_HEIGHT);
        }

        else if (strcmp(param1, "finish") == 0) {
            printf("Congratulations on the end of the LnD game\n");
            break;
        }

        else
            printf("Command is not correct. Try again\n");


        printf("\n");
    }

    return 0;
}
