/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinate_reasignment.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlehmann <mlehmann@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 11:07:53 by mlehmann          #+#    #+#             */
/*   Updated: 2026/05/20 11:57:25 by mlehmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	coordinates_float_to_int(int *ints, float *floats)
{
	ints[0] = (int)floats[0];
	ints[1] = (int)floats[1];
}

void	fassign_coordinates(float *new, float *old)
{
	new[0] = old[0];
	new[1] = old[1];
}

void	fadd_coordinate_x_y(float *coordinate, float x, float y)
{
	coordinate[0] += x;
	coordinate[1] += y;
}

void	floats_to_mapadress(int *adress, float *floats)
{
	adress[0] = (int)floats[0] / MAP_SCALE;
	adress[1] = (int)floats[1] / MAP_SCALE;
}

void	ints_to_mapadress(int *adress, int *ints)
{
	adress[0] = ints[0] / MAP_SCALE;
	adress[1] = ints[1] / MAP_SCALE;
}
