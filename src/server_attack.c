#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "unit.h"
#include "net_common.h"
#include "server_attack.h"

void server_attack(char param2[], char param3[],
                   struct GameState *game, int client_fd) {
    const char *message = NULL;

    if (param2[0] == '\0' || param3[0] == '\0') {
        message = "Error: one of the parameters is empty \n";
        send_all(client_fd, message, strlen(message));
        return;
    }

    char *end2, *end3;
    strtol(param2, &end2, 10);
    strtol(param3, &end3, 10);

    if (*end2 != '\0' || *end3 != '\0') {
        message = "Error: one of the parameters is not a number \n";
        send_all(client_fd, message, strlen(message));
        return;
    }

    enum GameError error;
    struct AttackResult result;
    error = game_attack(game, atoi(param2), atoi(param3), &result);

    switch (error) {
        case GAME_ERROR_ATTACKER_NOT_BELONG_PLAYER:
            message = "Error: the attacker unit does not belong to attacker player \n";
            send_all(client_fd, message, strlen(message));
            break;

        case GAME_ERROR_ATTACKER_NOT_NEAR:
            message = "Error: the attacker unit is not near the defender unit \n";
            send_all(client_fd, message, strlen(message));
            break;

        case GAME_ERROR_NO_SUCH_UNIT_ID:
            message = "Error: no such unit id \n";
            send_all(client_fd, message, strlen(message));
            break;

        case GAME_ERROR_UNIT_ALREADY_ATTACKED:
            message = "Error: this unit has already attacked \n";
            send_all(client_fd, message, strlen(message));
            break;

        case GAME_OK: {
            char buffer[4096];

            snprintf(buffer, sizeof(buffer),
                "The unit_%d attack unit_%d :\n"
                "------------------------attack------------------------ \n"
                "Unit_%d (all attack) = %d(based attack) + %d(RPS) + %d(random bonus) = %d \n"
                "Unit_%d (all defence) = %d(based defence) + %d(random bonus) = %d \n"
                "Unit_%d deals (%d damage) to unit_%d \n"
                "HP unit_%d: %d -> %d \n"
                "------------------------contr attack------------------------ \n"
                "Unit_%d (all attack) = %d(based attack) + %d(RPS) + %d(random bonus) = %d \n"
                "Unit_%d (all defence) = %d(based defence) + %d(random bonus) = %d \n"
                "Unit_%d deals (%d damage) to unit_%d \n"
                "HP unit_%d: %d -> %d \n"
                "------------------------deaths------------------------ \n",
                result.attacker_id, result.defender_id,
                result.attacker_id, result.attacker_based_attack,
                result.attacker_bonus_RPS, result.attacker_attack_random_bonus,
                result.all_attacker_attack,
                result.defender_id, result.defender_based_defence,
                result.defender_defence_random_bonus,
                result.all_defender_defence,
                result.attacker_id, result.damage_to_defender,
                result.defender_id,
                result.defender_id, result.defender_hp_before,
                result.defender_hp_after,
                result.defender_id, result.defender_based_attack,
                result.defender_bonus_RPS, result.defender_attack_random_bonus,
                result.all_defender_attack,
                result.attacker_id, result.attacker_based_defence,
                result.attacker_defence_random_bonus,
                result.all_attacker_defence,
                result.defender_id, result.damage_to_attacker,
                result.attacker_id,
                result.attacker_id, result.attacker_hp_before,
                result.attacker_hp_after
            );

            send_all(client_fd, buffer, strlen(buffer));

            if (result.defender_dead) {
                snprintf(buffer, sizeof(buffer), "Unit_%d is dead \n", result.defender_id);
                send_all(client_fd, buffer, strlen(buffer));
            }

            if (result.attacker_dead) {
                snprintf(buffer, sizeof(buffer), "Unit_%d is dead \n", result.attacker_id);
                send_all(client_fd, buffer, strlen(buffer));
            }

            if (!result.defender_dead && !result.attacker_dead) {
                message = "Both units remained alive \n";
                send_all(client_fd, message, strlen(message));
            }

            break;
        }

        default:
            message = "Error: unknown error type \n";
            send_all(client_fd, message, strlen(message));
            break;
    }
}