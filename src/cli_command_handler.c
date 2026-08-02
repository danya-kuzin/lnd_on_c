#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "cli_print_units.h"
#include "cli_create_unit.h"
#include "cli_help.h"
#include "cli_move.h"
#include "cli_status.h"
#include "cli_end_turn.h"
#include "cli_attack.h"
#include "cli_command_handler.h"

// распределение текстовых команд по их обработчикам
enum CliResult cli_handle_command(struct GameState *game, char param1[],
                                char param2[], char param3[], char param4[]) {
    if (strcmp(param1, "create") == 0) {
        cli_create_unit(game, param2);
        cli_status(game);
        return CLI_CONTINUE;
    }

    else if (strcmp(param1, "help") == 0) {
        cli_help();
        return CLI_CONTINUE;
    }

    else if (strcmp(param1, "move") == 0) {
        cli_move(param2, param3, param4, game);
        cli_status(game);
        return CLI_CONTINUE;
    }

    else if (strcmp(param1, "status") == 0) {
        cli_status(game);
        return CLI_CONTINUE;
    }

    else if (strcmp(param1, "finish") == 0) {
        printf("Congratulations on the end of the LnD game\n");
        return CLI_FINISH;
    }

    else if (strcmp(param1, "end") == 0) {
        cli_end_turn(game);
        return CLI_CONTINUE;
    }

    else if (strcmp(param1, "attack") == 0) {
        cli_attack(param2, param3, game);
        cli_status(game);
        return CLI_CONTINUE;
    }

    else {
        printf("Command is not correct. Try again\n");
        return CLI_CONTINUE;
    }
}