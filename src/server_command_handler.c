#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "game.h"
#include "net_common.h"
#include "server_help.h"
#include "server_create_unit.h"
#include "server_move.h"
#include "server_attack.h"
#include "server_end_turn.h"
#include "server_command_handler.h"

#define BUFFER_SIZE 256


// проверка на то, что эта команда выполняется в свой ход
static bool is_sender_current_player(struct GameState *game,
                                     struct Client clients[],
                                     int sender_i)
{
    if (clients[sender_i].client_id != game->cur_player_id_turn) {
        send_all(clients[sender_i].client_fd,
                 "Error: it is not your turn\n",
                 strlen("Error: it is not your turn\n"));
        return false;
    }
    return true;
}

void server_handle_command(struct GameState *game, struct Client clients[], int client_count,
                            int sender_i, char line[]) {
    // парсим строку (line)
    char param1[32] = "";
    char param2[32] = "";
    char param3[32] = "";
    char param4[32] = "";
    char extra[32] = "";
    
    int count = sscanf(line, "%31s %31s %31s %31s %31s",
                        param1, param2, param3, param4, extra);

    // проверка на пустую строку
    if (count <= 0) {
        send_all(clients[sender_i].client_fd,
                "Error: empty command\n",
                strlen("Error: empty command\n"));
        return;
    }

    // проверка на слишком большое кол-во аргументов
    if (count == 5) {
        send_all(clients[sender_i].client_fd,
                "Error: too many parameters\n",
                strlen("Error: too many parameters\n"));
        return;
    }

    if (strcmp(param1, "help") == 0) {
        server_help(clients[sender_i].client_fd);
    }

    else if (strcmp(param1, "create") == 0) {
        // проверяем, на совпадение текущего игрока и отправителя команды
        if (is_sender_current_player(game, clients, sender_i) == false) {
            return;
        }
        server_create_unit(game, param2, clients[sender_i].client_fd);
    }

    else if (strcmp(param1, "move") == 0) {
        // проверяем, на совпадение текущего игрока и отправителя команды
        if (is_sender_current_player(game, clients, sender_i) == false) {
            return;
        }
        server_move(param2, param3, param4, clients[sender_i].client_fd, game);
    }

    else if (strcmp(param1, "attack") == 0) {
        // проверяем, на совпадение текущего игрока и отправителя команды
        if (is_sender_current_player(game, clients, sender_i) == false) {
            return;
        }
        server_attack(param2, param3, game, clients[sender_i].client_fd);
    }

    else if (strcmp(param1, "end") == 0) {
        // проверяем, на совпадение текущего игрока и отправителя команды
        if (is_sender_current_player(game, clients, sender_i) == false) {
            return;
        }
        server_end_turn(game, clients[sender_i].client_fd);
    }

    else {
        char error[BUFFER_SIZE + 64];
        snprintf(error, sizeof(error), "Error: command is not correct. Try again\n");
        send_all(clients[sender_i].client_fd, error, strlen(error));
    }
    
}