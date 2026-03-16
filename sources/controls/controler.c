/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 14:40:12 by mlehmann          #+#    #+#             */
/*   Updated: 2026/03/16 16:02:06 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	actions(mlx_key_data_t key, void *params)
{
	t_cube	*game;

	game = params;
	if (key.key == MLX_KEY_RIGHT && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		turn_right(game);
	if (key.key == MLX_KEY_LEFT && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		turn_left(game);
	draw_minimap(game, game->input->map_info->map);
}
