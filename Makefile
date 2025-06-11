NAME = MyAES.a

FLAGS = -Wall -Werror -Wextra

CC = cc

SRC_DIR = .
OBJ_DIR = objs

C_SOURCE = cypher_utils.c main.c block_converter.c permutation_substitution.c
H_FILES = MyAES.h

OBJ_SOURCE = $(C_SOURCE:%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: %.c $(H_FILES)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ_SOURCE)
	ar -rcs $(NAME) $(OBJ_SOURCE)
	$(CC) $(FLAGS) main.c $(NAME) -o MyAES

re: fclean all

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f MyAES

.PHONY: all clean fclean re
