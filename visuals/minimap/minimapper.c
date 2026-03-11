/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimapper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlehmann <mlehmann@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 16:04:59 by mlehmann          #+#    #+#             */
/*   Updated: 2026/03/11 14:53:09 by mlehmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./../../includes/cub3d.h"

void	draw_ray(t_cube *game, float y, float x, char **minimap)
{
	float	i;

	i = 0.f;
	index = ((int)(game->player->position[1] + y) * 320 + (int)(game->player->position[0] + x)) * BPP;
	while (game->player->position[1] + i > 0 && game->player->position[1] + i < 320)
	{

		i += y
	}
}

void	draw_cone(t_cube * game, char **minimap)
{
	float	i;
	float	step;
	float	to_rad;

	i = 30.0f;
	to_rad = M_PI / 180;
	step = 60.f / 320;
	while (i > -30.0f)
	{
		if (game->player->direction + i > 89 && game->player->direction + i < 91)
			draw_ray(game, -1, 0, minimap);
		i -= step;
	}
}

void	pixel_to_image(uint8_t *pixel, uint32_t colour)
{
	pixel[0] = (uint8_t)(colour >> 24);
	pixel[1] = (uint8_t)(colour >> 16);
	pixel[2] = (uint8_t)(colour >> 8);
	pixel[3] = (uint8_t)(colour & 0xFF);
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
	int	player_x;
	int	player_y;

	i = 0;
	while (i < 10)
	{
		draw_line(game, minimap[i], i * 32);
		i++;
	}
	draw_cone(game, minimap);
	player_x = (int)game->player->position[0];
	player_y = (int)game->player->position[1];
	draw_player(game, player_x, player_y);
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
