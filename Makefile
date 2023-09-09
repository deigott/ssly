# Color codes for better output
COLOR_RESET=\033[0m
COLOR_RED=\033[31m
COLOR_GREEN=\033[32m
COLOR_YELLOW=\033[33m
COLOR_BLUE=\033[34m

# Compilation flags and variables
FLAGS=-Wall -Werror -Wextra
CC=gcc
EXEC_NAME=ft_ssl
SRCS=srcs/main.c srcs/libft/get_next_line.c srcs/algorithms/whirlpool/byte_order.c srcs/algorithms/whirlpool/whirlpool.c srcs/algorithms/whirlpool/whirlpool_sbox.c srcs/algorithms/whirlpool/whirlpool_utils.c srcs/libft/ft_memset.c srcs/algorithms/sha256/sha256.c srcs/algorithms/sha256/sha256_utils.c srcs/libft/ft_strjoin.c srcs/algorithms/md5/md5_utils.c srcs/algorithms/md5/md5.c  srcs/ssly.c srcs/libft/ft_strdup.c  srcs/libft/ft_putstr.c  srcs/libft/ft_strncmp.c srcs/libft/ft_bzero.c srcs/libft/ft_memcpy.c srcs/libft/ft_strlen.c srcs/libft/ft_strstr.c srcs/utils/collect_memory.c srcs/utils/concatenate_strings.c srcs/utils/show_help.c srcs/utils/show_errors.c srcs/parsing/parse_clo.c
INCLUDES=includes/

all: $(EXEC_NAME)

$(EXEC_NAME): $(SRCS)
	@$(CC) $(FLAGS) $(SRCS) -I $(INCLUDES) -o $(EXEC_NAME)
	@echo "$(COLOR_BLUE)$(EXEC_NAME) executable created$(COLOR_RESET)"

clean:
	@rm -rf $(EXEC_NAME)
	@echo "$(COLOR_YELLOW)Cleaned up the generated files$(COLOR_RESET)"

fclean: clean

re: fclean all

.PHONY: all clean fclean re
