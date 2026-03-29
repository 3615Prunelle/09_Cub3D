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

void	set_wallside(t_ray *ray, int[2] position, int[2] wall_position)
{
	if (wall_position[0] > position[0])
		ray->wall[0] = 'E';
	if (wall_position[0] < position[0])
		ray->wall[0] = 'W';
	if (wall_position[1] > position[1])
		ray->wall[0] = 'N';
	if (wall_position[1] > position[1])
		ray->wall[0] = 'S';
}

void	calculate_ray_length_and_wallside(t_cube *game, t_ray *ray, float deg, float[2] position)
{
	float	wall_posi[2];
	int		int_pos[2];
	int		int_wall_p[2];

	wall_posi[0] = position[0] * 32;
	wall_posi[1] = position[1] * 32;
	coordinates_float_to_int(int_wall_p, wall_posi);
	coordinates_float_to_int(int_pos, position);
	while (int_wall_p[0] / 32 == int_pos[0] && int_wall_p[1] / 32 == int_pos[1])
	{
		wall_posi[0] -= ray->step_x;
		wall_posi[1] -= ray->step_y;
		coordinates_float_to_int(int_wall_p, wall_posi);
	}
	int_wall_p[0] /=32;
	int_wall_p[1] /=32;
	set_wallside(ray, int_pos, int_wall_p);
	ray->length = fabs(fabs(wall_posi[1] - game->player->position[1]) / sin(deg * DEG_TO_RAD));
}

void	cast_horizontaly(t_cube *game, t_ray *ray, float deg, char **map)
{
	int		int_step[2];
	float	position[2];
	int		int_pos[2];

	set_x_y_int_steps(&int_step, deg);
	position[0] = game->player->int_cords[0] / 32 + 0.5;
	position[1] = game->player->int_cords[1] / 32 + 0.5;
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
	calculate_ray_length_and_wallside(game, ray, deg, position);
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
		if (degry == 45 || degry == 135 || degry == 225 || degry == 315)
			cast_horizontaly(game, game->rays[i], degry + fov_step, map);
		else
		{
			if ((degry >= 44 && degry <= 136) || (degry >= 224 && degry <= 316))
				cast_horizontaly(game,game->rays[i], degry, map);
			if (degry >= 314 || degry <= 46 || (degry >= 134 && degry <= 226))
				cast_verticaly(game, game->rays[i], degry, map);
		}
		i++;
	}
}
