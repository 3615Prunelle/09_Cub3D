NAME = cub3d

CC = cc

# Add -Wall -Wextra -Werror when we have something functional
CFLAGS = -g -I ./includes -I ./get_next_line -I ./MLX42/include/MLX42 -I ./libft

# Linking flags
LFLAGS = -L ./get_next_line -L ./MLX42/build -L ./libft -lmlx42 -lgetnextline -lglfw -lft #-lglfw goes with mlx42

SRCS =	main.c \
		parsing.c

# Libs to be used
LIBFT_LIB = ./libft/libft.a
GNL_LIB = ./get_next_line/libgetnextline.a
MLX42_LIB = ./MLX42/build/libmlx42.a

OBJS = $(SRCS:.c=.o)

all: $(NAME)

# libft fetch/build
$(LIBFT_LIB):
	@echo "Cloning Libft ..."
	git clone https://github.com/3615Prunelle/01_Libft.git libft
	@echo "Building Libft ..."
	@cd ./libft && make

# GNL fetch/build
$(GNL_LIB):
	@echo "Cloning Get_Next_Line ..."
	git clone https://github.com/3615Prunelle/03_Get_Next_Line.git get_next_line
	@echo "Building Get_Next_Line ..."
	@cd ./get_next_line && make

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

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C ./libft fclean
	$(MAKE) -C ./get_next_line fclean
	rm -rf ./MLX42
	rm -rf ./libft
	rm -rf ./get_next_line

re: fclean all

.PHONY: all clean fclean re
