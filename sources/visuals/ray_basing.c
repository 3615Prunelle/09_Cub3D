/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_basing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlehmann <mlehmann@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 12:10:03 by mlehmann          #+#    #+#             */
/*   Updated: 2026/05/20 11:31:35 by mlehmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_raystart(char **map, t_ray *ray, float *position, int *pre_pos)
{
	int		borders[2];

	set_borders(borders, ray, position);
	if (ray->direction == 'h')
	{
		while ((int)position[0] / MAP_SCALE == pre_pos[0] / MAP_SCALE && map[(int)position[1] / MAP_SCALE][(int)position[0] / MAP_SCALE] == '0')
		{
			position[0] += ray->step_x;
			position[1] += ray->step_y;
			if (small_corner(map, ray, position) == 1)
				break ;
		}
	}
	else
	{
		while ((int)position[1] / MAP_SCALE == pre_pos[1] / MAP_SCALE && map[(int)position[1] / MAP_SCALE][(int)position[0] / MAP_SCALE] == '0')
		{
			position[0] += ray->step_x;
			position[1] += ray->step_y;
			if (small_corner(map, ray, position) == 1)
				break ;
		}
	}
}

void	base_position(char **map,t_ray *ray, float deg, float *position)
{
	int	pre_pos[2];
	int	int_step[2];

	pre_pos[0] = (int)position[0];
	pre_pos[1] = (int)position[1];
	set_x_y_int_steps(int_step, deg);
	if (ray->direction == 'h')
	{
		ray->step_x = int_step[0];
		ray->step_y = int_step[1] * fabsf(int_step[0] / tanf(deg * DEG_TO_RAD));
	}
	else
	{
		ray->step_x = int_step[0] * fabsf(int_step[1] * tanf(deg * DEG_TO_RAD));
		ray->step_y = int_step[1];
	}
	unify_step(ray);
	set_raystart(map, ray, position, pre_pos);
	ray->step_x *= MAP_SCALE;
	ray->step_y *= MAP_SCALE;
}
