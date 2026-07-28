CC = gcc
CFLAGS = -Wall -Wextra -g -std=c11
TARGET = lnd

all: $(TARGET)

$(TARGET): src/main_cli.c src/cli_parsing.c src/cli_print_units.c src/cli_create_unit.c src/cli_help.c src/cli_move.c src/game.c src/game_create_unit.c src/game_move.c src/cli_status.c src/cli_command_handler.c src/cli_end_turn.c src/game_end_turn.c
	$(CC) $(CFLAGS) src/main_cli.c src/cli_parsing.c src/cli_print_units.c src/cli_create_unit.c src/cli_help.c src/cli_move.c src/game.c src/game_create_unit.c src/game_move.c src/cli_status.c src/cli_command_handler.c src/cli_end_turn.c src/game_end_turn.c -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
