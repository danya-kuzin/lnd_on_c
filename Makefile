CC = gcc
CFLAGS = -Wall -Wextra -g -std=c11
TARGET = lnd

all: $(TARGET)

$(TARGET): src/main.c src/str_read_and_parsing.c src/print_units.c src/com_create_unit.c src/com_help.c src/com_move.c
	$(CC) $(CFLAGS) src/main.c src/str_read_and_parsing.c src/print_units.c src/com_create_unit.c src/com_help.c src/com_move.c -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
