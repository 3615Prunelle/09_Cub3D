/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 16:06:52 by mlehmann          #+#    #+#             */
/*   Updated: 2026/05/21 12:22:35 by mlehmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_frame_borders(int *borders, t_cube *game, int i)
{
	borders[0] = VIEW_HEIGHT / 2 - (int)((((MAP_SCALE * VIEW_HEIGHT)
					/ (game->rays[i]->length + VIEW_DISTANCE))) / 2);
	borders[1] = VIEW_HEIGHT / 2 + (int)((((MAP_SCALE * VIEW_HEIGHT)
					/ (game->rays[i]->length + VIEW_DISTANCE))) / 2);
}

void	draw_rays(t_cube *game)
{
	int			i;
	int			j;
	uint32_t	color;
	int			borders[2];

	i = 0;
	while (i < VIEW_WIDTH)
	{
		set_frame_borders(borders, game, i);
		j = 0;
		while (borders[0] + j < borders[1])
		{
			while (borders[0] + j < 0)
				j++;
			color = paint_wall(game, game->rays[i], borders, j);
			pixel_to_image(&game->view->pixels[((borders[0] + j) * VIEW_WIDTH
					+ i) * sizeof(int32_t)], color);
			j++;
			if (borders[0] + j >= VIEW_HEIGHT)
				break ;
		}
		i++;
	}
}

void	make_floor_and_ceiling(t_cube *game, uint32_t color, int j)
{
	int	i;

	i = 0;
	while (i < VIEW_WIDTH)
	{
		pixel_to_image(&game->view->pixels[(j * VIEW_WIDTH + i)
			* sizeof(int32_t)], color);
		i++;
	}
}

void	fill_view(t_cube *game)
{
	int			j;
	uint32_t	colors[2];

	j = 0;
	colors[0] = load_color(game->input->ceiling);
	colors[1] = load_color(game->input->floor);
	while (j < VIEW_HEIGHT / 2)
	{
		make_floor_and_ceiling(game, colors[0], j);
		j++;
	}
	while (j < VIEW_HEIGHT)
	{
		make_floor_and_ceiling(game, colors[1], j);
		j++;
	}
}

void	start_visuals(t_cube *game)
{
	game->player->position[0] = game->player->int_cords[0]
		* MAP_SCALE + MAP_SCALE / 2;
	game->player->position[1] = game->player->int_cords[1]
		* MAP_SCALE + MAP_SCALE / 2;
	cast_rays(game, game->input->map_info->map);
	draw_minimap(game, game->input->map_info->map);
	fill_view(game);
	draw_rays(game);
	mlx_image_to_window(game->window, game->view, 0, 0);
	mlx_image_to_window(game->window, game->minimap, VIEW_WIDTH - MINI_WIDTH,
		VIEW_HEIGHT - MINI_HEIGHT);
}
