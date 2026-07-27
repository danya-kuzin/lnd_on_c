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
}