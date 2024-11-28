NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = $(wildcard $/*.c)

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@echo "$(GREEN)Compilation of libft successful!   😊$(RESET)"
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus