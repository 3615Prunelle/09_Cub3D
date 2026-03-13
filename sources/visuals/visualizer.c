/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlehmann <mlehmann@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 16:06:52 by mlehmann          #+#    #+#             */
/*   Updated: 2026/03/12 10:36:10 by mlehmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

void	start_visuals(t_cube *game)
{
	draw_minimap(game, game->input->map);
	mlx_image_to_window(game->window, game->minimap, 0, 0);
}

void	pixel_to_image(uint8_t *pixel, uint32_t colour)
{
	pixel[0] = (uint8_t)(colour >> 24);
	pixel[1] = (uint8_t)(colour >> 16);
	pixel[2] = (uint8_t)(colour >> 8);
	pixel[3] = (uint8_t)(colour & 0xFF);
}
