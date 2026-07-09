#include <stdio.h>
#include "unit.h"

void print_units(struct Unit all_units[], int cur_cnt_units)
{
    for (int i = 0; i < cur_cnt_units; i++) {
        printf(
            "unit %d: type=%d pos=(%d, %d) hp=%d atk=%d def=%d speed=%d cost=%d\n",
            i + 1,
            all_units[i].type,
            all_units[i].hex_x,
            all_units[i].hex_y,
            all_units[i].health,
            all_units[i].attack,
            all_units[i].defence,
            all_units[i].speed,
            all_units[i].cost,
            all_units[i].id
        );
    }
}

