#ifndef SERVER_COMMAND_HANDLER_H
#define SERVER_COMMAND_HANDLER_H

#include "game.h"

struct Client {
    int client_fd;
    int client_id;
};

void server_handle_command(
    struct GameState *game,
    struct Client clients[],
    int client_count,
    int sender_i,
    char line[]
);

#endif