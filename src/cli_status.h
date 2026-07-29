#include "game.h"

#ifndef CLI_STATUS_H
#define CLI_STATUS_H
#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_RESET "\x1b[0m"

void cli_status(struct GameState *game);

#endif