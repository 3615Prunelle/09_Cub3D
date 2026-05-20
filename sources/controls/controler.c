/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 14:40:12 by mlehmann          #+#    #+#             */
/*   Updated: 2026/05/20 12:50:49 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
Subject :
	The left and right arrow keys of the keyboard must allow you to look left and right in the maze
	The W, A, S, and D keys must allow you to move the point of view through the maze
	Pressing ESC must close the window and quit the program cleanly
	Clicking on the red cross on the window’s frame must close the window and quit the program cleanly
*/
void	actions(mlx_key_data_t key, void *params)
{
	t_cube	*game;
	float	degree;

	game = params;
	degree = game->player->direction;
	move_and_turn(key, game, degree);
	if (key.key == MLX_KEY_ESCAPE && (key.action == MLX_PRESS
			|| key.action == MLX_REPEAT))
	{
		printf(MSG_1);
		exit(1); // clean and exit properly instead - See w/ Maxi for the clean MLX (disappear function ? TBC)
	}
	// red cross mouse hook already dealt with through mlx_close_hook function (in main) - Check mem leaks
	cast_rays(game, game->input->map_info->map);
	fill_view(game);
	draw_rays(game);
	draw_minimap(game, game->input->map_info->map);
}

void	move_and_turn(mlx_key_data_t key, t_cube *game, float degree)
{
	if (key.key == MLX_KEY_RIGHT && (key.action == MLX_PRESS
			|| key.action == MLX_REPEAT))
		rotate_right(game);
	if (key.key == MLX_KEY_LEFT && (key.action == MLX_PRESS
			|| key.action == MLX_REPEAT))
		rotate_left(game);
	if ((key.key == MLX_KEY_W && (key.action == MLX_PRESS
				|| key.action == MLX_REPEAT)) || (key.key == MLX_KEY_D
			&& (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		|| (key.key == MLX_KEY_S && (key.action == MLX_PRESS
				|| key.action == MLX_REPEAT)) || (key.key == MLX_KEY_A
			&& (key.action == MLX_PRESS || key.action == MLX_REPEAT)))
	{
		if (key.key == MLX_KEY_D)					// Right
			degree = adjust_degree(RIGHT, degree);
		else if (key.key == MLX_KEY_S)				// Backwards
			degree = adjust_degree(BACK, degree);
		else if (key.key == MLX_KEY_A)				// Left
			degree = adjust_degree(LEFT, degree);
		if (!is_move_possible(game, degree))
			return ;
		move(game, degree);
	}
}

// Check which element is in the direction we're going
// If wall, return false
// Find the target position depending on the degree - Caution : The changes are in pixels, they'll be converted to int a few lines below
// Converts the float position[2] array into ints[2] to find what is the element that matches the target, in the logical map
bool	is_move_possible(t_cube *game, float degree)
{
	char	**map;
	float	*current_position;
	float	target_position[2];
	int		conv_position[2];
	char	target_element;

	map = game->input->map_info->map;
	current_position = game->player->position;
	target_position[0] = current_position[0];	// Line
	target_position[1] = current_position[1];	// Column
	if (degree > 270 || degree <= 90)	// Looking North
		target_position[1] -= 3;		// Up one line, column unchanged
	if (degree > 0 && degree <= 180)	// Looking East
		target_position[0] += 3;		// One column right, line unchanged
	if (degree > 90 && degree <= 270)	// Looking South
		target_position[1] += 3;		// Down one line, column unchanged
	if (degree > 180 && degree <= 360)	// Looking West
		target_position[0] -= 3;		// One column left, line unchanged
	conv_position[0] = (target_position[1]) / MAP_SCALE;
	conv_position[1] = (target_position[0]) / MAP_SCALE;
	target_element = map[conv_position[0]][conv_position[1]];
	if (target_element == '1')
	{
		//printf("Boom - Oops, looks like there's a wall at [%d][%d]\t[%f][%f]\n", conv_position[0], conv_position[1], (target_position[1]) / MAP_SCALE, (target_position[0]) / MAP_SCALE);		// Debug
		return (false);
	}
	return (true);
}
