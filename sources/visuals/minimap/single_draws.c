/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_draws.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 10:31:05 by mlehmann          #+#    #+#             */
/*   Updated: 2026/05/21 14:13:03 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line(t_cube *game, char *line, int position)
{
	int	i;
	int	j;
	int	length;
	int	index;

	i = 0;
	j = position;
	length = (ft_strlen(line)) * MAP_SCALE;
	while (j < position + 1 && j * i < MINI_WIDTH * MINI_HEIGHT)
	{
		while (i < MINI_WIDTH)
		{
			index = (j * MINI_WIDTH + i) * sizeof(int32_t);
			if (i + game->player->int_cords[0] - MINI_WIDTH / 2 > length
				|| i + game->player->int_cords[0] - MINI_WIDTH / 2 < 0)
				pixel_to_image(&game->minimap->pixels[index], 0x000000FF);
			else
				fill_minimap(game, line, i, index);
			i++;
		}
		i = 0;
		j++;
	}
}
