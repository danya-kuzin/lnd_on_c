#ifndef CLI_COMMAND_HANDLER_H
#define CLI_COMMAND_HANDLER_H

#include "game.h"

enum CliResult {
    CLI_CONTINUE,
    CLI_FINISH
};

enum CliResult cli_handle_command(struct GameState *game, char param1[],
                                char param2[], char param3[], char param4[]);

#endif