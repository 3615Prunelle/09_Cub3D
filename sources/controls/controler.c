/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 14:40:12 by mlehmann          #+#    #+#             */
/*   Updated: 2026/05/21 13:29:47 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		disappear(params);
	}
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
		if (key.key == MLX_KEY_D)
			degree = adjust_degree(RIGHT, degree);
		else if (key.key == MLX_KEY_S)
			degree = adjust_degree(BACK, degree);
		else if (key.key == MLX_KEY_A)
			degree = adjust_degree(LEFT, degree);
		if (!is_move_possible(game, degree))
			return ;
		move(game, degree);
	}
}

// Check which element is in the direction we're going
// If wall, return false
bool	is_move_possible(t_cube *game, float degree)
{
	char	**map;
	float	*current_position;
	float	target[2];

	map = game->input->map_info->map;
	current_position = game->player->position;
	target[0] = current_position[0];
	target[1] = current_position[1];
	if (degree > 270 || degree <= 90)
		target[1] -= 3;
	if (degree > 0 && degree <= 180)
		target[0] += 3;
	if (degree > 90 && degree <= 270)
		target[1] += 3;
	if (degree > 180 && degree <= 360)
		target[0] -= 3;
	if (map[(int)(target[1]) / MAP_SCALE]
			[(int)(target[0]) / MAP_SCALE] == '1')
	{
		printf("Boom - Oops, looks like there's a wall at [%d][%d]\n",
			(int)(target[1]) / MAP_SCALE, (int)(target[0]) / MAP_SCALE);
		return (false);
	}
	return (true);
}
