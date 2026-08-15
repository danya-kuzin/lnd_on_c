#include <string.h>
#include "net_common.h"
#include "server_help.h"

void server_help(int client_fd)
{
    const char *message =
        ""
        "COMMANDS:"
        "  help"
        "  status"
        "  create <mech|kop|arch|cav|scout>"
        "  move <unit_id> <x> <y>"
        "  attack <attacker_id> <defender_id>"
        "  end"
        "  finish\n";

    send_all(client_fd, message, strlen(message));
}