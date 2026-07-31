#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "cli_parsing.h"

void cli_parsing(int str_len, char str[], char param1[], 
                          char param2[], char param3[], char param4[]) {

    // ввод строки
    fgets(str, str_len, stdin);

    int i = 0, j = 0;
    int num_param = 1;
    char temp_param[str_len];
    temp_param[0] = '\0';

    while (i < str_len) {

        if (str[i] == ' ' || str[i] == '\n') {
            if (num_param == 1) {
                temp_param[j] = '\0'; // чтобы не читалось дальше размера соответ. параметра
                strcpy(param1, temp_param);
            }

            else if (num_param == 2) {
                temp_param[j] = '\0';
                strcpy(param2, temp_param); 
            }

            else if (num_param == 3) {
                temp_param[j] = '\0';
                strcpy(param3, temp_param);
            }

            else if (num_param == 4) {
                temp_param[j] = '\0';
                strcpy(param4, temp_param);
            }
            
            else if (num_param == 5) {
                printf("Incorrect command: too many parametrs");
                break;
            }

            if (str[i] == '\n') {
                break;
            }
            
            i++; // чтобы скипнуть пробел
            num_param++;
            j = 0;

        }

        temp_param[j] = str[i]; 
        i++;
        j++;
    }
}