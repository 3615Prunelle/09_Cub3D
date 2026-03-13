/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlehmann <mlehmann@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 14:52:15 by mlehmann          #+#    #+#             */
/*   Updated: 2026/03/13 11:40:33 by mlehmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	turn_right(t_cube *game)
{
	float	i;

	i = game->player->direction;
	game->player->direction = add_degree(i, 1); 
//	if (i == 0 || i == 45 || i == 90 || i == 135 || i == 180 || i == 225 || i == 270 || i == 315 || i == 360)
//	printf("dir=%.1f, ", game->player->direction); just a little test
}

void	turn_left(t_cube *game)
{
	float	i;

	i = game->player->direction;
	game->player->direction = add_degree(i, -1); 
}
