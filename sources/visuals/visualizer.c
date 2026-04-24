/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 16:06:52 by mlehmann          #+#    #+#             */
/*   Updated: 2026/04/01 14:42:08 by mlehmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	paint_wall(t_cube *game, t_ray *ray, int *borders, int j)
{
	uint32_t color;

	if (borders[0] > borders[1])
		return (0x000000FF);
	if (ray->wall[0] == 'N' && game->input->NO)
	{
		color = get_south_north_color(game, ray, borders, j);
		return (color);
	}
	if (ray->wall[0] == 'S' && game->input->SO)
	{
		color = get_south_north_color(game, ray, borders, j);
		return (color);
	}
	if (ray->wall[0] == 'W' && game->input->WE)
	{
		color = get_west_east_color(game, ray, borders, j);
		return (color);
	}
	if (ray->wall[0] == 'E' && game->input->EA)
	{
		color = get_west_east_color(game, ray, borders, j);
		return (color);
	}
	if (ray->wall[0] == 'K' && game->input->SO)
		return (0x00FF00FF);
	return (0x000000FF);
}

void	draw_rays(t_cube *game)
{
	int			i;
	int			j;
	uint32_t	color;
	int			borders[2];

	i = 0;
//	printf("\n");//debug
	while (i < VIEW_WIDTH)
	{
//		borders[0] = VIEW_HEIGHT / 2 - (int)((VIEW_HEIGHT / game->rays[i]->length));
//		borders[1] = VIEW_HEIGHT / 2 + (int)((VIEW_HEIGHT / game->rays[i]->length));
		borders[0] = VIEW_HEIGHT / 2 - (int)((((MAP_SCALE * VIEW_HEIGHT) / (game->rays[i]->length + VIEW_DISTANCE))) / 2);
		borders[1] = VIEW_HEIGHT / 2 + (int)((((MAP_SCALE * VIEW_HEIGHT) / (game->rays[i]->length + VIEW_DISTANCE))) / 2);
//		if (i < VIEW_WIDTH - 4)
//			ft_spike(game, i, borders);//debug
//		if (i % 10 == 0)
//			printf("%d borders: %d / %d\t", i, borders[0], borders[1]);//debug
/*		if (borders[0] < 0)
			borders[0] = 0;
		if (borders[1] > VIEW_HEIGHT)
			borders[1] = VIEW_HEIGHT;*/
		j = 0;
		while (borders[0] + j < borders[1])
		{
			while (borders[0] + j < 0)
				j++;
			color = paint_wall(game, game->rays[i], borders, j);
			pixel_to_image(&game->view->pixels[((borders[0] + j) * VIEW_WIDTH + i) * sizeof(int32_t)], color);
			j++;
			if (borders[0] + j >= VIEW_HEIGHT)
				break ;
		}
		i++;
	}
}

void	fill_view(t_cube *game)
{
	int	i;
	int	j;
	uint32_t	colors[2];

	i = 0;
	j = 0;
	colors[0] = load_color(game->input->ceiling);
	colors[1] = load_color(game->input->floor);
	while (j < VIEW_HEIGHT / 2)
	{
		while (i < VIEW_WIDTH)
		{
			pixel_to_image(&game->view->pixels[(j * VIEW_WIDTH + i) * sizeof(int32_t)], colors[0]);
			i++;
		}
		i = 0;
		j++;
	}
	while (j < VIEW_HEIGHT)
	{
		while (i < VIEW_WIDTH)
		{
			pixel_to_image(&game->view->pixels[(j * VIEW_WIDTH + i) * sizeof(int32_t)], colors[1]);
			i++;
		}
		i = 0;
		j++;
	}
}

void	start_visuals(t_cube *game)
{
	draw_minimap(game, game->input->map_info->map);
	cast_rays(game, game->input->map_info->map);
	fill_view(game);
	draw_rays(game);
	mlx_image_to_window(game->window, game->view, 0, 0);
	mlx_image_to_window(game->window, game->minimap, VIEW_WIDTH - MINI_WIDTH, VIEW_HEIGHT - MINI_HEIGHT);
}

void	pixel_to_image(uint8_t *pixel, uint32_t colour)
{
	pixel[0] = (uint8_t)(colour >> 24);
	pixel[1] = (uint8_t)(colour >> 16);
	pixel[2] = (uint8_t)(colour >> 8);
	pixel[3] = (uint8_t)(colour & 0xFF);
}
