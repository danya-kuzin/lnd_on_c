#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "str_read_and_parsing.h"

void str_read_and_parsing(int str_len, char str[], char param1[], 
                          char param2[], char param3[]) {

    // ввод строки
    fgets(str, str_len, stdin);

    int i = 0, j = 0;
    int num_param = 1;
    char temp_param[str_len];
    temp_param[0] = '\0';

    while (i <= str_len) {

        if (str[i] == ' ' || str[i] == '\n') {
            if (num_param == 1) {
                strcpy(param1, temp_param);
                param1[j] = '\0';  // чтобы не читалось дальше размера соответ. параметра
            }

            else if (num_param == 2) {
                strcpy(param2, temp_param); 
                param2[j] = '\0';
            }

            else {
                strcpy(param3, temp_param);
                param3[j] = '\0';
                break;
            }
            
            i++; // чтобы скипнуть пробел
            num_param++;
            j = 0;

            if (str[i] == '\n')
                break;
        }

        temp_param[j] = str[i]; 
        i++;
        j++;
    }
}