NAME = parser
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INC = -Iinclude
SRC = src/minishell_parser.c
OBJ = $(SRC:.c=.o)
LIBS = -lreadline

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(INC) $(SRC) -o $(NAME) $(LIBS)

clean:
	rm -f $(NAME)

re: clean all

.PHONY: all clean re

