/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimapper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 16:04:59 by mlehmann          #+#    #+#             */
/*   Updated: 2026/05/08 15:30:24 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*void	draw_ray(t_cube *game, float y, float x, char **minimap)
{
	float	i;
	float	j;
	int		index;
	int		ray[2];
	int		ppr;

	i = 0.f;
	j = 0.f;
	ppr = MINI_WIDTH;
	while (MINI_HEIGHT / 2 + i > 0 && MINI_HEIGHT / 2 + i < MINI_HEIGHT
		&& MINI_WIDTH / 2 + j > 0 && MINI_WIDTH / 2 + j < MINI_WIDTH)
	{
		ray[1] = (int)i;
		ray[0] = (int)j;
		if (minimap[(game->player->int_cords[1] + ray[1]) / MAP_SCALE][(game->player->int_cords[0] + ray[0]) / MAP_SCALE] != '1')
		{
			index = ((MINI_HEIGHT / 2 + ray[1]) * ppr + MINI_WIDTH / 2 + ray[0]) * sizeof(int32_t);
			pixel_to_image(&game->minimap->pixels[index], 0xFFFFFFFF);
		}
		else
			break ;
		j += x;
		i += y;
	}
}

void	draw_cone(t_cube * game, char **minimap)
{
	float	i;
	float	base;
	float	fov_step;
	int		ray_step[2]; //0 for x 1 for y, so the direction is right

	i = FOV / 2;
	base = game->player->direction;
	fov_step = FOV / VIEW_WIDTH;
	while (i > - FOV / 2)
	{
		ray_step[0] = 1;
		ray_step[1] = 1;
		if (add_degree(base, i) > 270 || add_degree(base, i) < 90)
			ray_step[1] = -1;
		if (add_degree(base, i) > 180 && add_degree(base, i) < 360)
			ray_step[0] = -1;
		if ((add_degree(base, i) >= 44 && add_degree(base, i) <= 136) || (add_degree(base, i) >= 224 && add_degree(base, i) <= 316))
			draw_ray(game, ray_step[1] * fabsf(ray_step[0] / tanf(add_degree(base, i) * DEG_TO_RAD)), ray_step[0], minimap);
//			draw_ray(game, tanf(add_degree(base, i - 90) * DEG_TO_RAD), ray_step[0], minimap);
		if ((add_degree(base, i) >= 314 || add_degree(base, i) <= 46) || (add_degree(base, i) >= 134 && add_degree(base, i) <= 226))
			draw_ray(game, ray_step[1], ray_step[0] * fabsf(tanf(add_degree(base, i) * DEG_TO_RAD)), minimap);
		i -= fov_step;
	}
}*/
int	ray_contact(t_ray *ray, float *position, float *step, int *index)
{
	int	contact;

	contact = 0;
	step[0] += ray->step_x;
	step[1] += ray->step_y;
	if ((ray->step_x < 0 && step[0] <= ray->contact_x) || (ray->step_x > 0 &&
		 step[0] >= ray->contact_x))
		contact++;
	if ((ray->step_y < 0 && step[1] <= ray->contact_y) || (ray->step_y > 0 &&
		 step[1] >= ray->contact_y))
		contact++;
	if (contact == 2)
		return (1);
	index[0] = ((index[2] + (int)step[1] - (int)position[1]) * MINI_WIDTH +
		index[1] + ((int)step[0] - (int)position[0])) * sizeof(int32_t);
	return (0);
}

void	draw_cone(t_cube * game, float *position)
{
	int		i;
	float	step[2];
	int		index[3];
	t_ray	*ray;

	i = 0;
	index[1] = MINI_WIDTH /2;
	index[2] = MINI_HEIGHT / 2;
	while (i < VIEW_WIDTH)
	{
		step[0] = position[0];
		step[1] = position[1];
		ray = game->rays[i];
		while (step[0] - position[0] < index[1] - 1 && step[1] - position[1] <
			index[2] - 1 && step[0] - position[0] >	- index[1] + 1 &&
			 step[1] - position[1] > -index[2] + 1)
		{
			if (ray_contact(ray, position, step, index) == 1 ||
				game->input->map_info->map[(int)step[1] / MAP_SCALE]
				[(int)step[0] / MAP_SCALE] == '1')
				break ;
			pixel_to_image(&game->minimap->pixels[index[0]], 0xFFFFFFFF);
		}
		i++;
	}
}

void	draw_line(t_cube *game, char *line, int position)
{
	int	i;
	int	j;
	int	length;
	int index;

	i = 0;
	j = position;
	length = (ft_strlen(line) - 1) * MAP_SCALE;
	while (j < position + 1 && j * i < MINI_WIDTH * MINI_HEIGHT)
	{
		while ( i < MINI_WIDTH)
		{
			index = (j * MINI_WIDTH + i) * sizeof(int32_t);
			if (i + game->player->int_cords[0] - MINI_WIDTH / 2 > length || i + game->player->int_cords[0] - MINI_WIDTH / 2 < 0)
				pixel_to_image(&game->minimap->pixels[index], 0x000000FF);
			else
			{
				if (line[(i + game->player->int_cords[0] - MINI_WIDTH / 2) / MAP_SCALE] == ' ')
					pixel_to_image(&game->minimap->pixels[index], 0x000000FF);
//				if (line[(i + game->player->int_cords[0] - MINI_WIDTH / 2) / 32] == '0')
				else
					pixel_to_image(&game->minimap->pixels[index], 0x003388FF);
				if (line[(i + game->player->int_cords[0] - MINI_WIDTH / 2) / MAP_SCALE] == '1')
					pixel_to_image(&game->minimap->pixels[index], 0x0000FFFF);
			}
			i++;
		}
		i = 0;
		j++;
	}
}

void	draw_player(t_cube *game, int x, int y)
{
	int	index;
	int	BPP;
	int BPR;

	BPP = sizeof(int32_t);
	BPR = BPP * MINI_WIDTH;
	index = (MINI_HEIGHT / 2 * MINI_WIDTH + MINI_WIDTH / 2) * BPP;
	pixel_to_image(&game->minimap->pixels[index], 0xFF0000FF);
	pixel_to_image(&game->minimap->pixels[index - BPP], 0xFF0000FF);
	pixel_to_image(&game->minimap->pixels[index + BPP], 0xFF0000FF);
	pixel_to_image(&game->minimap->pixels[index - BPR], 0xFF0000FF);
	pixel_to_image(&game->minimap->pixels[index + BPR], 0xFF0000FF);
}

void	draw_minimap(t_cube *game, char **minimap)
{
	int	i;

	i = 0;
	game->player->int_cords[0] = (int)game->player->position[0];
	game->player->int_cords[1] = (int)game->player->position[1];
	while (i < MINI_HEIGHT)
	{
		if ((i + game->player->int_cords[1] - MINI_HEIGHT / 2) < 0 || (i + game->player->int_cords[1] - MINI_HEIGHT / 2) / 32 >= game->input->map_info->total_lines)
			draw_line(game, "", i);
		else
			draw_line(game, minimap[(i + game->player->int_cords[1] - MINI_HEIGHT / 2) / MAP_SCALE], i);
		i++;
	}
	draw_cone(game, game->player->position);
	draw_player(game, game->player->int_cords[0], game->player->int_cords[1]);
}
