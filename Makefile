CC = gcc
CFLAGS = -Wall -Wextra -g -std=c11
TARGET = lnd

all: $(TARGET)

$(TARGET): src/main.c
	$(CC) $(CFLAGS) src/main.c -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
