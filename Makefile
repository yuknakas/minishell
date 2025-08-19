# ------------------------- Project Vars -------------------------
#
# This Makefile supports both Linux (default) and MacOS builds.
# For MacOS, use: make mac
#
# The 'mac' target adds AddressSanitizer, debug info, and corrects readline paths for Homebrew.
# ---------------------------------------------------------------
NAME        = minishell
CC          = cc
CFLAGS      = -Wall -Wextra -Werror

SRC_DIR     = src
OBJ_DIR     = obj
INCLUDE_DIR = include

SRCS        = $(shell find $(SRC_DIR) -name '*.c')
OBJS        = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a

# -------------------- Linux by default --------------------------
INCLUDES    = -I$(INCLUDE_DIR)
LIBS        = -lreadline

# ------------- MacOS block (call "make mac") -------------------
MAC_INCLUDES = -I$(INCLUDE_DIR) -I/opt/homebrew/opt/readline/include
MAC_LIBS     = -L/opt/homebrew/opt/readline/lib -lreadline

# --------------------- Build Targets ----------------------------
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)
	@echo "> make all compiled"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# -------------------- MacOS Target ------------------------------
# Usage: make mac
# Builds with AddressSanitizer, debug info, and Homebrew readline paths
mac: CFLAGS   := -g -fsanitize=address -Wall -Wextra -Werror
mac: INCLUDES := $(MAC_INCLUDES)
mac: LIBS     := $(MAC_LIBS)
mac: fclean
	$(MAKE) CFLAGS="-g -fsanitize=address -Wall -Wextra -Werror" INCLUDES="$(MAC_INCLUDES)" LIBS="$(MAC_LIBS)" all

# ------------------------ Cleaners ------------------------------
clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

bonus:
	$(MAKE) BONUS=1 all

.PHONY: all clean fclean re bonus mac

