/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 12:42:45 by mlehmann          #+#    #+#             */
/*   Updated: 2026/05/21 15:50:31 by schappuy         ###   ########.fr       */
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
	free_input_info_struct(game->input);
	exit(0);
}
