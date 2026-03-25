/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlehmann <mlehmann@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 11:07:54 by mlehmann          #+#    #+#             */
/*   Updated: 2026/03/25 13:27:14 by mlehmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast_horizontaly(t_cube *game, t_ray *ray, float deg, char **map)
{
	int		int_step[2];
	float	position[2];
	int		int_pos[2];

	int_step[0] = 1;
	if (deg > 180 && deg < 360)
		int_step[0] = -1;
	int_step[1] = 1;
	if (deg > 270 || deg < 90)
		int_step[1] = -1;
	position[0] = game->player->int_cords[0] / 32 + 0.1;
	position[1] = game->player->int_cords[1] / 32 + 0.1;
	int_pos[0] = (int)position[0];
	int_pos[1] = (int)position[1];
	ray->step_x = (float)int_step[0];
	ray->step_y = int_step[1] * fabsf(int_step[0] / tanf(deg * DEG_TO_RAD));
	while (map[int_pos[1]][int_pos[0]] != '1')
	{
		position[0] += ray->step_x;
		position[1] += ray->step_y;
		int_pos[0] = (int)position[0];
		int_pos[1] = (int)position[1];
	}
}

void	cast_rays(t_cube *game, char **map)
{
	int		i;
	float	fov_step;
	float	degry;

	i = 0;
	fov_step = 60.0 / VIEW_WIDTH;
	while (i < VIEW_WIDTH)
	{
		game->rays[i]->length = 0.0;
		degry = add_degree(game->player->direction, -30 + fov_step * i);
		if ((degry >= 44 && degry <= 136) || (degry >= 224 && degry <= 316))
			cast_horizontaly(game,game->rays[i], degry, map);
		if (degry >= 314 || degry <= 46 || (degry >= 134 && degry <= 226))
			cast_verticaly(game, game->rays[i], degry, map);
		i++;
	}
}
