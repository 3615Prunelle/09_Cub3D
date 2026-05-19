/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_corner_cases.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlehmann <mlehmann@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 10:30:07 by mlehmann          #+#    #+#             */
/*   Updated: 2026/05/19 10:36:30 by mlehmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_small_corner(char **map, t_ray *ray, int *int_pos, float *posi)
{
	int	coords[2];
	int ncoords[4];

	coords[0] = int_pos[0] / MAP_SCALE;
	coords[1] = int_pos[1] / MAP_SCALE;
	ncoords[0] = (int)(posi[0] + ray->step_x) / MAP_SCALE;
	ncoords[1] = (int)(posi[1] + ray->step_y) / MAP_SCALE;
	ncoords[2] = (int)(posi[0] - ray->step_x) / MAP_SCALE;
	ncoords[3] = (int)(posi[1] - ray->step_y) / MAP_SCALE;
	if (map[coords[1]][coords[0]] != '0')
		return (1);
	if (map[ncoords[1]][coords[0]] != '0' && map[coords[1]][ncoords[0]]
		!= '0')
		return (1);
	if ((map[ncoords[3]][coords[0]] != '0' && map[coords[1]][ncoords[2]]
		!= '0')/* && ((int)ray->start_x / MAP_SCALE != coords[0]
		&& (int)ray->start_y / MAP_SCALE != coords[1])*/)
	{
		posi[0] -= ray->step_x;
		posi[1] -= ray->step_y;
		coordinates_float_to_int(int_pos, posi);
		return (1);
	}
	else
		return (0);
}

int	small_corner(char **map, t_ray *ray, float *posi)
{
	float	pre_posi[2];
	float	tiny_step[2];
	int		int_pos[2];
	int		borders[2];
	int		flag;

//	if (cant_be_corner(map, ray, posi) == 0)
//		return (0);
	flag = 0;
	fassign_coordinates(pre_posi, posi);
	tiny_step[0] = ray->step_x / 10;
	tiny_step[1] = ray->step_y / 10;
	set_borders(borders, ray, posi);
	coordinates_float_to_int(int_pos, posi);
	if (is_small_corner(map, ray, int_pos, posi) == 1)
	{
		while (map[int_pos[1] / MAP_SCALE][int_pos[0] / MAP_SCALE] == '0' && posi[0] != pre_posi[0] + ray->step_x)
		{
			fadd_coordinate_x_y(posi, tiny_step[0], tiny_step[1]);
			coordinates_float_to_int(int_pos, posi);
			if (borders_crossed(map, ray, borders, int_pos) == 1)
		//	if (map[int_pos[1] / MAP_SCALE][int_pos[0] / MAP_SCALE] != '0' || (map[int_pos[1] / MAP_SCALE][(int_pos[0] - (int)tiny_step[0] * 50) / MAP_SCALE] != '0' && map[(int_pos[1] - (int)tiny_step[1] * 50) / MAP_SCALE][int_pos[0] / MAP_SCALE] != '0'))
			{
				flag = 1;
				break ;
			}
		}
	}
	if (flag == 0)
		fassign_coordinates(posi, pre_posi);
	coordinates_float_to_int(int_pos, posi);
	return (flag);
}
