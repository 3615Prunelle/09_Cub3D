/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlehmann <mlehmann@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 11:07:54 by mlehmann          #+#    #+#             */
/*   Updated: 2026/05/20 11:28:09 by mlehmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast_verticaly(t_cube *game, t_ray *ray, float deg, char **map)
{
	float	position[2];
	int		int_pos[2];
	float	pre_length;

	pre_length = ray->length;
	ray->direction = 'v';
	position[0] = game->player->position[0];
	position[1] = game->player->position[1];
	base_position(map, ray, deg, position);
	coordinates_float_to_int(int_pos, position);
	if (corner(map, ray, position, int_pos) == 1)
	{
		calculate_ray_length_and_wallside(game, ray, position);
		return ;
	}
	while (map[int_pos[1] / MAP_SCALE][int_pos[0] / MAP_SCALE] == '0')
	{
		if (corner(map, ray, position, int_pos) == 1)
			break ;
		position[0] += ray->step_x;
		position[1] += ray->step_y;
		coordinates_float_to_int(int_pos, position);
	}
	calculate_ray_length_and_wallside(game, ray, position);
	if (pre_length != 1.0 && ray->length > pre_length)
	{
		ray->length = pre_length;
		ray->direction = 'h';
	}
	else if (ray->direction != 'h')
		ray->direction = 'v';
}

void	cast_horizontaly(t_cube *game, t_ray *ray, float deg, char **map)
{
	float	position[2];
	int		int_pos[2];

	ray->direction = 'h';
	position[0] = game->player->position[0];
	position[1] = game->player->position[1];
	ray->start_x = position[0];
	ray->start_y = position[1];
	base_position(map, ray, deg, position);
	coordinates_float_to_int(int_pos, position);
	if (corner(map, ray, position, int_pos) == 1)
	{
		calculate_ray_length_and_wallside(game, ray, position);
		return ;
	}
	while (map[int_pos[1] / MAP_SCALE][int_pos[0] / MAP_SCALE] == '0')
	{
		if (corner(map, ray, position, int_pos) == 1)
			break ;
		position[0] += ray->step_x;
		position[1] += ray->step_y;
		coordinates_float_to_int(int_pos, position);
	}
	calculate_ray_length_and_wallside(game, ray, position);
}

void	cast_rays(t_cube *game, char **map)
{
	int		i;
	float	degry;
	float	view_pos;

	i = 0;
	while (i < VIEW_WIDTH)
	{
		game->rays[i]->id = i;
		view_pos = (((i * 2.0) - (VIEW_WIDTH - 1.0)) / (VIEW_WIDTH - 1.0))
			* (game->viewplane / 2);
		game->rays[i]->direction = '0';
		game->rays[i]->length = 1.0;
		degry = add_degree(game->player->direction,
				atan2(view_pos, game->viewplane) / DEG_TO_RAD);
		game->rays[i]->degree = degry;
		if ((degry >= 40 && degry <= 140) || (degry >= 220 && degry <= 320))
			cast_horizontaly(game, game->rays[i], degry, map);
		if (degry > 310 || degry < 50 || (degry > 130 && degry < 230))
			cast_verticaly(game, game->rays[i], degry, map);
		game->rays[i]->length = game->rays[i]->length
			* cosf(atan2(view_pos, game->viewplane));
		i += 1;
	}
}
