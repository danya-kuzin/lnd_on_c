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
#include <time.h>

// мои заголовки
#include "cli_parsing.h"
#include "unit.h"
#include "cli_command_handler.h"
#include "game.h"


#define LENGTH_INPUT_STR 20

int main()
{
    // запуск генерации псевдослучайных чисел
    srand(time(NULL)); 

    // переменные для старта игры
    char start_input[10];  
    char num_of_players_input[10]; 

    // переменные для парсинга команды
    int num_of_players;
    char input[LENGTH_INPUT_STR];
    char param1[LENGTH_INPUT_STR];
    char param2[LENGTH_INPUT_STR];
    char param3[LENGTH_INPUT_STR];
    char param4[LENGTH_INPUT_STR];
    enum CliResult continue_or_finish = CLI_CONTINUE;

    // вход в игру
    printf("\n\n\n");
    while (true) {
        printf("Enter the number of players: ");
        fgets(num_of_players_input, sizeof(num_of_players_input), stdin);
        num_of_players = num_of_players_input[0] - '0';

        // проверка на выход за границы нормального количества игороков
        if ((num_of_players < 2) || (num_of_players > MAX_CNT_OF_PLAYERS)) {
            printf("\nError: incorrect number of players \n");
        } else {
            break;
        }
    }

    while (true) {
        printf("\nPrint 'start' to start the LnD game: ");
        fgets(start_input, sizeof(start_input), stdin);

        if (strcmp(start_input, "start\n") == 0) {
            printf("Good luck! (to view the list of commands write 'help')\n\n");
            break;
        } else
            printf("Try again\n\n");

    }

    // инициализация игры
    struct GameState game;
    game_init(&game, num_of_players);

    // основной цикл
    while (continue_or_finish == CLI_CONTINUE) {

        // номер раунда
        game.cur_round++;
        printf("\n\n\n-------------ROUND %d-------------\n", game.cur_round);

        game.all_players_end_turns = false;
        while (game.all_players_end_turns == false) {

            printf("Player %d: ", game.cur_player_id_turn);

            // очищаем парамеры
            param1[0] = '\0';
            param2[0] = '\0';
            param3[0] = '\0';
            param4[0] = '\0';

            // читаем строку и парсим параметры
            cli_parsing(LENGTH_INPUT_STR, input, param1, param2, param3, param4);
            /* printf("param1: %s \n", param1);
            printf("param2: %s \n", param2);
            printf("param3: %s \n", param3);
            printf("param4: %s \n", param4); */
            
            // отправляем команду в расределитель команд по программам для их обработки
            continue_or_finish = cli_handle_command(&game, param1, param2, param3, param4);
            if (continue_or_finish == CLI_FINISH) {
                break;
            }

            printf("\n");
        }

    }

    return 0;
}
