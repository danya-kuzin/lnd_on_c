#include <stdio.h>
#include <stdlib.h>
#include "game.h"

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

    // сама команда attack
    int damage;
    for (int i = 0; i < game->cur_cnt_units; i++) {
        if (game->all_units[i].id == defender_id) {
            damage = cur_attacker_unit.attack - cur_defender_unit.defence;
            if (damage > 0) {
                game->all_units[i].health -= damage;
            }
        }

        if (game->all_units[i].id == attacker_id) {
            damage = cur_defender_unit.attack - cur_attacker_unit.defence;
            if (damage > 0) {
                game->all_units[i].health -= damage;
                break;
            }
        }
    }

    // проверяем умер ли кто-то
    for (int i = 0; i < game->cur_cnt_units; i++) {
        if ((game->all_units[i].id == defender_id) && 
            (game->all_units[i].health <= 0)){
            
        }

        if ((game->all_units[i].id == attacker_id) && 
            (game->all_units[i].health <= 0)){
            
        }
    }

    return GAME_OK;
}