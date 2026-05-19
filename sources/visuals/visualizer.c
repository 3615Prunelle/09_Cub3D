/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 16:06:52 by mlehmann          #+#    #+#             */
/*   Updated: 2026/05/08 15:04:52 by mlehmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_rays(t_cube *game)
{
	int			i;
	int			j;
	uint32_t	color;
	int			borders[2];

	i = 0;
	while (i < VIEW_WIDTH)
	{
		borders[0] = VIEW_HEIGHT / 2 - (int)((((MAP_SCALE * VIEW_HEIGHT) / (game->rays[i]->length + VIEW_DISTANCE))) / 2);
		borders[1] = VIEW_HEIGHT / 2 + (int)((((MAP_SCALE * VIEW_HEIGHT) / (game->rays[i]->length + VIEW_DISTANCE))) / 2);
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
	game->player->position[0] = game->player->int_cords[0] * MAP_SCALE + MAP_SCALE / 2;
	game->player->position[1] = game->player->int_cords[1] * MAP_SCALE + MAP_SCALE / 2;
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
