NAME = pipex
NAME_BONUS = pipex_bonus

CC = /bin/cc
CFLAGS = -Wall -Wextra -Werror

GREEN = \\033[0;32m
YELLOW = \\033[0;33m
RED = \\033[0;31m
BLUE = \\033[0;34m
RESET = \\033[0m

INCLUDES = includes/
LIBFT_DIR = libft
SRC_DIR = src/
OBJ_DIR = obj/

SRC_FILES = pipex.c pipex_utils.c free_func.c error_check.c
OBJ_FILES = $(SRC_FILES:.c=.o)

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

LIBFT = $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "========================================"
	@echo "$(GREEN)$(NAME) program created.$(RESET)"
	@echo "========================================"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@/bin/mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I$(INCLUDES) -I $(LIBFT_DIR) -o $@ -c $<
	@echo "$(YELLOW)-> Compilation of \"$<\"$(RESET)"

clean:
	@/bin/rm -rf $(OBJ_DIR)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
	@echo "$(RED)Deleted object files for $(NAME).$(RESET)"

fclean: clean
	@/bin/rm -f $(NAME)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean

re: fclean all
