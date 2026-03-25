/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 14:40:12 by mlehmann          #+#    #+#             */
/*   Updated: 2026/03/25 17:32:55 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
Subject :
	The left and right arrow keys of the keyboard must allow you to look left and right in the maze
	The W, A, S, and D keys must allow you to move the point of view through the maze
	Pressing ESC must close the window and quit the program cleanly
	Clicking on the red cross on the window’s frame must close the window and quit the program cleanly

	WARNING - Right implementation is not correct, check direction (degree) before moving
*/
void	actions(mlx_key_data_t key, void *params)
{
	t_cube	*game;
	float	degree = 40;

	game = params;
	degree = game->player->direction;


// All of the above works if player moves forward.
// If player moves backwards, the exact opposite should happen (all positive becomes neg, and vice versa)
// If player moves right, add 90 to the current degree ? And remove 90 for left ?

	if (key.key == MLX_KEY_RIGHT && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		turn_right(game);
	if (key.key == MLX_KEY_LEFT && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		turn_left(game);

	if (key.key == MLX_KEY_W && (key.action == MLX_PRESS || key.action == MLX_REPEAT))	// Forward
	{
		move(game, degree);
	}
	if (key.key == MLX_KEY_D && (key.action == MLX_PRESS || key.action == MLX_REPEAT))	// Right
	{
		degree = adjust_degree(RIGHT, degree);
		move(game, degree);
	}
	if (key.key == MLX_KEY_S && (key.action == MLX_PRESS || key.action == MLX_REPEAT))	// Backwards
	{
		degree = adjust_degree(BACK, degree);
		move(game, degree);
	}
	if (key.key == MLX_KEY_A && (key.action == MLX_PRESS || key.action == MLX_REPEAT))	// Left
	{
		degree = adjust_degree(LEFT, degree);
		move(game, degree);
	}

// printf("Degree [%f] - Diff x [%f] - Diff y [%f] - Coords : [%d][%d]\n", degree, diff_x, diff_y, game->player->int_cords[0], game->player->int_cords[1]);
// game->player->position[0] += diff_x;
// game->player->position[1] += diff_y;

	// implement escape
	if (key.key == MLX_KEY_ESCAPE && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
	{
		printf(ERR_MSG_09);
		exit (1);		// clean and exit properly instead - See w/ Maxi for the clean MLX
	}
	// implement red cross mouse hook (maybe not here ?)
	draw_minimap(game, game->input->map_info->map);
}

/*
the same key can be 4 directions depending on the degree

float direction = degree =	0 (315 to 45) = looking North
							90 (45 to 135) = looking East
							180 (135 to 225) = looking South
							270 (225 to 315) = looking West

Maxis's function : float	add_degree(float a, float b)
If player looking	North -	right = D	left = A	up = W			down = S (classic)
					East -	right = S	left = W	straight = D	backwards = A
					South -	right = A	left = D	straight = S	backwards = W
					West -	right = W	left = S	straight = A	backwards = D

Implement directions :



When done : make sure player doesn't go through walls
*/



/*
NOTES FROM SO_LONG

Je passe l'adresse de game dans la fonction appelante car je dois
respecter le "void param" que mlx_key_hook me demande
Variable move est utilisée dans la fonction target_position
A chaque touche pressée, on check le nombre de collectibles restants

void	key_actions(mlx_key_data_t keydata, void *param)
{
	t_game	*game;
	int		move;

	game = param;
	move = 0;
	if (!game || !game->playr_img || game->playr_img->count < 1)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		ft_printf(MSG_02);
		clean_and_exit(game);
	}
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		move = RIGHT;
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		move = LEFT;
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		move = UP;
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		move = DOWN;
	if (!move)
		return ;
	move_player_logic(*game, move);
	move_player_graphic(game);
	delete_collectible_instance(game);
}

*/
