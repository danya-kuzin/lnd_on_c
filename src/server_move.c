#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "unit.h"
#include "net_common.h"
#include "server_move.h"

void server_move(char param2[], char param3[], char param4[],
              int client_fd, struct GameState *game) {

    // проверка на непустые параметры
    if (param2[0] == '\0' || param3[0] == '\0' || param4[0] == '\0') {
        const char *message = "Error: one of the parameters is empty \n";
        send_all(client_fd, message, strlen(message));
        return;
        };
    
    // проверка на то, что параметры - числа
    char *end2, *end3, *end4;
    strtol(param2, &end2, 10);
    strtol(param3, &end3, 10);
    strtol(param4, &end4, 10);
    if (*end2 != '\0' || *end3 != '\0' || *end4 != '\0') {
        const char *message = "Error: one of the parameters is not a number \n";
        send_all(client_fd, message, strlen(message));
        return;
        };
    
    // передаем unit_id, target_x, target_y в ядро игры
    enum GameError error;
    error = game_move(game, atoi(param2), atoi(param3), atoi(param4));
    
    const char *message = NULL;
    switch (error) {
        case GAME_ERROR_GOING_BEYOND_BOUNDARIES_MAP:
            message = "Error: going beyond the boundaries of the map \n";
            send_all(client_fd, message, strlen(message));
            break;

        case GAME_ERROR_NO_SUCH_COORDINATES:
            message = "Error: there are no such coordinates \n";
            send_all(client_fd, message, strlen(message));
            break;

        case GAME_ERROR_NO_SUCH_UNIT_ID:
            message = "Error: there is no such unit_id \n";
            send_all(client_fd, message, strlen(message));
            break;
        
        case GAME_ERROR_NOT_ENOUGH_SPEED:
            message = "Error: not enough speed for this type of unit \n";
            send_all(client_fd, message, strlen(message));
            break;
        
        case GAME_ERROR_ALREADY_UNIT_ON_HEX:
            message = "Error: there is already a unit on this hex \n";
            send_all(client_fd, message, strlen(message));
            break;
        
        case GAME_ERROR_UNKNOWN_UNIT_TYPE:
            message = "Error: unknown unit type \n";
            send_all(client_fd, message, strlen(message));
            break;

        case GAME_ERROR_NOT_YOUR_UNIT:
            message = "Error: the selected unit for movement does not belong to you \n";
            send_all(client_fd, message, strlen(message));
            break;

        case GAME_OK:
            message = "The unit has been successfully moved \n";
            send_all(client_fd, message, strlen(message));
            break;

        default:
            message = "Error: unknown error type \n";
            send_all(client_fd, message, strlen(message));
            break;
    }
}