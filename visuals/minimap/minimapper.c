/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimapper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlehmann <mlehmann@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 16:04:59 by mlehmann          #+#    #+#             */
/*   Updated: 2026/03/06 16:44:50 by mlehmann         ###   ########.fr       */
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

void	draw_line(t_cube *game, char *line, int position)
{
	int	i;
	int	j;
	int	length;

	i = 0;
	j = 0;
	length = ft_strlen(line) * 32;
	while (j < 33)
	{
		while ( i < length)
		{
			if (line[i / 32] == '0')
				mlx_put_pixel(game->minimap, i, position + j, 0x000000);
			if (line[i / 32] == '1')
				mlx_put_pixel(game->minimap, i, position + j, 0x0000FF);
			i++;
		}
		i = 0;
		j++;
	}
}

void	draw_minimap(t_cube *game, char **minimap)
{
	int	i;

	i = 1;
	while (i < 10)
	{
		draw_line(game, minimap[i], i * 32);
		i++;
	}
	draw_cone(game, minimap);
	mlx_put_pixel(game->minimap, (int)game->player->position[0], (int)game->player->position[1], 0xFF0000);
	mlx_put_pixel(game->minimap, (int)game->player->position[0], (int)game->player->position[1] - 1, 0xFF0000);
	mlx_put_pixel(game->minimap, (int)game->player->position[0], (int)game->player->position[1] + 1, 0xFF0000);
	mlx_put_pixel(game->minimap, (int)game->player->position[0] - 1, (int)game->player->position[1], 0xFF0000);
	mlx_put_pixel(game->minimap, (int)game->player->position[0] + 1, (int)game->player->position[1], 0xFF0000);
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
