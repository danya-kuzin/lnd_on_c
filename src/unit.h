#ifndef UNIT_H
#define UNIT_H

enum UnitType {
    SWORDSMAN,
    SPEARMAN,
    ARCHER
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
};

#endif
