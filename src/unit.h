#ifndef UNIT_H
#define UNIT_H

#include <stdbool.h>

enum UnitType {
    SWORDSMAN,
    SPEARMAN,
    ARCHER,
    CAVALRY,
    SCOUT,
    NO_TYPE
};

struct Unit {
    enum UnitType type;
    int hex_x;
    int hex_y;
    int cost;
    int health;
    int attack;
    int defence;
    int speed;
    int id;
    int player_id;
    int movement_left;
    bool attack_flag;
    int attack_range;
    int max_attack_random_bonus;
    int max_defence_random_bonus;
    int attack_RPS_bonus; // сколько
    enum UnitType attack_RPS_bonus_UT; // против кого
};

#endif
