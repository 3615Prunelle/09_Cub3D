/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corner_cases.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlehmann <mlehmann@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 14:09:59 by mlehmann          #+#    #+#             */
/*   Updated: 2026/05/19 12:15:50 by mlehmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int borders_crossed(char **map, t_ray *ray, int *int_pos)
{
	int	cords[2];

	cords[0] = int_pos[0] / MAP_SCALE;
	cords[1] = int_pos[1] / MAP_SCALE;
	if (ray->step_x > 0 && ray->step_y > 0 && map[cords[1] - 1][cords[0]]
		!= '0' && map[cords[1]][cords[0] - 1] != '0')
		return (1);
	if (ray->step_x < 0 && ray->step_y > 0 && map[cords[1] - 1][cords[0]]
		!= '0' && map[cords[1]][cords[0] + 1] != '0')
		return (1);
	if (ray->step_x > 0 && ray->step_y < 0 && map[cords[1] + 1][cords[0]]
		!= '0' && map[cords[1]][cords[0] - 1] != '0')
		return (1);
	if (ray->step_x < 0 && ray->step_y < 0 && map[cords[1] + 1][cords[0]]
		!= '0' && map[cords[1]][cords[0] + 1] != '0')
		return (1);
	if (map[cords[1]][cords[0]] != '0')
		return (1);
	else
		return (0);
}

int is_corner(char **map, t_ray *ray, int *int_pos, float *posi)
{
	int	coords[2];
	int	int_step[2];

	coords[0] = int_pos[0] / MAP_SCALE;
	coords[1] = int_pos[1] / MAP_SCALE;
	set_x_y_int_steps(int_step, ray->degree);
	if (map[coords[1]][coords[0]] != '0')
		return (1);
	if (map[coords[1] + int_step[1]][coords[0]] != '0'
		|| map[coords[1]][coords[0] + int_step[0]] != '0')
		return (1);
	if ((map[coords[1] - int_step[1]][coords[0]] != '0' && map[coords[1]]
		[coords[0] - int_step[0]] != '0') && ((int)ray->start_x / MAP_SCALE
		!= coords[0] && (int)ray->start_y / MAP_SCALE != coords[1]))
	{
		posi[0] -= ray->step_x;
		posi[1] -= ray->step_y;
		coordinates_float_to_int(int_pos, posi);
		return (1);
	}
	else
		return (0);
}

int	corner(char **map, t_ray *ray, float *posi, int *int_pos)
{
	float	pre_posi[2];
	float	tiny_step[2];
	int		borders[2];
	int		flag;

	flag = 0;
	fassign_coordinates(pre_posi, posi);
	tiny_step[0] = ray->step_x / 200;
	tiny_step[1] = ray->step_y / 200;
	set_borders(borders, ray, posi);
	coordinates_float_to_int(int_pos, posi);
	if (is_corner(map, ray, int_pos, posi) == 1)
	{
		while (map[int_pos[1] / MAP_SCALE][int_pos[0] / MAP_SCALE] == '0' && posi[0] != pre_posi[0] + ray->step_x)
		{
			fadd_coordinate_x_y(posi, tiny_step[0], tiny_step[1]);
			coordinates_float_to_int(int_pos, posi);
			if (borders_crossed(map, ray, int_pos) == 1)
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
