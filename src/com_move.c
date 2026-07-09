#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unit.h"

#include "com_move.h"

void com_move(char param2[], char param3[], 
              char param4[], struct Unit all_units[],
              int cur_cnt_units, int map_width, int map_height) {

    // проверка на непустые параметры
    if (param2[0] == '\0' || param3[0] == '\0' || param4[0] == '\0') {
        printf("Incorrect command: one of the parameters is empty \n");
        return;
        };
    
    // проверка на то, что параметры - числа
    char *end2, *end3, *end4;
    strtol(param2, &end2, 10);
    strtol(param3, &end3, 10);
    strtol(param4, &end4, 10);
    if (*end2 != '\0' || *end3 != '\0' || *end4 != '\0') {
        printf("Incorrect command: one of the parameters is not a number \n");
        return;
        };

    // проверка на выход за границы карты
    if (atoi(param3) >  map_width || atoi(param4) >  map_height) {
        printf("Incorrect command: going beyond the boundaries of the map \n");
        return;
    }

    // проверка на несуществующие коордиинаты
    if ( atoi(param3) < 1 || atoi(param4) < 1 || 
        (abs(atoi(param3) - atoi(param4)) % 2 == 0) ) {
        printf("Incorrect command: there are no such coordinates \n");
        return;
        }


    // находим нашего юнита
    struct Unit cur_unit;
    int flag_id = 0;
    for (int i = 0; i <= cur_cnt_units; i++) {
        if (all_units[i].id == atoi(param2)) {
            cur_unit = all_units[i];
            flag_id = 1;
        }
    }

    // проверка на несуществующий id
    if (flag_id == 0) {
        printf("Incorrect command: there is no such unit_id \n");
        return;
    }

    // проверка на возможности по скорости
    int delta_x = abs(cur_unit.hex_x - atoi(param3));
    int delta_y = abs(cur_unit.hex_y - atoi(param4));
    if (delta_x + delta_y > cur_unit.speed * 2){
        printf("Incorrect command: not enough speed for this type of unit \n");
        return;
    }
    
    // проверка на попытку поставить отряд на занятый гекс
    for (int i = 0; i <= cur_cnt_units; i++) {
        if (atoi(param3) == all_units[i].hex_x && 
            atoi(param4) == all_units[i].hex_y) {
            printf("Incorrect command: there is already a unit on this hex \n");
            return;
        }
    }

    // сама команда move
    for (int i = 0; i <= cur_cnt_units; i++) {
        if (all_units[i].id == atoi(param2)) {
            all_units[i].hex_x = atoi(param3);
            all_units[i].hex_y = atoi(param4);
            break;
        }
    }
}