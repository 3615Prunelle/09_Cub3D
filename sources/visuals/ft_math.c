/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 09:28:39 by mlehmann          #+#    #+#             */
/*   Updated: 2026/03/16 15:55:48 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	coordinates_float_to_int(int *ints, float *floats)
{
	ints[0] = (int)floats[0];
	ints[1] = (int)floats[1];
}

void	set_x_y_int_steps(int *steps, float deg)
{
	steps[0] = 1;
	steps[1] = 1;
	if (deg > 180 && deg < 360)
		steps[0] = -1;
	if (deg > 270 || deg < 90)
		steps[1] = -1;
}

float	add_degree(float a, float b)
{
	if ((a + b) < 0)
		return (a + b + 360);
	if ((a + b) > 360)
		return (a + b - 360);
	else
		return (a + b);
}
