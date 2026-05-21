/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlehmann <mlehmann@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 12:42:45 by mlehmann          #+#    #+#             */
/*   Updated: 2026/05/21 12:49:11 by mlehmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	disappear(void *param)
{
	t_cube	*game;
	int		i;

	i = 0;
	game = param;
	if (game->minimap)
		mlx_delete_image(game->window, game->minimap);
	if (game->view)
		mlx_delete_image(game->window, game->view);
	if (game->window)
		mlx_terminate(game->window);
	if (game->input->map_info->map)
		breakdown(game->input->map_info->map);
	while (i < VIEW_WIDTH)
	{
		if (game->rays[i])
		{
			free(game->rays[i]->wall);
			free(game->rays[i]);
		}
		game->rays[i] = NULL;
		i++;
	}
	exit(0);
}
