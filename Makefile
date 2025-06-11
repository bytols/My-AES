NAME =  MyAES.a 

FLAGS = -Wall -Werror -Wextra

CC= cc

C_SOURCE= cypher_utils.c main.c

H_FILES = MyAES.h 

OBJ_SOURCE= $(C_SOURCE:.c=.o)

.c.o:
	$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME): $(OBJ_SOURCE)
	ar -src $(NAME) $(OBJ_SOURCE)
	$(CC) $(FLAGS) main.c MyAES.a -o MyAES 

$(OBJ_SOURCE): $(C_SOURCE)
	$(CC) $(FLAGS) -c $(C_SOURCE)
 
re: $(NAME) $(OBJ_SOURCE)
	make fclean
	make all

clean:
	rm -rf $(OBJ_SOURCE)

fclean:
	rm -rf $(NAME)
	rm -rf $(OBJ_SOURCE)
	rm philosophers

.PHONY: all clean fclean re