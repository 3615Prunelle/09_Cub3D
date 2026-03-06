/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlehmann <mlehmann@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 16:06:52 by mlehmann          #+#    #+#             */
/*   Updated: 2026/03/06 16:41:30 by mlehmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

void	start_visuals(t_cube *game)
{
	draw_minimap(game, game->input->map);
	mlx_image_to_window(game->window, game->minimap, 0, 0);
}
