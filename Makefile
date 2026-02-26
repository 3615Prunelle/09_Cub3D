# IP - DO TO
# Add rule to dl & build libft

NAME = cub3d

CC = cc

# Add -Wall -Wextra -Werror when we have something functional
CFLAGS = -g -I ./get_next_line -I ./ft_printf -I ./MLX42/include/MLX42 -I ./libft

# Linking flags
LFLAGS = -L ./get_next_line -L ./ft_printf -L ./MLX42/build -L ./libft -lmlx42 -lgetnextline -lftprintf -lglfw -lft #-lglfw goes with mlx42

SRCS =	main.c

# Libs to be used
MLX42_LIB = ./MLX42/build/libmlx42.a
LIBFT_LIB = ./libft/libft.a
PRINTF_LIB = ./ft_printf/libftprintf.a
GNL_LIB = ./get_next_line/libgetnextline.a

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
