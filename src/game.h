#ifndef GAME_H
#define GAME_H

#include "unit.h"

#define MAX_CNT_OF_UNITS 64
#define MAP_WIDTH 8
#define MAP_HEIGHT 4

// структура для хранения войска игроков
struct GameState {
    struct Unit all_units[MAX_CNT_OF_UNITS];
    int cur_cnt_units;
};

enum GameError {
    GAME_OK,
    GAME_ERROR_UNIT_LIMIT,
    GAME_ERROR_GOING_BEYOND_BOUNDARIES_MAP,
    GAME_ERROR_NO_SUCH_COORDINATES,
    GAME_ERROR_NO_SUCH_UNIT_ID,
    GAME_ERROR_NOT_ENOUGH_SPEED,
    GAME_ERROR_ALREADY_UNIT_ON_HEX,
    GAME_ERROR_UNKNOWN_UNIT_TYPE
    //GAME_ERROR_EMPTY_PARAMETER,
    //GAME_ERROR_PARAMETER_IS_NOT_NUMBER,
    //GAME_ERROR_TOO_MANY_PARAMETERS
};

void game_init(struct GameState *game);

enum GameError game_create_unit(struct GameState *game, enum UnitType unit_type);

enum GameError game_move(struct GameState *game, int unit_id, int target_x, int target_y);

#endif