NAME = cub3d

CC = cc

# Add -Wall -Wextra -Werror when we have something functional
CFLAGS = -g -I ./includes -I ./MLX42/include/MLX42 -I ./libft

# Linking flags
LFLAGS = -L ./get_next_line -L ./MLX42/build -L ./libft -lmlx42 -lglfw -lm -lft #-lglfw goes with mlx42 and -lm is needed for math

SRCS =	./sources/main.c \
		./sources/parsing/input_parsing.c \
		./sources/parsing/fetch_elements.c \
		./sources/parsing/free_functions.c \
		./sources/parsing/map_parsing.c \
		./sources/visuals/minimap/minimapper.c \
		./sources/visuals/image_handler.c \
		./sources/visuals/visualizer.c \
		./sources/visuals/ray_casting.c \
		./sources/visuals/ft_math.c \
		./sources/controls/movements.c \
		./sources/controls/controler.c

# Libs to be used
LIBFT_LIB = ./libft/libft.a
MLX42_LIB = ./MLX42/build/libmlx42.a

OBJS = $(SRCS:.c=.o)

all: $(NAME)

# libft fetch/build
$(LIBFT_LIB):
	@echo "Cloning Libft ..."
	git clone https://github.com/3615Prunelle/01_Libft.git libft
	@echo "Building Libft ..."
	@cd ./libft && make

# MLX42 fetch/build
# Dependency of MLX42 to create the .o, otherwise MLX header is not found during compilation
# CMakeLists.txt avoids timestamp / relinks issues
%.o: %.c ./MLX42/CMakeLists.txt
	$(CC) $(CFLAGS) -c $< -o $@

$(MLX42_LIB): ./MLX42
	@echo "Building MLX42 ..."
	@cd ./MLX42 && cmake -B build && cmake --build build -j4

./MLX42:
	@echo "Cloning MLX42 ..."
	@git clone https://github.com/codam-coding-college/MLX42.git

# CMakeLists.txt gets automatically created when MLX42 is cloned
./MLX42/CMakeLists.txt: ./MLX42

$(NAME): $(MLX42_LIB) $(LIBFT_LIB) $(GNL_LIB) $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) -o $(NAME)

clean:
	rm -f $(OBJS)

medclean : clean
	rm -f $(NAME)

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C ./libft fclean
	rm -rf ./MLX42
	rm -rf ./libft

# Medclean to avoid erasing/building libft & gnl every time we do 'make re' (as they're not supposed to change)
re: medclean all

.PHONY: all clean fclean re
