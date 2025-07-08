NAME        = minishell
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
LIBS        = -lreadline
INCLUDES    = -Iinclude

SRC_DIR     = src
OBJ_DIR     = obj

SRCS        = $(shell find $(SRC_DIR) -name '*.c')
OBJS        = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

bonus:
	$(MAKE) BONUS=1 all

.PHONY: all clean fclean re bonus

