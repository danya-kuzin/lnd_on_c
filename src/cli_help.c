#include <stdio.h>

#include "cli_help.h"

void cli_help(void)
{
    printf("\n");
    printf("\n");
    printf("===========================================================\n");
    printf("               COMMANDS AND WHAT THEY DO\n");
    printf("\n");
    printf("\n");

    printf("-----------------------------------------------------------\n");
    printf("                         move\n");
    printf("format:  move <unit_id> <x_hex_goto> <y_hex_goto>\n");
    printf("meaning: move the selected unit to the hex with coordinates (x, y)\n");
    printf("example: move 1 4 3\n");

    printf("-----------------------------------------------------------\n");
    printf("                        attack\n");
    printf("format:  attack <attacker_id> <defender_id>\n");
    printf("meaning: attack the defender unit with the selected attacker unit\n");
    printf("example: attack 2 5\n");

    printf("-----------------------------------------------------------\n");
    printf("                        create\n");
    printf("format:  create <unit_type>\n");
    printf("unit types:\n");
    printf("         mech  - swordsman\n");
    printf("         kop   - spearman\n");
    printf("         arch  - archer\n");
    printf("         cav   - cavalry\n");
    printf("         scout - scout\n");
    printf("example: create arch\n");

    printf("-----------------------------------------------------------\n");
    printf("                        status\n");
    printf("format:  status\n");
    printf("meaning: show the current map, players' gold and all units\n");
    printf("example: status\n");

    printf("-----------------------------------------------------------\n");
    printf("                         help\n");
    printf("format:  help\n");
    printf("meaning: show the list of available commands\n");
    printf("example: help\n");

    printf("-----------------------------------------------------------\n");
    printf("                         end\n");
    printf("format:  end\n");
    printf("meaning: finish the current player's turn\n");
    printf("example: end\n");

    printf("-----------------------------------------------------------\n");
    printf("                        finish\n");
    printf("format:  finish\n");
    printf("meaning: exit the game\n");
    printf("example: finish\n");

    printf("-----------------------------------------------------------\n");
}