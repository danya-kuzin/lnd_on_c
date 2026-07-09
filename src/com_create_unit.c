#include "unit.h"
#include <stdio.h>

#include "com_create_unit.h"

/*  при такой передаче массива он сам превращается в свой адрес
    то есть функция получает доступ к настоящему массиву, а не к его копии*/
void create_unit(struct Unit all_units[], enum UnitType unit_type,
                int * cur_cnt_units, int max_cnt_of_units) {

    // проверка на достижения предела количества юнитов
    if (*cur_cnt_units >= max_cnt_of_units) {
        printf("Cannot create unit: unit limit reached\n");
        return;
    }

    // создаем нового юнита
    struct Unit new_unit;
    
    // задаем ему характеристики
    switch (unit_type) {
        case SWORDSMAN:
            new_unit.type = SWORDSMAN;
            new_unit.hex_x = 2;
            new_unit.hex_y = 1;
            new_unit.cost = 6;
            new_unit.health = 3;
            new_unit.attack = 2;
            new_unit.defence = 1;
            new_unit.speed = 1;
            new_unit.id = *cur_cnt_units + 1;
            break;

        case SPEARMAN:
            new_unit.type = SPEARMAN;
            new_unit.hex_x = 2;
            new_unit.hex_y = 1;
            new_unit.cost = 8;
            new_unit.health = 4;
            new_unit.attack = 3;
            new_unit.defence = 2;
            new_unit.speed = 1;
            new_unit.id = *cur_cnt_units + 1;
            break;
    }

    // добавляем его в массив юнитов
    all_units[*cur_cnt_units] = new_unit;
    (*cur_cnt_units)++;
}