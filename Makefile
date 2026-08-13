CC = gcc
CFLAGS = -Wall -Wextra -g -std=c11

BUILD_DIR = build

CLI = $(BUILD_DIR)/lnd_cli
SERVER = $(BUILD_DIR)/lnd_server
CLIENT = $(BUILD_DIR)/lnd_client

GAME_SRC = \
	src/game.c \
	src/game_create_unit.c \
	src/game_move.c \
	src/game_end_turn.c \
	src/game_attack.c

CLI_SRC = \
	src/main_cli.c \
	src/cli_parsing.c \
	src/cli_print_units.c \
	src/cli_create_unit.c \
	src/cli_help.c \
	src/cli_move.c \
	src/cli_status.c \
	src/cli_command_handler.c \
	src/cli_end_turn.c \
	src/cli_attack.c

NET_SRC = \
	src/net_common.c

SERVER_SRC = \
	src/lnd_server.c

CLIENT_SRC = \
	src/lnd_client.c

HEADERS = \
	src/game.h \
	src/unit.h \
	src/hex.h \
	src/cli_parsing.h \
	src/cli_print_units.h \
	src/cli_create_unit.h \
	src/cli_help.h \
	src/cli_move.h \
	src/cli_status.h \
	src/cli_command_handler.h \
	src/cli_end_turn.h \
	src/cli_attack.h \
	src/net_common.h

.PHONY: all clean run run-cli run-server run-client

all: $(CLI) $(SERVER) $(CLIENT)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(CLI): $(CLI_SRC) $(GAME_SRC) $(HEADERS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CLI_SRC) $(GAME_SRC) -o $(CLI)

$(SERVER): $(SERVER_SRC) $(GAME_SRC) $(NET_SRC) $(HEADERS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SERVER_SRC) $(GAME_SRC) $(NET_SRC) -o $(SERVER)

$(CLIENT): $(CLIENT_SRC) $(NET_SRC) $(HEADERS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CLIENT_SRC) $(NET_SRC) -o $(CLIENT)

run: run-cli

run-cli: $(CLI)
	./$(CLI)

run-server: $(SERVER)
	./$(SERVER)

run-client: $(CLIENT)
	./$(CLIENT) 127.0.0.1

clean:
	rm -rf $(BUILD_DIR)