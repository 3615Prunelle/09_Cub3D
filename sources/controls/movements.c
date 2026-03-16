/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 14:52:15 by mlehmann          #+#    #+#             */
/*   Updated: 2026/03/16 18:37:36 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

// Sophie's note : WIP
void	move_forward(t_cube *game)
{
	// Make sure the move is possible (in case of wall) TBC - In the calling function ? Here ? Case already covered earlier in the code ?
	float	y;

	y = game->player->position[1];
	game->player->position[1] = y + 1;		// Not sure about that - Double check w/ Maxi
}

void	move_backward(t_cube *game)
{
	float	y;

	y = game->player->position[1];
	game->player->position[1] = y - 1;
}

void	move_right(t_cube *game)
{
	float	x;

	x = game->player->position[0];
	game->player->position[0] = x + 1;
}

void	move_left(t_cube *game)
{
	float	x;

	x = game->player->position[0];
	game->player->position[0] = x - 1;
}
