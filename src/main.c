// дабл ю дабл ю
    // Красный текст
    //printf("\x1b[31m");
    //printf("Этот текст красный");
    //printf("\x1b[0m"); // Сброс

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "str_read_and_parsing.h"

#define LENGTH_INPUT_STR 20


int main()
{
    char start_input[10];


    char input[LENGTH_INPUT_STR];
    char param1[LENGTH_INPUT_STR];
    char param2[LENGTH_INPUT_STR];
    char param3[LENGTH_INPUT_STR];
    bool not_finish = true;

    // вход в игру
    while (true) {

        printf("Print 'start' to start the LnD game: ");
        fgets(start_input, sizeof(start_input), stdin);

        if (strcmp(start_input, "start\n") == 0) {
            printf("Good luck!\n\n");
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

        // читаем строку и парсим параметры
        str_read_and_parsing(LENGTH_INPUT_STR, input, param1, param2, param3);
        printf("param1: %s \n", param1);
        printf("param2: %s \n", param2);
        printf("param3: %s \n", param3);
        
        // проверка введенных команд на корректность
        if (strcmp(param1, "move") == 0) {
            printf("move WW \n");
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
