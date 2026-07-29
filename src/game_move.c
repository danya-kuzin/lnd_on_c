#include <stdio.h>
#include <stdlib.h>
#include "game.h"

enum GameError game_move(struct GameState *game, int unit_id, int target_x, int target_y) {
    // проверка на выход за границы карты
    if (target_x >  MAP_WIDTH || target_y >  MAP_HEIGHT) {
        return GAME_ERROR_GOING_BEYOND_BOUNDARIES_MAP;
    }

    // проверка на несуществующие коордиинаты
    if ( target_x < 1 || target_y < 1 || 
        (abs(target_x - target_y) % 2 == 0) ) {
        return GAME_ERROR_NO_SUCH_COORDINATES;
        }


    // находим нашего юнита
    struct Unit cur_unit;
    int flag_id = 0;
    for (int i = 0; i < game->cur_cnt_units; i++) {
        if (game->all_units[i].id == unit_id) {
            cur_unit = game->all_units[i];
            flag_id = 1;

            // проверка на попытку воспользоваться чужим юнитом
            if (game->all_units[i].player_id != game->cur_player_id_turn) {
                return GAME_ERROR_NOT_YOUR_UNIT;
            }
        }
    }

    // проверка на несуществующий id
    if (flag_id == 0) {
        return GAME_ERROR_NO_SUCH_UNIT_ID;
    }

    // проверка на возможности по скорости
    int delta_x = abs(cur_unit.hex_x - target_x);
    int delta_y = abs(cur_unit.hex_y - target_y);
    if (delta_x + delta_y > cur_unit.speed * 2){
        return GAME_ERROR_NOT_ENOUGH_SPEED;
    }
    
    // проверка на попытку поставить отряд на занятый гекс
    for (int i = 0; i < game->cur_cnt_units; i++) {
        if (target_x == game->all_units[i].hex_x && 
            target_y == game->all_units[i].hex_y) {
            return GAME_ERROR_ALREADY_UNIT_ON_HEX;
        }
    } 

    // сама команда move
    for (int i = 0; i < game->cur_cnt_units; i++) {
        if (game->all_units[i].id == unit_id) {
            game->all_units[i].hex_x = target_x;
            game->all_units[i].hex_y = target_y;
            break;
        }
    }

    return GAME_OK;
}