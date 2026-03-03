#Tests parsing ohne MLX42
NAME = ./../cub3d

CC = cc

# Add -Wall -Wextra -Werror when we have something functional
CFLAGS = -g -I ../../../98_include -I ../../includes

# Linking flags
LFLAGS = -L ../../../99_lib -lgetnextline -lft

SRCS =	../main.c \
		./check_and_read.c \
		./fetch_elements.c \
		./free_functions.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) -o .$(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
