/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_assignment_and_color.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 14:47:27 by mlehmann          #+#    #+#             */
/*   Updated: 2026/05/20 13:03:37 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	paint_wall(t_cube *game, t_ray *ray, int *borders, int j)
{
	if (ray->wall[0] == 'N' && game->input->north)
		return (get_south_north_color(game, ray, borders, j));
	if (ray->wall[0] == 'S' && game->input->south)
		return (get_south_north_color(game, ray, borders, j));
	if (ray->wall[0] == 'W' && game->input->west)
		return (get_west_east_color(game, ray, borders, j));
	if (ray->wall[0] == 'E' && game->input->east)
		return (get_west_east_color(game, ray, borders, j));
	if (ray->wall[0] == 'K' && game->input->south)
		return (0x00FF00FF);
	return (0x000000FF);
}

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
	if (map[wall_position[1]][position[0]] != '0')
	{
		if (wall_position[0] - position[0] == 1)
			ray->wall[0] = 'W';
		if (wall_position[0] - position[0] == -1)
			ray->wall[0] = 'E';
		return ;
	}
	else if (map[position[1]][wall_position[0]] != '0')
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

void	calculate_ray_length_and_wallside(t_cube *game, t_ray *ray, float *position)
{
	float	wall_posi[2];
	int		int_pos[2];
	int		int_wall_p[2];

	fassign_coordinates(wall_posi, position);
	coordinates_float_to_int(int_wall_p, wall_posi);
	coordinates_float_to_int(int_pos, position);
	while (/*(int_wall_p[1] / MAP_SCALE) > 0
			&& (int_wall_p[1] / MAP_SCALE) < game->input->map_info->total_lines - 1
			&& (int_wall_p[0] / MAP_SCALE) > 0
			&& (int_wall_p[0] / MAP_SCALE) < game->input->map_info->total_columns - 1
			&&*/ game->input->map_info->map[int_wall_p[1] / MAP_SCALE][int_wall_p[0] / MAP_SCALE] != '0')
	{
		wall_posi[0] -= ray->step_x /400;
		wall_posi[1] -= ray->step_y /400;
		coordinates_float_to_int(int_wall_p, wall_posi);
	}
	ints_to_mapadress(int_wall_p, int_wall_p);
//	int_wall_p[0] /= MAP_SCALE;
//	int_wall_p[1] /= MAP_SCALE;
	ray->contact_x = wall_posi[0];
	ray->contact_y = wall_posi[1];
	ints_to_mapadress(int_pos, int_pos);
//	int_pos[0] /= MAP_SCALE;
//	int_pos[1] /= MAP_SCALE;
	set_wallside(ray, int_pos, int_wall_p, game->input->map_info->map);
	if (ray->wall[0] == 'K')
		set_corners(game, ray, int_pos);
	ray->length = sqrt(pow(ray->contact_x - game->player->position[0], 2)
			+ pow(ray->contact_y - game->player->position[1], 2));
}
