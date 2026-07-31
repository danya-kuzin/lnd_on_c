#ifndef UNIT_H
#define UNIT_H

#include <stdbool.h>

enum UnitType {
    SWORDSMAN,
    SPEARMAN,
    ARCHER,
    CAVALRY,
    SCOUT
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
};

#endif
