/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 20:17:58 by schappuy          #+#    #+#             */
/*   Updated: 2026/02/26 18:19:28 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "get_next_line.h"
# include <fcntl.h>		// open
# include <limits.h>	// INT_MAX
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>	// EXIT_FAILURE, EXIT_SUCCESS
# include <sys/stat.h>	// open
# include <sys/time.h>	// time
# include <sys/types.h>	// opendir
# include <unistd.h>	// close, pipe, fork, read, write, getcwd, chdir
// ADD MLX42

// Structs
typedef struct s_player_data
{
	int		initial_coordinates[2];
	float	position[2];		// This gets updated as soon as player starts to move
	char	initial_direction;
	float	direction;			// Conversion from initial_direction variable : South = 270 / North = 90 / East = 0 / West = 180
}	t_player_data;

typedef	struct	s_input
{
	char			*NO;
	char			*SO;
	char			*WE;
	char			*EA;
	int				floor[3];
	int				ceiling[3];
	char			**map;
	t_player_data	player;

}	t_input;

// main.c
int	main(int ac, char **av);

// parsing.c
int		parsing(char *path_to_map, t_input *map_data);
bool	is_filename_correct(char *path_to_map);
int		fill_up_struct(char *path_to_map, t_input *map_data);
int		paths_to_textures(char **file_content, t_input *map_data);
char	*clean_path(char *full_line);
int		floor_and_ceiling_colors(char **file_content, t_input *map_data);
char	**get_rgb_array(char *full_line);
int		create_map(char **file_content, t_input *map_data);

#endif
