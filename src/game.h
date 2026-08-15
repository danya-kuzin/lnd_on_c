#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include "unit.h"
#include "hex.h"

#define MAX_CNT_OF_UNITS 64
#define MAP_WIDTH 16
#define MAP_HEIGHT 8
#define MAX_CNT_OF_PLAYERS 4

// для вывода и хранения результатов атаки
struct AttackResult {
    int attacker_id;
    int defender_id;
    int damage_to_defender;
    int damage_to_attacker;

    int defender_based_defence;
    int defender_hp_before;
    int defender_hp_after;
    int defender_based_attack;
    int defender_attack_random_bonus;
    int defender_defence_random_bonus;
    int defender_bonus_RPS;
    bool defender_dead;

    int attacker_based_defence;
    int attacker_hp_before;
    int attacker_hp_after;
    int attacker_based_attack;
    int attacker_attack_random_bonus;
    int attacker_defence_random_bonus;
    int attacker_bonus_RPS;
    bool attacker_dead;

    int all_attacker_attack;
    int all_attacker_defence;
    int all_defender_attack;
    int all_defender_defence;
};

// перечислимый тип для хода игрока
enum PlayerTurn {
    NOT_TURN_YET,
    TURN_NOW,
    ALREADY_TURN
};

// структура для хранения состояния игры (завершена/продолжается)
enum ServerResult {
    SERVER_CONTINUE,
    SERVER_FINISH
};

// структура игрока
struct Player {
    int gold;
    int id;
    enum PlayerTurn turn;

    int castle_x;
    int castle_y;
};

// структура для хранения войска игроков
struct GameState {
    struct Unit all_units[MAX_CNT_OF_UNITS];
    int cur_cnt_units;

    struct Player players[MAX_CNT_OF_PLAYERS];
    int cur_round;
    int num_of_players;
    int cur_player_id_turn;
    bool all_players_end_turns;
    int next_unit_id;

    struct Hex map[MAP_HEIGHT][MAP_WIDTH];
};

enum GameError {
    GAME_OK,
    GAME_ERROR_UNIT_LIMIT,
    GAME_ERROR_GOING_BEYOND_BOUNDARIES_MAP,
    GAME_ERROR_NO_SUCH_COORDINATES,
    GAME_ERROR_NO_SUCH_UNIT_ID,
    GAME_ERROR_NOT_ENOUGH_SPEED,
    GAME_ERROR_ALREADY_UNIT_ON_HEX,
    GAME_ERROR_UNKNOWN_UNIT_TYPE,
    GAME_ERROR_NOT_ENOUGH_GOLD,
    GAME_ERROR_NOT_YOUR_UNIT,
    GAME_ERROR_SPAWN_HEX_OCCUPIED,
    GAME_ERROR_ATTACKER_NOT_BELONG_PLAYER,
    GAME_ERROR_ATTACKER_NOT_NEAR,
    GAME_ERROR_UNIT_ALREADY_ATTACKED
    //GAME_ERROR_EMPTY_PARAMETER,
    //GAME_ERROR_PARAMETER_IS_NOT_NUMBER,
    //GAME_ERROR_TOO_MANY_PARAMETERS
};

void game_init(struct GameState *game, int num_of_players);

enum GameError game_create_unit(struct GameState *game, enum UnitType unit_type);

enum GameError game_move(struct GameState *game, int unit_id, int target_x, int target_y);

enum GameError game_end_turn(struct GameState *game);

enum GameError game_attack(struct GameState *game, int attacker_id, int defender_id, struct AttackResult *result);

#endif