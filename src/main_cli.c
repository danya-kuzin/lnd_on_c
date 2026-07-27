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
#include "cli_command_handler.h"
#include "game.h"

#define LENGTH_INPUT_STR 20

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
    enum CliResult continue_or_finish = CLI_CONTINUE;

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
    while (continue_or_finish == CLI_CONTINUE) {

        // очищаем парамеры
        param1[0] = '\0';
        param2[0] = '\0';
        param3[0] = '\0';
        param4[0] = '\0';

        // читаем строку и парсим параметры
        cli_parsing(LENGTH_INPUT_STR, input, param1, param2, param3, param4);
        printf("param1: %s \n", param1);
        printf("param2: %s \n", param2);
        printf("param3: %s \n", param3);
        printf("param4: %s \n", param4);
        
        continue_or_finish = cli_handle_command(&game, param1, param2, param3, param4);

        printf("\n");
    }

    return 0;
}
