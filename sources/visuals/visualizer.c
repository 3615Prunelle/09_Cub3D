/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 16:06:52 by mlehmann          #+#    #+#             */
/*   Updated: 2026/03/25 11:06:07 by mlehmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

u32int_t	paint_wall(t_cube *game, t_ray *ray, int[2] borders)
{
	if (borders[0] > borders[1])
		return (0x000000FF);
	if (ray->wall[0] = 'N' && game->input->NO)
		return (0x0000FFFF);
	if (ray->wall[0] = 'S' && game->input->SO)
		return (0xFFFF00FF);
	if (ray->wall[0] = 'W' && game->input->WE)
		return (0xFF00FFFF);
	if (ray->wall[0] = 'E' && game->input->EA)
		return (0xFF0000FF);
}

void	draw_rays(t_cube *game)
{
	int			i;
	u32int_t	color;
	int			borders[2];

	i = 0;
	while (i < VIEW_WIDTH)
	{
		borders[0] = (int)game->rays[i]->length;
		borders[1] = VIEW_HEIGHT - borders[0];
		while (borders[0] < borders[1])
		{
			color = paint_wall(game, game->rays[i], borders);
			pixel_to_image(&game->view->pixels[(borders[0] * VIEW_WIDTH + i) * sizeof(int32_t)], color);
			borders[0]++;
		}
		i++;
	}
}

void	fill_view(t_cube *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < VIEW_HEIGHT / 2)
	{
		while (i < VIEW_WIDTH)
		{
			pixel_to_image(&game->view->pixels[(j * VIEW_WIDTH + i) * sizeof(int32_t)], 0x000000FF);
			i++;
		}
		i = 0;
		j++;
	}
	while (j < VIEW_HEIGHT)
	{
		while (i < VIEW_WIDTH)
		{
			pixel_to_image(&game->view->pixels[(j * VIEW_WIDTH + i) * sizeof(int32_t)], 0xFFFFFFFF);
			i++;
		}
		i = 0;
		j++;
	}
}

void	start_visuals(t_cube *game)
{
	cast_rays(game, game->input->map_info->map);
	draw_minimap(game, game->input->map_info->map);
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
