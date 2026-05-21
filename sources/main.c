/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 14:07:52 by schappuy          #+#    #+#             */
/*   Updated: 2026/05/21 15:56:28 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_cube	game;
	t_input	*input_info;

	if (ac != 2)
		print_error_free_exit(NULL, ERR_MSG_1, false, NULL);
	input_info = ft_calloc(sizeof(t_input), 1);
	if (!input_info)
		print_error_free_exit(NULL, strerror(errno), false, NULL);
	parsing(av[1], input_info);
	printf("Parsing & Map creation success\n");
	game.input = input_info;
	game.player = &input_info->player;
	set_game(&game);
	start_visuals(&game);
	mlx_key_hook(game.window, actions, &game);
	mlx_close_hook(game.window, disappear, &game);
	mlx_loop(game.window);
	disappear(&game);
	return (0);
}
