#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "unit.h"
#include "cli_attack.h"

void cli_attack(char param2[], char param3[], 
              struct GameState *game) {

    // проверка на непустые параметры
    if (param2[0] == '\0' || param3[0] == '\0') {
        printf("Error: one of the parameters is empty \n");
        return;
        };
    
    // проверка на то, что параметры - числа
    char *end2, *end3;
    strtol(param2, &end2, 10);
    strtol(param3, &end3, 10);
    if (*end2 != '\0' || *end3 != '\0') {
        printf("Error: one of the parameters is not a number \n");
        return;
        };
    
    // передаем attacker_id и defender_id в ядро игры
    enum GameError error;
    error = game_attack(game, atoi(param2), atoi(param3));
    
    switch (error) {

        case GAME_ERROR_ATTACKER_NOT_BELONG_PLAYER:
            printf("Error: the attacker unit does not belong to attacker player \n");
            break;

        case GAME_ERROR_ATTACKER_NOT_NEAR:
            printf("Error: the attacker unit is not near the defender unit \n");
            break;

        case GAME_ERROR_NO_SUCH_UNIT_ID:
            printf("Error: no such unit id \n");
            break;

        case GAME_ERROR_UNIT_ALREADY_ATTACKED:
            printf("Error: this unit has already attacked \n");
            break;

        case GAME_OK:
            printf("The unit has been successfully attack \n");
            break;

        default:
            printf("Error: unknown error type \n");
            break;
    }
}