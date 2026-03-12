/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 20:17:58 by schappuy          #+#    #+#             */
/*   Updated: 2026/03/12 12:35:32 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"			// no need because in Makefile ?
# include "get_next_line.h"	// no need because in Makefile ?
# include <fcntl.h>			// open
# include <limits.h>		// INT_MAX
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>		// EXIT_FAILURE, EXIT_SUCCESS
# include <string.h>
# include <errno.h>
# include <sys/stat.h>		// open
# include <sys/time.h>		// time
# include <sys/types.h>		// opendir
# include <unistd.h>		// close, pipe, fork, read, write, getcwd, chdir
// ADD MLX42				// no need because in Makefile ?

# define ERR_MSG_01	"Invalid amount of args - Just provide a map in .cub format\n"
# define ERR_MSG_02	"Invalid filename - We only accept .cub format\n"
# define ERR_MSG_03	"Invalid line in scene description (path to texture)\n"
# define ERR_MSG_04	"Missing element(s) or invalid line (map)\n"
# define ERR_MSG_05	"Empty .cub file\n"
# define ERR_MSG_06	"Invalid line in scene description (color)\n"
# define ERR_MSG_07	"Invalid map\n"
# define ERR_MSG_08	"Something wrong with the player\n"

// Structs
typedef struct s_player_data
{
	int		initial_coordinates[2];	// [0] = line	[1] = column
	float	position[2];			// This gets updated as soon as player starts to move
	char	initial_direction;
	float	direction;				// Conversion from initial_direction variable : South = 270 / North = 90 / East = 0 / West = 180
}	t_player_data;

typedef struct s_map_info
{
	char	**map;
	int		max_columns;
	int		max_lines;
}	t_map_info;

typedef	struct	s_input
{
	char			*path_to_map;
	char			*NO;
	char			*SO;
	char			*WE;
	char			*EA;
	int				floor[3];
	int				ceiling[3];
	t_map_info		*map_info;
	t_player_data	player;

}	t_input;

// main.c
int	main(int ac, char **av);

// input_parsing.c
void	parsing(char *path_to_map, t_input *input_info);
bool	is_filename_correct(char *path_to_map);
void	read_scene_description(t_input *input_info);
int		count_lines_from_scene_description(t_input *input_info);
bool	is_line_from_map(char *line);
void	spaces_fill_up(t_map_info *map_info);

// fetch_elements.c
int		check_and_add_texture_path(char *line, t_input *input_info);
char	*clean_path(char *full_line);
int		check_and_add_colors(char *line, t_input *input_info);
char	**get_rgb_array(char *full_line);
void	add_line_in_map_struct(char *line, t_input *input_info);

// free_functions.c
void	print_error_free_exit(t_input *input_info, char *error_message, bool free_array, char **array);
void	free_strings_array(char **array);
void	free_input_info_struct(t_input *input_info);

// map_parsing.c
bool	is_map_valid(t_map_info *map_info);
bool	is_wall_only(char *line);
bool	are_surroundings_valid(char **map, int element_line, int element_column);
int		update_player_info(t_input *input_info);

#endif
