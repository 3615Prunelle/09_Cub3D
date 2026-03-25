/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 14:52:15 by mlehmann          #+#    #+#             */
/*   Updated: 2026/03/25 17:56:12 by schappuy         ###   ########.fr       */
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


//	MOVING 1 STEP FORWARD
//	Adjust the degree (in calling function) depending on key pressed
void	move(t_cube *game, float degree)
{
	float	diff_x;
	float	diff_y;
	float	length_of_step = 1;							// Remove this variable and replace it by 1 in calculations below, because it won't ever change

	float	sinus = fabsf(sinf(degree * DEG_TO_RAD));	// fabsf avoids negative values
	diff_x = sinus * length_of_step;					// Same as sinus (because x1) - (Opposé = sin(α) × H)

	float	cosinus = fabsf(cosf(degree * DEG_TO_RAD));
	diff_y = cosinus * length_of_step;					// Same as cosinus (because x1) - (Adjacent = cos(α) × H)

	// Could this be useful at some point ? : (sin(degree)²) + (cos(degree)²) = 1

	// Keep in mind that [0][0] is up left
	if(degree > 0 && degree <= 90)
	{
		diff_y *= -1;
	}
	// else if(degree > 90 && degree <= 180)			// No need because both diffs are positive
	else if(degree > 180 && degree <= 270)
	{
		diff_x *= -1;
	}
	else if(degree > 270 || degree == 0)
	{
		diff_x *= -1;
		diff_y *= -1;
	}
	game->player->position[0] += diff_x;
	game->player->position[1] += diff_y;
}

// Degree must be >= 0 and < 360
float	adjust_degree(enum e_directions direction, float degree)
{
	if (direction == RIGHT)
	{
		// Add 90 degrees, making sure I stay within the limits
		if (degree < 270)
			degree += 90;
		else
			degree -= 270;		// If degree = 271, new is 1
	}
	else if (direction == BACK)
	{
		// Remove 180 degrees, making sure I stay within the limits
		if (degree >= 180)
			degree -= 180;
		else
			degree = (180 + degree);		// If degree = 1, new is 181
	}
	else if (direction == LEFT)
	{
		// Remove 90 degrees, making sure I stay within the limits
		if (degree >= 90)
			degree -= 90;
		else
			degree = (270 + degree);		// If degree = 10, new is 280
	}
	return (degree);
}
