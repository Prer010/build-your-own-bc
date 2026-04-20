NAME := my_bc
CC := gcc 
CFLAGS := -Wall -Wextra -Werror -Iinclude

SRC := src/main.c src/error.c src/dynarray.c src/lexer.c src/shunting.c src/evaluate.c
OBJ := $(SRC:.c=.o) 

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) 

clean:
	rm -f $(OBJ)

fclean: clean 
	rm -f $(NAME)

re: fclean all

# address sanitizer
asan: CFALGS += -g3 -fsanitize=address
asan: re 

.PHONY: all clean fclean re asan