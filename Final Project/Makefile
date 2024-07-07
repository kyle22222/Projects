CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = main.c defs.h ghost.c house.c hunter.c logger.c room.c utils.c
OBJ = $(SRC:.c=.o)
EXEC = main

all:
	$(CC) $(CFLAGS) $(SRC) -o $(EXEC)

clean:
	rm -f $(OBJ) $(EXEC)
