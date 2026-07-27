#include "game.h"

enum GameError game_create_unit(struct GameState *game, enum UnitType unit_type) {
    // проверка на достижения предела количества юнитов
    if (game->cur_cnt_units >= MAX_CNT_OF_UNITS) {
        return GAME_ERROR_UNIT_LIMIT;
    }

    // создаем нового юнита
    struct Unit new_unit;
    
    // задаем ему характеристики
    switch (unit_type) {
        case SWORDSMAN:
            new_unit.type = SWORDSMAN;
            new_unit.hex_x = 2;
            new_unit.hex_y = 1;
            new_unit.cost = 6;
            new_unit.health = 3;
            new_unit.attack = 2;
            new_unit.defence = 1;
            new_unit.speed = 1;
            new_unit.id = game->cur_cnt_units + 1;
            break;

        case SPEARMAN:
            new_unit.type = SPEARMAN;
            new_unit.hex_x = 2;
            new_unit.hex_y = 1;
            new_unit.cost = 8;
            new_unit.health = 4;
            new_unit.attack = 3;
            new_unit.defence = 2;
            new_unit.speed = 1;
            new_unit.id = game->cur_cnt_units + 1;
            break;

        default:
            return GAME_ERROR_UNKNOWN_UNIT_TYPE;
    }

    // добавляем его в массив юнитов
    game->all_units[game->cur_cnt_units] = new_unit;
    (game->cur_cnt_units)++;
    return GAME_OK;
}