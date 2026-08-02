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

enum GameError game_attack(struct GameState *game, int attacker_id, int defender_id,
                            struct AttackResult *result) {

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
    int distance =  (delta_x + delta_y) / 2;
    if (distance > cur_attacker_unit.attack_range) {
        return GAME_ERROR_ATTACKER_NOT_NEAR;
    }

    // проверка на то, что это первая атака за этот ход
    if (cur_attacker_unit.attack_flag == true) {
        return GAME_ERROR_UNIT_ALREADY_ATTACKED;
    }

    // сама команда attack
    int damage;
    int defender_index = -1;
    int attacker_index = -1;
    *result = (struct AttackResult){0};  // обнуляем result

    // начинаем запонять result для вывода
    result->attacker_id = attacker_id;
    result->attacker_hp_before = cur_attacker_unit.health;
    result->attacker_based_attack = cur_attacker_unit.attack;
    result->attacker_based_defence = cur_attacker_unit.defence;

    if (cur_attacker_unit.attack_RPS_bonus_UT == cur_defender_unit.type) {
        result->attacker_bonus_RPS = cur_attacker_unit.attack_RPS_bonus;
    } else {
        result->attacker_bonus_RPS = 0;
    } 

    result->defender_id = defender_id;
    result->defender_hp_before = cur_defender_unit.health;
    result->defender_based_attack = cur_defender_unit.attack;
    result->defender_based_defence = cur_defender_unit.defence;

    if (cur_defender_unit.attack_RPS_bonus_UT == cur_attacker_unit.type) {
        result->defender_bonus_RPS = cur_defender_unit.attack_RPS_bonus;
    } else {
        result->defender_bonus_RPS = 0;
    } 

    // генерируем рандомные бонусы к атаке и защите
    if (cur_attacker_unit.max_attack_random_bonus > 0) {
        result->attacker_attack_random_bonus =
            rand() % (cur_attacker_unit.max_attack_random_bonus + 1);
    } else {
        result->attacker_attack_random_bonus = 0;
    }

    if (cur_defender_unit.max_attack_random_bonus > 0) {
        result->defender_attack_random_bonus =
            rand() % (cur_defender_unit.max_attack_random_bonus + 1);
    } else {
        result->defender_attack_random_bonus = 0;
    }

    if (cur_attacker_unit.max_defence_random_bonus > 0) {
        result->attacker_defence_random_bonus =
            rand() % (cur_attacker_unit.max_defence_random_bonus + 1);
    } else {
        result->attacker_defence_random_bonus = 0;
    }

    if (cur_defender_unit.max_defence_random_bonus > 0) {
        result->defender_defence_random_bonus =
            rand() % (cur_defender_unit.max_defence_random_bonus + 1);
    } else {
        result->defender_defence_random_bonus = 0;
    }

    // считаем общие показатели атаки и защиты
    result->all_attacker_attack = cur_attacker_unit.attack 
                                + result->attacker_attack_random_bonus
                                + result->attacker_bonus_RPS;

    result->all_attacker_defence = cur_attacker_unit.defence
                                + result->attacker_defence_random_bonus;

    result->all_defender_attack = cur_defender_unit.attack 
                                + result->defender_attack_random_bonus
                                + result->defender_bonus_RPS;

    result->all_defender_defence = cur_defender_unit.defence
                                + result->defender_defence_random_bonus;

    for (int i = 0; i < game->cur_cnt_units; i++) {
        if (game->all_units[i].id == defender_id) {
            
            damage = result->all_attacker_attack - result->all_defender_defence;
            defender_index = i;
    
            if (damage > 0) {
                game->all_units[i].health -= damage;
                result->defender_hp_after = game->all_units[i].health;
                result->damage_to_defender = damage;
            } else {
                result->defender_hp_after = game->all_units[i].health;
                result->damage_to_defender = 0;
            }
        }

        if (game->all_units[i].id == attacker_id) {
            damage = result->all_defender_attack - result->all_attacker_defence;
            attacker_index = i;
            game->all_units[i].attack_flag = true;

            // distance == 1 то есть ответка прилетает только если defender рядом
            if ((damage > 0) && (distance == 1)) {
                game->all_units[i].health -= damage;
                result->attacker_hp_after = game->all_units[i].health;
                result->damage_to_attacker = damage;
            } else {
                result->attacker_hp_after = game->all_units[i].health;
                result->damage_to_attacker = 0;
            }
        }
    }

    // удаляем погибшие отряды
    result->defender_dead = result->defender_hp_after <= 0;
    result->attacker_dead = result->attacker_hp_after <= 0;

    if (attacker_index == defender_index) {
        if (game->all_units[attacker_index].health <= 0) {
            delete_dead_unit(game, attacker_index);
        }
        return GAME_OK;
    }

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