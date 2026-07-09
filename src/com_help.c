#include <stdio.h>

#include "com_help.h"

void com_help(void){
    printf("\n");
    printf("\n");
    printf("===========================================================\n");
    printf("               COMMANDS AND WHAT THEY DO\n");
    printf("\n");
    printf("\n");
    printf("-----------------------------------------------------------\n");
    printf("         move <unit_id> <x_hex_goto> <x_hex_goto>\n");
    printf("meaning: move the unit to the hex with coordinates (x, y)\n");
    printf("example: move 1 2 3\n");
    printf("-----------------------------------------------------------\n");
    printf("           create <mech> / <luch> / <kop>\n");
    printf("meaning: allows you to create a new unit \n");
    printf("example: create mech\n");
    printf("-----------------------------------------------------------\n");
    printf("                         status\n");
    printf("meaning: provides a detailed overview of the current state \n");
    printf("of the game and what is happening on the map\n");
    printf("example: status\n");
    printf("-----------------------------------------------------------\n");
    printf("                      unit <unit_id>\n");
    printf("meaning: provides a detailed overview of the selected unit \n");
    printf("example: unit 3\n");
    printf("-----------------------------------------------------------\n");
    printf("                        end turn\n");
    printf("meaning: finish the turn \n");
    printf("example: end turn\n");
    printf("-----------------------------------------------------------\n");
    printf("                         finish\n");
    printf("meaning: exit the game \n");
    printf("example: finish\n");
    printf("-----------------------------------------------------------\n");
};