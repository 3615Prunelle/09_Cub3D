# IP - DO TO
# Add rule to dl & build libft

NAME = cub3d

CC = cc

# Add -Wall -Wextra -Werror when we have something functional
CFLAGS = -

# Linking flags
LFLAGS =

SRCS =	main.c

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
