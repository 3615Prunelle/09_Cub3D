#include "cub3d.h"

int	main(int ac, char **av)
{
	t_input	*input_info;
	if (ac != 2)
		print_error_free_exit(NULL, ERR_MSG_01, false, NULL);
	input_info = ft_calloc(sizeof(t_input), 1);				// Ⓜ️
	if(!input_info)
		print_error_free_exit(NULL, strerror(errno), false, NULL);
	parsing(av[1], input_info);
	printf("Parsing & Map creation success\n");

	// rendering in minimap
	// set up textures
	// render final map & movements in loop

	t_cube			game;
	t_player_data	player;
	t_input			input;
	char			**map;
	map = mockup_map(0);//so I dont need any checks
	set_input(&input, map);
	game.input = &input;
	player.int_cords[0] = 5;
	player.int_cords[1] = 3;
	player.position[0] = 32.0f * 5 + 16;
	player.position[1] = 32.0f * 3 + 16;
	player.direction = 0.0f;
	player.initial_direction = 'N';
	game.player = &player;
	set_game(&game);
	// av[1] = a map in format *.cub
	// 1st function = parsing & checking
	// rendering in minimap
	start_visuals(&game);
	// set up textures
	// render final map & movements in loop
	mlx_key_hook(game.window, actions, &game);
	mlx_close_hook(game.window, disappear, &game);
	mlx_loop(game.window);
	disappear(&game);

	free_input_info_struct(input_info);
	return(0);
}
