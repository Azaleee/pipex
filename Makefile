NAME = pipex

CC = /bin/cc
CFLAGS = -Wall -Wextra -Werror -g

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
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	/bin/mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDES) -I $(LIBFT_DIR) -o $@ -c $<

clean:
	/bin/rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	/bin/rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all