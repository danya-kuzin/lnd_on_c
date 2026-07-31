#include <stdio.h>
#include <stdlib.h>
#include "game.h"

// функция удаления умершего отряда с индексом index
void delete_dead_unit(struct GameState *game, int index) {
    for (int i = index; i < game->cur_cnt_units - 1; i++) {
        game->all_units[i] = game->all_units[i + 1];
    }
    game->cur_cnt_units--;

    return;
}

enum GameError game_attack(struct GameState *game, int attacker_id, int defender_id) {

    // находим атакующего и защищающегося юнита
    struct Unit cur_attacker_unit;
    struct Unit cur_defender_unit;
    int flag_attacker = 0;
    int flag_defender = 0;
    for (int i = 0; i < game->cur_cnt_units; i++) {
        if (game->all_units[i].id == attacker_id) {
            cur_attacker_unit = game->all_units[i];
            flag_attacker = 1;

            // проверка на попытку воспользоваться чужим юнитом
            if (game->all_units[i].player_id != game->cur_player_id_turn) {
                return GAME_ERROR_ATTACKER_NOT_BELONG_PLAYER;
            }
        }

        if (game->all_units[i].id == defender_id) {
            cur_defender_unit = game->all_units[i];
            flag_defender = 1;
        }
    }

    // проверка на несуществующий id
    if ((flag_attacker == 0) || (flag_defender == 0)) {
        return GAME_ERROR_NO_SUCH_UNIT_ID;
    }
    
    // проверка на то, что атакующий рядом с защищающимся
    int delta_x = abs(cur_defender_unit.hex_x - cur_attacker_unit.hex_x);
    int delta_y = abs(cur_defender_unit.hex_y - cur_attacker_unit.hex_y);
    if ((delta_x + delta_y) != 2) {
        return GAME_ERROR_ATTACKER_NOT_NEAR;
    }

    // проверка на то, что это первая атака за этот ход
    if (cur_attacker_unit.attack_flag == true) {
        return GAME_ERROR_UNIT_ALREADY_ATTACKED;
    }

    // сама команда attack
    int damage;
    int defender_index;
    int attacker_index;
    for (int i = 0; i < game->cur_cnt_units; i++) {
        if (game->all_units[i].id == defender_id) {
            damage = cur_attacker_unit.attack - cur_defender_unit.defence;
            defender_index = i;
    
            if (damage > 0) {
                game->all_units[i].health -= damage;
            }
        }

        if (game->all_units[i].id == attacker_id) {
            damage = cur_defender_unit.attack - cur_attacker_unit.defence;
            attacker_index = i;
            game->all_units[i].attack_flag = true;
            if (damage > 0) {
                game->all_units[i].health -= damage;
            }
        }
    }

    // удаляем погибшие отряды
    if (defender_index > attacker_index) {
        if (game->all_units[defender_index].health <= 0) {
                delete_dead_unit(game, defender_index);
        }

        if (game->all_units[attacker_index].health <= 0) {
                delete_dead_unit(game, attacker_index);
        }
    } else {
        if (game->all_units[attacker_index].health <= 0) {
                delete_dead_unit(game, attacker_index);
        }

        if (game->all_units[defender_index].health <= 0) {
                delete_dead_unit(game, defender_index);
        }
    }
 
    return GAME_OK;
}