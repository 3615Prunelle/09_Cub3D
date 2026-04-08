/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlehmann <mlehmann@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 11:07:54 by mlehmann          #+#    #+#             */
/*   Updated: 2026/04/01 14:43:38 by mlehmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_corners(t_cube *game, t_ray *ray, int *position)
{
	position[0] *= 32;
	position[1] *= 32;
	if (game->player->position[1] <= position[1])
		ray->wall[0] = 'S';
	else if (game->player->position[0] <= position[0])
		ray->wall[0] = 'E';
	else if (game->player->position[1] >= position[1])
		ray->wall[0] = 'N';
	else if (game->player->position[0] >= position[0])
		ray->wall[0] = 'W';
	else
		ray->wall[0] = 'K';
}

void	set_wallside(t_ray *ray, int *position, int *wall_position, char **map)
{
	if (wall_position[0] == position[0])
	{
		if (wall_position[1] - position[1] == 1)
			ray->wall[0] = 'N';
		if (wall_position[1] - position[1] == -1)
			ray->wall[0] = 'S';
		return ;
	}
	else if (wall_position[1] == position[1])
	{
		if (wall_position[0] - position[0] == 1)
			ray->wall[0] = 'W';
		if (wall_position[0] - position[0] == -1)
			ray->wall[0] = 'E';
		return ;
	}
	else if (map[wall_position[1]][position[0]] == '1')
	{
		if (wall_position[0] - position[0] == 1)
			ray->wall[0] = 'W';
		if (wall_position[0] - position[0] == -1)
			ray->wall[0] = 'E';
		return ;
	}
	else if (map[position[1]][wall_position[0]] == '1')
	{
		if (wall_position[1] - position[1] == 1)
			ray->wall[0] = 'N';
		if (wall_position[1] - position[1] == -1)
			ray->wall[0] = 'S';
		return ;
	}
	else
		ray->wall[0] = 'K';
}

void	calculate_ray_length_and_wallside_v(t_cube *game, t_ray *ray, float deg, float *position)
{
	float	wall_posi[2];
	int		int_pos[2];
	int		int_wall_p[2];
	char	**map;

	map = game->input->map_info->map;
	wall_posi[0] = position[0];
	wall_posi[1] = position[1];
	coordinates_float_to_int(int_wall_p, wall_posi);
	coordinates_float_to_int(int_pos, position);
//	printf("wall raycord[%.2f/%.2f]\t", position[0], position[1]);//debug
	while (map[int_wall_p[1] / 32][int_wall_p[0] / 32] == '1')
	{
		wall_posi[0] -= ray->step_x;
		wall_posi[1] -= ray->step_y;
		coordinates_float_to_int(int_wall_p, wall_posi);
	}
	int_wall_p[0] /=32;
	int_wall_p[1] /=32;
	ray->x_contact = wall_posi[0];
	ray->y_contact = wall_posi[1];
	int_pos[0] /=32;
	int_pos[1] /=32;
	set_wallside(ray, int_pos, int_wall_p, game->input->map_info->map);
	if (ray->wall[0] == 'K')
		set_corners(game, ray, int_pos);
	ray->length = sqrt(pow(wall_posi[0] - game->player->position[0], 2) + pow(wall_posi[1] - game->player->position[1], 2));
//	printf("wall cont[%.2f/%.2f]\t", wall_posi[0]/32, wall_posi[1]/32);//debug
//	ray->length = fabs(fabs(wall_posi[1] - game->player->position[1]) / cos(deg * DEG_TO_RAD));
}

void	calculate_ray_length_and_wallside_h(t_cube *game, t_ray *ray, float deg, float *position)
{
	float	wall_posi[2];
	int		int_pos[2];
	int		int_wall_p[2];
	char	**map;

	map = game->input->map_info->map;
	wall_posi[0] = position[0];
	wall_posi[1] = position[1];
	coordinates_float_to_int(int_wall_p, wall_posi);
	coordinates_float_to_int(int_pos, position);
//	printf("wall raycord[%.2f/%.2f]\t", position[0], position[1]);//debug
	while (map[int_wall_p[1] / 32][int_wall_p[0] / 32] == '1')
	{
		wall_posi[0] -= ray->step_x;
		wall_posi[1] -= ray->step_y;
		coordinates_float_to_int(int_wall_p, wall_posi);
	}
	int_wall_p[0] /=32;
	int_wall_p[1] /=32;
	ray->x_contact = wall_posi[0];
	ray->y_contact = wall_posi[1];
	int_pos[0] /=32;
	int_pos[1] /=32;
	set_wallside(ray, int_pos, int_wall_p, game->input->map_info->map);
	if (ray->wall[0] == 'K')
		set_corners(game, ray, int_pos);
	ray->length = sqrt(pow(wall_posi[0] - game->player->position[0], 2) + pow(wall_posi[1] - game->player->position[1], 2));
//	printf("wall cont[%.2f/%.2f]\t", wall_posi[0]/32, wall_posi[1]/32);//debug
//	ray->length = fabs(fabs(wall_posi[0] - game->player->position[0]) / sin(deg * DEG_TO_RAD));
}

void	cast_verticaly(t_cube *game, t_ray *ray, float deg, char **map)
{
	int		int_step[2];
	float	position[2];
	int		int_pos[2];
	float	pre_length;

//	printf("cast verti\t");//debug
	pre_length = ray->length;
	set_x_y_int_steps(int_step, deg);
	position[0] = game->player->int_cords[0];
	position[1] = game->player->int_cords[1];
	int_pos[0] = (int)position[0];
	int_pos[1] = (int)position[1];
	ray->step_y = (float)int_step[1];
	ray->step_x = int_step[0] * fabsf(int_step[1] * tanf(deg * DEG_TO_RAD));
	while (map[int_pos[1] /32][int_pos[0] /32] != '1')
	{
		position[0] += ray->step_x;
		position[1] += ray->step_y;
		int_pos[0] = (int)position[0];
		int_pos[1] = (int)position[1];
	}
	calculate_ray_length_and_wallside_v(game, ray, deg, position);
	if (pre_length != 1.0 && ray->length < pre_length)
		ray->length = pre_length;
}

void	cast_horizontaly(t_cube *game, t_ray *ray, float deg, char **map)
{
	int		int_step[2];
	float	position[2];
	int		int_pos[2];

//	printf("cast horizont\t");//debug
	set_x_y_int_steps(int_step, deg);
	position[0] = game->player->int_cords[0];
	position[1] = game->player->int_cords[1];
	int_pos[0] = (int)position[0];
	int_pos[1] = (int)position[1];
	ray->step_x = (float)int_step[0];
	ray->step_y = int_step[1] * fabsf((int_step[0] / tanf(deg * DEG_TO_RAD)));
	while (map[int_pos[1] / 32][int_pos[0] / 32] != '1')
	{
		position[0] += ray->step_x;
		position[1] += ray->step_y;
		int_pos[0] = (int)position[0];
		int_pos[1] = (int)position[1];
	}
	calculate_ray_length_and_wallside_h(game, ray, deg, position);
}
/*void	cast_verticaly(t_cube *game, t_ray *ray, float deg, char **map)
{
	int		int_step[2];
	float	position[2];
	int		int_pos[2];

//	printf("cast verti\t");//debug
	set_x_y_int_steps(int_step, deg);
	position[0] = game->player->int_cords[0] / 32 + 0.5;
	position[1] = game->player->int_cords[1] / 32 + 0.5;
	int_pos[0] = (int)position[0];
	int_pos[1] = (int)position[1];
	ray->step_y = (float)int_step[1];
	ray->step_x = int_step[0] * fabsf(int_step[1] * tanf(deg * DEG_TO_RAD));
	while (map[int_pos[1]][int_pos[0]] != '1')
	{
		position[0] += ray->step_x;
		position[1] += ray->step_y;
		int_pos[0] = (int)position[0];
		int_pos[1] = (int)position[1];
	}
	calculate_ray_length_and_wallside_v(game, ray, deg, position);
}

void	cast_horizontaly(t_cube *game, t_ray *ray, float deg, char **map)
{
	int		int_step[2];
	float	position[2];
	int		int_pos[2];

//	printf("cast horizont\t");//debug
	set_x_y_int_steps(int_step, deg);
	position[0] = game->player->int_cords[0] / 32 + 0.5;
	position[1] = game->player->int_cords[1] / 32 + 0.5;
	int_pos[0] = (int)position[0];
	int_pos[1] = (int)position[1];
	ray->step_x = (float)int_step[0];
	ray->step_y = int_step[1] * (int_step[0] / tanf(deg * DEG_TO_RAD));
	while (map[int_pos[1]][int_pos[0]] != '1')
	{
		position[0] += ray->step_x;
		position[1] += ray->step_y;
		int_pos[0] = (int)position[0];
		int_pos[1] = (int)position[1];
	}
	calculate_ray_length_and_wallside_h(game, ray, deg, position);
}*/

void	cast_rays(t_cube *game, char **map)
{
	int		i;
//	int		test;//debug
	float	fov_step;
	float	degry;

//	printf("\n");//debug
	i = 0;
	fov_step = FOW / VIEW_WIDTH;
	while (i < VIEW_WIDTH)
	{
		game->rays[i]->length = 1.0;
		degry = add_degree(game->player->direction, (-1 * FOW / 2) + (fov_step * i));
		game->rays[i]->degree = degry;
//		test = i / 10;//debug
//		printf("Ray [%d - %d]\tdegree: %.2f\t", i, i + 10,degry);//debug
		if (degry == 45 || degry == 135 || degry == 225 || degry == 315)
			cast_horizontaly(game, game->rays[i], degry + fov_step, map);
		else
		{
			if ((degry >= 45 && degry <= 135) || (degry >= 225 && degry <= 315))
				cast_horizontaly(game,game->rays[i], degry, map);
			if (degry > 315 || degry < 45 || (degry > 135 && degry < 225))
				cast_verticaly(game, game->rays[i], degry, map);
		}
/*		while (i / 10 == test && VIEW_WIDTH - 1 > i)//debug
		{
			i++;
			game->rays[i]->length = game->rays[i - 1]->length;
			game->rays[i]->step_x = game->rays[i - 1]->step_x;
			game->rays[i]->step_y = game->rays[i - 1]->step_y;
			game->rays[i]->wall = game->rays[i - 1]->wall;
		}//debug
		printf("length: %.2f\n", game->rays[i]->length);//debug*/
		game->rays[i]->length = game->rays[i]->length * cosf(add_degree(degry, - game->player->direction) * DEG_TO_RAD);
		i++;
	}
}
