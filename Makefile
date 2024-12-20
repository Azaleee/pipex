NAME = pipex
NAME_BONUS = pipex_bonus

CC = /bin/cc
CFLAGS = -Wall -Wextra -Werror -g

INCLUDES = includes/
LIBFT_DIR = libft
SRC_DIR = src/
BONUS_DIR = src/bonus/
OBJ_DIR = obj/
OBJ_BONUS_DIR = obj_bonus/

SRC_FILES = pipex.c pipex_utils.c free_func.c error_check.c
SRC_BONUS_FILES = pipex_bonus.c pipex_utils_bonus.c free_func_bonus.c error_check_bonus.c parsing_bonus.c
OBJ_FILES = $(SRC_FILES:.c=.o)
OBJ_BONUS_FILES = $(SRC_BONUS_FILES:.c=.o)

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

SRC_BONUS = $(addprefix $(BONUS_DIR), $(SRC_BONUS_FILES))
OBJ_BONUS = $(addprefix $(OBJ_BONUS_DIR), $(OBJ_BONUS_FILES))

LIBFT = $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

bonus: $(LIBFT) $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_BONUS)
	$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBFT) -o $(NAME_BONUS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	/bin/mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDES) -I $(LIBFT_DIR) -o $@ -c $<

$(OBJ_BONUS_DIR)%.o: $(BONUS_DIR)%.c
	/bin/mkdir -p $(OBJ_BONUS_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDES) -I $(LIBFT_DIR) -o $@ -c $<

clean:
	/bin/rm -rf $(OBJ_DIR) $(OBJ_BONUS_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	/bin/rm -f $(NAME) $(NAME_BONUS)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
