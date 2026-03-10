/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimapper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlehmann <mlehmann@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 16:04:59 by mlehmann          #+#    #+#             */
/*   Updated: 2026/03/10 15:29:45 by mlehmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./../../includes/cub3d.h"

void	draw_cone(t_cube * game, char **minimap)
{
	float	i;

	i = 30.0f;
	while (i > -30.0f)
	{
		i -= 60.f / 360;
	}
}

void	pixel_to_image(uint8_t *pixel, uint32_t colour)
{
	*(pixel++) = (uint8_t)(colour >> 24);
	*(pixel++) = (uint8_t)(colour >> 16);
	*(pixel++) = (uint8_t)(colour >> 8);
	*(pixel++) = (uint8_t)(colour & 0xFF);
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

	BPP = sizeof(int32_t);
	index = (y * 320 + x) * BPP;
	pixel_to_image(&game->minimap->pixels[index], 0xFF0000FF);
	index = (y * 320 + x + 1) * BPP;
	pixel_to_image(&game->minimap->pixels[index], 0xFF0000FF);
	index = (y * 320 + x - 1) * BPP;
	pixel_to_image(&game->minimap->pixels[index], 0xFF0000FF);
	index = ((y + 1)* 320 + x) * BPP;
	pixel_to_image(&game->minimap->pixels[index], 0xFF0000FF);
	index = ((y - 1)* 320 + x) * BPP;
	pixel_to_image(&game->minimap->pixels[index], 0xFF0000FF);
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
//	draw_player(game, player_x, player_y);
/*	mlx_put_pixel(game->minimap, (int)game->player->position[0], (int)game->player->position[1], 0xFF0000);
	mlx_put_pixel(game->minimap, (int)game->player->position[0], (int)game->player->position[1] - 1, 0xFF0000);
	mlx_put_pixel(game->minimap, (int)game->player->position[0], (int)game->player->position[1] + 1, 0xFF0000);
	mlx_put_pixel(game->minimap, (int)game->player->position[0] - 1, (int)game->player->position[1], 0xFF0000);
	mlx_put_pixel(game->minimap, (int)game->player->position[0] + 1, (int)game->player->position[1], 0xFF0000);*/
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
