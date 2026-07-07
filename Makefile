CC = gcc
CFLAGS = -Wall -Wextra -g -std=c11
TARGET = lnd

all: $(TARGET)

$(TARGET): src/main.c src/str_read_and_parsing.c
	$(CC) $(CFLAGS) src/main.c src/str_read_and_parsing.c -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
