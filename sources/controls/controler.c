/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 14:40:12 by mlehmann          #+#    #+#             */
/*   Updated: 2026/03/25 19:13:27 by schappuy         ###   ########.fr       */
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

	if (key.key == MLX_KEY_RIGHT && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		turn_right(game);
	if (key.key == MLX_KEY_LEFT && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		turn_left(game);

	if ((key.key == MLX_KEY_W && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		|| (key.key == MLX_KEY_D && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		|| (key.key == MLX_KEY_S && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		|| (key.key == MLX_KEY_A && (key.action == MLX_PRESS || key.action == MLX_REPEAT)))
	{
		if (key.key == MLX_KEY_D)	// Right
			degree = adjust_degree(RIGHT, degree);
		else if (key.key == MLX_KEY_S)	// Backwards
			degree = adjust_degree(BACK, degree);
		else if (key.key == MLX_KEY_A)	// Left
			degree = adjust_degree(LEFT, degree);

		// HERE : Make sure the move is possible (player doesn't go through walls)
		if (!is_move_possible(game, degree))
			return ;
		move(game, degree);
	}

	// implement escape
	if (key.key == MLX_KEY_ESCAPE && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
	{
		printf(ERR_MSG_09);
		exit (1);		// clean and exit properly instead - See w/ Maxi for the clean MLX (disappear function ? TBC)
	}
	// implement red cross mouse hook - Nope ? Already dealt with through mlx_close_hook function (in main) TBC ? Check mem leaks

	draw_minimap(game, game->input->map_info->map);
}

bool	is_move_possible(t_cube *game, float degree)
{
	// Check which element is in the direction we're going
	// If wall, return false
	char	**map;
	map = game->input->map_info->map;

	float	*current_position;
	current_position = game->player->position;

	// Convert the float position[2] array into ints[2] doing the reverse of this :
	// game->player->position[0] = game->player->int_cords[0] * 32 + 16;
	// game->player->position[1] = game->player->int_cords[1] * 32 + 16;

	int		conv_position[2];
	conv_position[0] = (current_position[1] - 16) / 32;
	conv_position[1] = (current_position[0] - 16) / 32;

	// Find the target position depending on the degree
	int		target_position[2];
	target_position[0] = conv_position[0];	// Line
	target_position[1] = conv_position[1];	// Column

	if (degree > 315 || degree <= 45) // Looking North
		target_position[0] -= 1;							// Up one line, column unchanged
	if (degree > 45 && degree <= 135) // Looking East
		target_position[1] += 1;							// One column right, line unchanged
	if (degree > 135 && degree <= 225) // Looking South
		target_position[0] += 1;							// Down one line, column unchanged
	if (degree > 225 && degree <= 315) // Looking West
		target_position[1] -= 1;							// One column left, line unchanged

	// Check what element is at the target
	char	check;
	check = map[target_position[0]][target_position[1]];
	if (check == '1')
	{
		printf("Boom - Oops, looks like there's a wall at [%d][%d]\n", target_position[0], target_position[1]);
		// Why the left wall doesn't appear well ?
		// Are the spaces removed from the float position locator ?
		return (false);
	}
	return (true);
}
