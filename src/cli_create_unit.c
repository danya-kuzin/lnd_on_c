#include <stdio.h>
#include <string.h>
#include "unit.h"
#include "game.h"
#include "cli_create_unit.h"

/*  при такой передаче массива он сам превращается в свой адрес
    то есть функция получает доступ к настоящему массиву, а не к его копии*/
void cli_create_unit(struct GameState *game, char unit_name[]) {

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
        printf("Error: unknown unit type\n");
        return;
    }

    if (error == GAME_OK) {
        printf("The unit was created successfully\n");
    }

    else if (error == GAME_ERROR_UNIT_LIMIT) {
        printf("Error: the unit limit has been reached\n");
    }

    else if (error == GAME_ERROR_NOT_ENOUGH_GOLD) {
        printf("Error: not enough gold to create\n");
    }

    else if (error == GAME_ERROR_SPAWN_HEX_OCCUPIED) {
        printf("Error: castle hex is occupied\n");
    }
}