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
    struct AttackResult result;
    error = game_attack(game, atoi(param2), atoi(param3), &result);
    
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
            printf("The unit_%d attack unit_%d :\n", 
                    result.attacker_id, result.defender_id);
            printf("------------------------attack------------------------ \n");
            printf("Unit_%d (all attack) = %d(based attack) + %d(RPS) + %d(random bonus) = %d \n", 
                    result.attacker_id, result.attacker_based_attack,
                    result.attacker_bonus_RPS, result.attacker_attack_random_bonus, 
                    result.all_attacker_attack);
            
            printf("Unit_%d (all defence) = %d(based defence) + %d(random bonus) = %d \n", 
                    result.defender_id, result.defender_based_defence,
                    result.defender_defence_random_bonus, 
                    result.all_defender_defence);

            printf("Unit_%d deals (%d damage) to unit_%d \n", 
                    result.attacker_id, result.damage_to_defender, 
                    result.defender_id);
            printf("HP unit_%d: %d -> %d \n",
                    result.defender_id, result.defender_hp_before,
                    result.defender_hp_after);
    
            printf("------------------------contr attack------------------------ \n");
            printf("Unit_%d (all attack) = %d(based attack) + %d(RPS) + %d(random bonus) = %d \n", 
                    result.defender_id, result.defender_based_attack,
                    result.defender_bonus_RPS, result.defender_attack_random_bonus, 
                    result.all_defender_attack);
            
            printf("Unit_%d (all defence) = %d(based defence) + %d(random bonus) = %d \n", 
                    result.attacker_id, result.attacker_based_defence,
                    result.attacker_defence_random_bonus, 
                    result.all_attacker_defence);

            printf("Unit_%d deals (%d damage) to unit_%d \n", 
                    result.defender_id, result.damage_to_attacker, 
                    result.attacker_id);
            printf("HP unit_%d: %d -> %d \n",
                    result.attacker_id, result.attacker_hp_before,
                    result.attacker_hp_after);
                
            printf("------------------------deaths------------------------ \n");
            if (result.defender_dead) {
                printf("Unit_%d is dead \n", result.defender_id);
            }
            if (result.attacker_dead) {
                printf("Unit_%d is dead \n", result.attacker_id);
            } 
            if (!result.defender_dead && !result.attacker_dead) {
                printf("Both units remained alive \n");
            } 

            break;

        default:
            printf("Error: unknown error type \n");
            break;
    }
}