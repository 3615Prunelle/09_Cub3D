/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 20:17:58 by schappuy          #+#    #+#             */
/*   Updated: 2026/03/13 09:44:26 by mlehmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include <fcntl.h>		// open
# include <limits.h>	// INT_MAX
# include <stdbool.h>
# include <math.h>	//the scary stuff (tan, cos, sin, atan) but also yummy pie
# include <stdio.h> //mal lock mal nicht lock
# include <stdlib.h>	// EXIT_FAILURE, EXIT_SUCCESS
# include <sys/stat.h>	// open
# include <sys/time.h>	// time
# include <sys/types.h>	// opendir
# include <unistd.h>	// close, pipe, fork, read, write, getcwd, chdir
# include <MLX42.h> // ADDED MLX42 ;D
# define DEG_TO_RAD 0.017453293


// Structs
typedef struct s_player_data
{
	int		int_cords[2];
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
}	t_input;

typedef struct s_cube
{
	t_input			*input;
	t_player_data	*player;
	mlx_t			*window;
	mlx_image_t		*view;
	mlx_image_t		*minimap;
} t_cube;

// main.c

//minimapper.c
void	draw_minimap(t_cube *game, char **minimap);
void	draw_line(t_cube *game, char *line, int position);
void	draw_cone(t_cube * game, char **minimap);
void	start_visuals(t_cube *game);

//visualiser.c
void	pixel_to_image(uint8_t *pixel, uint32_t colour);

//controller.c
void	actions(mlx_key_data_t key, void *params);

//movements.c
void	turn_right(t_cube *game);
void	turn_left(t_cube *game);

//ft_math.c
float	add_degree(float a, float b);

// split by file

#endif
