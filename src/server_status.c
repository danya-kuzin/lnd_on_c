#include <stdio.h>
#include <string.h>
#include "game.h"
#include "net_common.h"
#include "server_status.h"

static char unit_type_letter(enum UnitType type)
{
    switch (type) {
        case SWORDSMAN:
            return 'm';
        case SPEARMAN:
            return 'k';
        case ARCHER:
            return 'a';
        case CAVALRY:
            return 'c';
        case SCOUT:
            return 's';
        default:
            return '#';
    }
}

static const char *terrain_name(enum TerrainType terrain)
{
    switch (terrain) {
        case TERRAIN_PLAIN:
            return "plain";
        case TERRAIN_FOREST:
            return "forest";
        case TERRAIN_HILL:
            return "hill";
        case TERRAIN_MOUNTAIN:
            return "mountain";
        case TERRAIN_VILLAGE_1:
            return "village_1";
        case TERRAIN_VILLAGE_2:
            return "village_2";
        case TERRAIN_VILLAGE_3:
            return "village_3";
        case NOT_EXISTS:
        default:
            return "not_exists";
    }
}

void server_status(struct GameState *game, int client_fd)
{
    char buffer[512];

    snprintf(buffer, sizeof(buffer),
             "Status: round=%d current_player=%d units=%d\n",
             game->cur_round, game->cur_player_id_turn, game->cur_cnt_units);
    send_all(client_fd, buffer, strlen(buffer));

    for (int i = 0; i < game->num_of_players; i++) {
        snprintf(buffer, sizeof(buffer),
                 "Player %d: gold=%d castle=(%d,%d)\n",
                 game->players[i].id,
                 game->players[i].gold,
                 game->players[i].castle_x,
                 game->players[i].castle_y);
        send_all(client_fd, buffer, strlen(buffer));
    }

    for (int i = 0; i < game->cur_cnt_units; i++) {
        struct Unit unit = game->all_units[i];
        int map_i = MAP_HEIGHT - unit.hex_y;
        int map_j = unit.hex_x - 1;

        snprintf(buffer, sizeof(buffer),
                 "Unit %c%d: player=%d pos=(%d,%d) hp=%d move=%d/%d atk=%d def=%d range=%d terrain=%s\n",
                 unit_type_letter(unit.type),
                 unit.id,
                 unit.player_id,
                 unit.hex_x,
                 unit.hex_y,
                 unit.health,
                 unit.movement_left,
                 unit.speed,
                 unit.attack,
                 unit.defence,
                 unit.attack_range,
                 terrain_name(game->map[map_i][map_j].terrain));
        send_all(client_fd, buffer, strlen(buffer));
    }
}
