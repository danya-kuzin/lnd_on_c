#include "game.h"

enum GameError game_create_unit(struct GameState *game, enum UnitType unit_type) {
    // проверка на достижения предела количества юнитов
    if (game->cur_cnt_units >= MAX_CNT_OF_UNITS) {
        return GAME_ERROR_UNIT_LIMIT;
    }

    // создаем нового юнита
    struct Unit new_unit;
    
    // задаем ему характеристики
    // общие характеристики
    new_unit.id = game->cur_cnt_units + 1;
    new_unit.player_id = game->cur_player_id_turn;
    
    // частные характеристики
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
            break;

        default:
            return GAME_ERROR_UNKNOWN_UNIT_TYPE;
    }

    // при создании юнита его возможное перемещение максимально и равно его скорости
    new_unit.movement_left = new_unit.speed;

    // проверка на достаточное количество золота
    int player_i = game->cur_player_id_turn - 1;
    if (game->players[player_i].gold < new_unit.cost) {
        return GAME_ERROR_NOT_ENOUGH_GOLD;
    } else {
        game->players[player_i].gold -= new_unit.cost;
    }

    // добавляем его в массив юнитов
    game->all_units[game->cur_cnt_units] = new_unit;
    (game->cur_cnt_units)++;
    return GAME_OK;
}