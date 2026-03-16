/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 14:40:12 by mlehmann          #+#    #+#             */
/*   Updated: 2026/03/16 19:23:36 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
Subject :
	The left and right arrow keys of the keyboard must allow you to look left and right in the maze
	The W, A, S, and D keys must allow you to move the point of view through the maze
	Pressing ESC must close the window and quit the program cleanly
	Clicking on the red cross on the window’s frame must close the window and quit the program cleanly
*/
void	actions(mlx_key_data_t key, void *params)
{
	t_cube	*game;

	game = params;
	if (key.key == MLX_KEY_RIGHT && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		turn_right(game);
	if (key.key == MLX_KEY_LEFT && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		turn_left(game);
	// implement move right = D /left = A /up = W /down = S )
	if (key.key == MLX_KEY_D && key.action == MLX_PRESS || key.action == MLX_REPEAT)
		move_right(game);
	if (key.key == MLX_KEY_A && key.action == MLX_PRESS || key.action == MLX_REPEAT)
		move_left(game);
	if (key.key == MLX_KEY_W && key.action == MLX_PRESS || key.action == MLX_REPEAT)
		move_forward(game);
	if (key.key == MLX_KEY_S && key.action == MLX_PRESS || key.action == MLX_REPEAT)
		move_backward(game);
	// implement escape
	if (key.key == MLX_KEY_ESCAPE && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
	{
		printf(ERR_MSG_09);
		// clean and exit properly - See w/ Maxi for the clean MLX
	}
	// implement red cross mouse hook (maybe not here ?)
	draw_minimap(game, game->input->map_info->map);
}

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
