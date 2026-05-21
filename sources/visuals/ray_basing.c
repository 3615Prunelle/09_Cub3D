/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_basing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlehmann <mlehmann@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 12:10:03 by mlehmann          #+#    #+#             */
/*   Updated: 2026/05/21 12:52:40 by mlehmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_raystart(char **map, t_ray *ray, float *posi, int *pre_pos)
{
	if (ray->direction == 'h')
	{
		while ((int)posi[0] / MAP_SCALE == pre_pos[0] / MAP_SCALE
			&& map[(int)posi[1] / MAP_SCALE][(int)posi[0] / MAP_SCALE] == '0')
		{
			posi[0] += ray->step_x;
			posi[1] += ray->step_y;
			if (small_corner(map, ray, posi) == 1)
				break ;
		}
	}
	else
	{
		while ((int)posi[1] / MAP_SCALE == pre_pos[1] / MAP_SCALE
			&& map[(int)posi[1] / MAP_SCALE][(int)posi[0] / MAP_SCALE] == '0')
		{
			posi[0] += ray->step_x;
			posi[1] += ray->step_y;
			if (small_corner(map, ray, posi) == 1)
				break ;
		}
	}
}

void	base_position(char **map, t_ray *ray, float deg, float *position)
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
