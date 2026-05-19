/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 09:28:39 by mlehmann          #+#    #+#             */
/*   Updated: 2026/05/18 11:23:20 by mlehmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_borders(int *borders, t_ray *ray, float *posi)
{
	if (ray->step_x > 0)
		borders[0] = ((((int)posi[0] / MAP_SCALE) + 1) * MAP_SCALE) + 1;
	else
		borders[0] = (((int)posi[0] / MAP_SCALE) * MAP_SCALE) - 1;
	if (ray->step_y > 0)
		borders[1] = ((((int)posi[1] / MAP_SCALE) + 1) * MAP_SCALE) + 1;
	else
		borders[1] = (((int)posi[1] / MAP_SCALE) * MAP_SCALE) - 1;
}

void	unify_step(t_ray *ray)
{
	float	max_step;

	max_step = fmaxf(fabsf(ray->step_x), fabsf(ray->step_y));
	if (max_step > 1)
	{
		ray->step_x /= max_step;
		ray->step_y /= max_step;
	}
}

void	set_x_y_int_steps(int *steps, float deg)
{
	steps[0] = 1;
	steps[1] = 1;
	if (deg >= 180 && deg <= 360)
		steps[0] = -1;
	if (deg >= 270 || deg <= 90)
		steps[1] = -1;
}

float	add_degree(float a, float b)
{
	if ((a + b) < 0)
		return (a + b + 360);
	if ((a + b) > 360)
		return (a + b - 360);
	if ((a + b) == 360)
		return (0);
	else
		return (a + b);
}
