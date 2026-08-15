#include <stdio.h>
#include <string.h>
#include "unit.h"
#include "game.h"
#include "net_common.h"
#include "server_create_unit.h"

/*  при такой передаче массива он сам превращается в свой адрес
    то есть функция получает доступ к настоящему массиву, а не к его копии*/
void server_create_unit(struct GameState *game, char unit_name[], int client_fd) {

    enum GameError error;

    if (strcmp(unit_name, "mech") == 0){
        error = game_create_unit(game, SWORDSMAN);
    }

    else if (strcmp(unit_name, "kop") == 0){
        error = game_create_unit(game, SPEARMAN);
    }

    else if (strcmp(unit_name, "cav") == 0){
        error = game_create_unit(game, CAVALRY);
    }

    else if (strcmp(unit_name, "arch") == 0){
        error = game_create_unit(game, ARCHER);
    }

    else if (strcmp(unit_name, "scout") == 0){
        error = game_create_unit(game, SCOUT);
    }

    else {
        const char *message = "Error: unknown unit type\n";
        send_all(client_fd, message, strlen(message));
        return;
    }

    if (error == GAME_OK) {
        const char *message = "The unit was created successfully\n";
        send_all(client_fd, message, strlen(message));
    }

    else if (error == GAME_ERROR_UNIT_LIMIT) {
        const char *message = "Error: the unit limit has been reached\n";
        send_all(client_fd, message, strlen(message));
    }

    else if (error == GAME_ERROR_NOT_ENOUGH_GOLD) {
        const char *message = "Error: not enough gold to create\n";
        send_all(client_fd, message, strlen(message));
    }

    else if (error == GAME_ERROR_SPAWN_HEX_OCCUPIED) {
        const char *message = "Error: castle hex is occupied\n";
        send_all(client_fd, message, strlen(message));
    }
}