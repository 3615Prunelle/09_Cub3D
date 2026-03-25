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
