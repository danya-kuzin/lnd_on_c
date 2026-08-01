#ifndef HEX_H
#define HEX_H

#include <stdbool.h>

enum TerrainType {
    NOT_EXISTS,
    TERRAIN_PLAIN,
    TERRAIN_FOREST,
    TERRAIN_HILL,
    TERRAIN_MOUNTAIN,
    TERRAIN_VILLAGE_1,
    TERRAIN_VILLAGE_2,
    TERRAIN_VILLAGE_3
};

struct Hex {
    int x;
    int y;
    enum TerrainType terrain;
    bool is_discovered;
    int owner_player_id;
};

#endif