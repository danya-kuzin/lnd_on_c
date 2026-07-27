#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "unit.h"
#include "cli_move.h"

void cli_move(char param2[], char param3[], 
              char param4[], struct GameState *game) {

    // проверка на непустые параметры
    if (param2[0] == '\0' || param3[0] == '\0' || param4[0] == '\0') {
        printf("Error: one of the parameters is empty \n");
        return;
        };
    
    // проверка на то, что параметры - числа
    char *end2, *end3, *end4;
    strtol(param2, &end2, 10);
    strtol(param3, &end3, 10);
    strtol(param4, &end4, 10);
    if (*end2 != '\0' || *end3 != '\0' || *end4 != '\0') {
        printf("Error: one of the parameters is not a number \n");
        return;
        };
    
    // передаем unit_id, target_x, target_y в ядро игры
    enum GameError error;
    error = game_move(game, atoi(param2), atoi(param3), atoi(param4));
    
    switch (error) {
        case GAME_ERROR_GOING_BEYOND_BOUNDARIES_MAP:
            printf("Error: going beyond the boundaries of the map \n");
            break;

        case GAME_ERROR_NO_SUCH_COORDINATES:
            printf("Error: there are no such coordinates \n");
            break;

        case GAME_ERROR_NO_SUCH_UNIT_ID:
            printf("Error: there is no such unit_id \n");
            break;
        
        case GAME_ERROR_NOT_ENOUGH_SPEED:
            printf("Error: not enough speed for this type of unit \n");
            break;
        
        case GAME_ERROR_ALREADY_UNIT_ON_HEX:
            printf("Error: there is already a unit on this hex \n");
            break;
        
        case GAME_ERROR_UNKNOWN_UNIT_TYPE:
            printf("Error: unknown unit type \n");
            break;

        case GAME_OK:
            printf("The unit has been successfully moved \n");
            break;

        default:
            printf("Error: unknown error type \n");
            break;
    }
}