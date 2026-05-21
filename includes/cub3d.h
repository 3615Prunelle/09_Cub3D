/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 20:17:58 by schappuy          #+#    #+#             */
/*   Updated: 2026/05/21 13:53:08 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <libft.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include <MLX42.h>

# define FAIL 0
# define SUCCESS 1
# define MAP_BEGINS 2
# define STEP_LENGTH 1

# define VIEW_WIDTH 700
# define VIEW_HEIGHT 700
# define MINI_WIDTH 350
# define MINI_HEIGHT 350
# define MAP_SCALE 32
# define FOV 150.0
# define VIEW_DISTANCE 4
# define DEG_TO_RAD 0.017453293

# define ERR_MSG_1 "Invalid amount of args\
	- Just provide a map in .cub format\n"
# define ERR_MSG_2 "No jeans, no sneakers, only .cub - Can't get in, sorry.\n"
# define ERR_MSG_3 "Empty .cub file\n"
# define ERR_MSG_4 "Can be either : \n\
		 -------------------- -----------------------\n\
		|  Invalid png file  |     Invalid line      |\n\
		 -------------------- -----------------------\n\
		| Missing element(s) | Duplicated element(s) |\n\
		 -------------------- -----------------------\n\
		==> RTFM (Aka. README.md) to find out\n\n"
# define ERR_MSG_5 "Something wrong with the player\n"
# define ERR_MSG_6 "Invalid map\n"
# define MSG_1 "Thanks for shopping at Cub, tschüssi !\n"

// Structs
typedef enum e_directions
{
	RIGHT,
	BACK,
	LEFT,
}					t_directions;

// int_cords[2]			[0] = X	[1] = Y
// position[2]			Gets updated as soon as player starts to move
// direction			South = 270 / North = 90 / East = 0 / West = 180
typedef struct s_player_data
{
	int		int_cords[2];
	float	position[2];
	char	initial_direction;
	float	direction;
}	t_player_data;

typedef struct s_map_info
{
	char			**map;
	int				total_columns;
	int				total_lines;
}					t_map_info;

typedef struct s_input
{
	char			*path_to_map;
	char			**scene;
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	int				floor[3];
	int				ceiling[3];
	t_map_info		*map_info;
	t_player_data	player;

}					t_input;

typedef struct s_ray
{
	float	start_x;
	float	start_y;
	float	degree;
	float	contact_x;
	float	contact_y;
	float	length;
	float	step_x;
	float	step_y;
	char	*wall;
	char	direction;
} t_ray;

typedef struct s_cube
{
	float			viewplane;
	t_input			*input;
	t_player_data	*player;
	t_ray			**rays;
	mlx_t			*window;
	mlx_texture_t	**textures;
	mlx_image_t		*view;
	mlx_image_t		*minimap;
}					t_cube;

// main.c
int					main(int ac, char **av);

// input_parsing.c
void				parsing(char *path_to_map, t_input *input_info);
void				read_scene(t_input *input_info,
						char **scene);
char				**export_map(t_input *input_info, char **scene,
						int i);
char				**open_fd_export_content(t_input *input_info);
int					line_management(t_input *input_info, char **split_line,
						int i, int *elements_counter);

// input_parsing_helpers.c
bool				is_filename_correct(char *path_to_map);
void				remove_char_from_line(char **line, char to_remove);
int					count_lines_from_scene(t_input *input_info);
int					coma_check(char *line);

// fetch_elements.c
int					check_and_add_texture_path(char **split_line,
						t_input *input_info);
bool				is_image_reachable(char *path);
int					check_and_add_colors(char *line, t_input *input_info);
void				add_line_in_map_struct(char *line, t_input *input_info);
int					add_rgb_in_struct(t_input *input_info, char *identifier,
						int color, int i);

// free_functions.c
void				print_error_free_exit(t_input *input_info,
						char *error_message, bool free_array, char **array);
void				free_strings_array(char **array);
void				free_input_info_struct(t_input *input_info);

// map_parsing.c
bool				is_map_valid(t_map_info *map_info);
int					check_player(t_input *input_info, char **map);
void				add_player_info_in_struct(t_input *input_info, int line,
						int column);

// map_parsing_helpers.c
bool				is_line_from_map(char *line);
void				spaces_fill_up(t_map_info *map_info);
bool				is_wall_only(char *line);
bool				are_surroundings_valid(char **map, int element_line,
						int element_column);

// minimapper.c
void				draw_minimap(t_cube *game, char **minimap);
void				draw_line(t_cube *game, char *line, int position);
void				draw_cone(t_cube *game, float *position);

//ray_basing.c
void	base_position(char **map,t_ray *ray, float deg, float *position);

//ray_casting.c
void	set_corners(t_cube *game, t_ray *ray, int *position);
void	set_wallside(t_ray *ray, int *position, int *wall_position, char **map);
void	calculate_ray_length_and_wallside(t_cube *game, t_ray *ray, float *position);
void	cast_verticaly(t_cube *game, t_ray *ray, float deg, char **map);
void	cast_horizontaly(t_cube *game, t_ray *ray, float deg, char **map);
void	cast_rays(t_cube *game, char **map);

//corner_cases.c
int is_corner(char **map, t_ray *ray, int *int_pos, float *posi);
int	corner(char **map, t_ray *ray, float *posi, int *int_pos);
int borders_crossed(char **map, t_ray *ray, int *int_pos);

//small_corner_cases.c
int	small_corner(char **map, t_ray *ray, float *posi);
int is_small_corner(char **map, t_ray *ray, int *int_pos, float *posi);

// visualiser.c
uint32_t			paint_wall(t_cube *game, t_ray *ray, int *borders, int j);
void				draw_rays(t_cube *game);
void				fill_view(t_cube *game);
void				start_visuals(t_cube *game);
void				pixel_to_image(uint8_t *pixel, uint32_t colour);

// controler.c
void				actions(mlx_key_data_t key, void *params);
void				move_and_turn(mlx_key_data_t key, t_cube *game,
						float degree);
bool				is_move_possible(t_cube *game, float degree);

// movements.c
void				rotate_right(t_cube *game);
void				rotate_left(t_cube *game);
void				move(t_cube *game, float degree);
float				adjust_degree(enum e_directions direction, float degree);

//coordinate_reasignment.c
void	coordinates_float_to_int(int *ints, float *floats);
void	fadd_coordinate_x_y(float *coordinate, float x, float y);
void	fassign_coordinates(float *new, float *old);
void	floats_to_mapadress(int *adress, float *floats);
void	ints_to_mapadress(int *adress, int *ints);

//ft_math.c
void	set_borders(int *borders, t_ray *ray, float *posi);
void	unify_step(t_ray *ray);
void	set_x_y_int_steps(int *steps, float deg);
float	add_degree(float a, float b);

// image_handler.c
void				breakdown(char **map);
void				disappear(void *param);
void				set_game(t_cube *game);

// textures.c
uint32_t			get_south_north_color(t_cube *game, t_ray *ray,
						int *borders, int place);
uint32_t			get_west_east_color(t_cube *game, t_ray *ray, int *borders,
						int place);
uint32_t			load_color(int *colors);

// debug.c
void				ft_spike(t_cube *game, int i, int *borders);

#endif
