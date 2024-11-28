NAME = pipex
OS = $(shell uname)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

LIBS_DIR = ./libs
OBJ_DIR = ./obj
SRC_DIR = ./src
LIBFT_DIR = $(LIBS_DIR)/libft

LIBFT = $(LIBFT_DIR)/libft.a

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

GREEN = \033[1;32m
RED = \033[0m
BLUE = \033[1;34m
YELLOW = \033[1;33m
BLACK = \033[0;30m
WHITE = \033[1;37m
ORANGE = \033[0;33m
VIOLET = \033[0;35m
CYAN = \033[0;36m

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ_FILES)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES) $(LIBFT)
	@echo "$(GREEN)Compilation of pipex successful!   😊$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)
	
clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "$(GREEN)Clean done 🧹$(RESET)"

re: fclean all

.PHONY: all clean fclean re
