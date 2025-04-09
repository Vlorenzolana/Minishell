NAME = parser
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3
INC = -Iinclude
SRC = src/parser.c src/main.c
OBJ = $(SRC:.c=.o)
LIBS = -lreadline

TEST_SRC = tests/test_parser.c
TEST = test_parser

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(INC) $(SRC) -o $(NAME) $(LIBS)

valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)


test: $(TEST_SRC) $(SRC)
	$(CC) $(CFLAGS) $(INC) $(SRC) $(TEST_SRC) -o $(TEST) $(LIBS)

clean:
	rm -f $(NAME) $(TEST)

re: clean all

.PHONY: all clean re