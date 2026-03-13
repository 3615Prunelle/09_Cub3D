/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimapper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlehmann <mlehmann@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 16:04:59 by mlehmann          #+#    #+#             */
/*   Updated: 2026/03/13 11:50:12 by mlehmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cub3d.h"

void	draw_ray(t_cube *game, float y, float x, char **minimap)
{
	float	i;
	float	j;
	int		index;
	int		ray_x;
	int		ray_y;

	i = 0.f;
	j = 0.f;
	while (game->player->position[1] + i > 0 && game->player->position[1] + i < 320
		&& game->player->position[0] + j > 0 && game->player->position[0] + j < 320)
	{
		ray_y = (int)i;
		ray_x = (int)j;
		if (minimap[(game->player->int_cords[1] + ray_y) / 32][(game->player->int_cords[0] + ray_x) / 32] != '1')
		{
			index = ((game->player->int_cords[1] + ray_y) * 320 + game->player->int_cords[0] + ray_x) * sizeof(int32_t);
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

	i = 30.0f;
	base = game->player->direction;
	fov_step = 60.f / 320;
	while (i > -30.0f)
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
}

void	draw_line(t_cube *game, char *line, int position)
{
	int	i;
	int	j;
	int	length;
	int index;

	i = 0;
	j = position;
	length = ft_strlen(line) * 32;
	while (j < position + 33)
	{
		while ( i < length)
		{
			index = (j * length + i) * sizeof(int32_t);
			if (line[i / 32] == '0')
				pixel_to_image(&game->minimap->pixels[index], 0x000000FF);
			if (line[i / 32] == '1')
				pixel_to_image(&game->minimap->pixels[index], 0x0000FFFF);
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
	BPR = BPP * 320;
	index = (y * 320 + x) * BPP;
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
	while (i < 10)
	{
		draw_line(game, minimap[i], i * 32);
		i++;
	}
	game->player->int_cords[0] = (int)game->player->position[0];
	game->player->int_cords[1] = (int)game->player->position[1];
	draw_cone(game, minimap);
	draw_player(game, game->player->int_cords[0], game->player->int_cords[1]);
}

void	transscibe(char **minimap, char **map, int mapsize)
{
	int	i;
	int	j;
	int	k;
	int	l;

	i = 0;
	j = 0;
	while (1)
	{
		while (j < ft_strlen(map[i]))
		{
			if (map[i][j] == 'P')
				break ;
			j++;
		}
		if (map[i][j] == 'P')
			break ;
		j = 0;
		i++;
	}
	while (k < 7)
	{
		if (i - 3 + k < 0 || i - 3 + k > mapsize)
		{
			while (l < 7)
			{
				minimap[k][l] = ' ';
				l++;
			}
			l = 0;
			k++;
		}
		else
		{
			while (l < 7)
			{
				if (j - 3 + l < 0 || j - 3 + l > ft_strlen(map[k]))
				{
					minimap[k][l] = ' ';
					l++;
				}
				else
				{
					minimap[k][l] = map[i - 3 + k][j - 3 + l];
					l++;
				}
			}
			l = 0;
			k++;
		}
		minimap[i][j] = '0';
	}
}
