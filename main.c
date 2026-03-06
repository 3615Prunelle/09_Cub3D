/* Notes random
🔴
🟠
🟡
🟢
🔵
🟣
🟤
⚫
⚪

⬇️✅‼️⁉️❓❌Ⓜ️🆓
*/
#include "includes/cub3d.h"

void	breakdown(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
	{
		if (map[i])
			free(map[i]);
		i++;
	}
	free(map);
}

char	**mockup_map(int i)
{
	char	**map;
	int		j;

	j = 0;
	map = (char **)malloc(sizeof(char *) * 10);
	if (!map)
		return(NULL);
	map[9] = NULL;
	while (i < 9)
	{
		map[i] = (char *)malloc(sizeof(char) * 11);
		if (!map[i])
		{
			breakdown(map);
			return (NULL);
		}
		while (j < 10)
		{
			if (i == 0 || j == 0 || j == 9 || i == 9)
				map[i][j] = '1';
			else
				map[i][j] = '0';
			j++;
		}
		map[i][j] = '\0';
		j = 0;
		i++;
	}
//	map[5][5] = 'S';
	return map;
}

void	disappear(t_cube *game)
{
	mlx_delete_image(game->window, game->minimap);
	mlx_delete_image(game->window, game->view);
	mlx_terminate(game->window);
	breakdown(game->input->map);
	exit(0);
}

int	main(int ac, char **av)
{
	t_cube			game;
	t_player_data	player;
	char			**map;
	map = mockup_map(0);//so I dont need any checks
	game.input->map = map;
	player.initial_coordinates[0] = 5;
	player.initial_coordinates[1] = 5;
	player.position[0] = 32.0f * 5;
	player.position[1] = 32.0f * 5;
	player.direction = 0.0f;
	game.player = &player;
	// av[1] = a map in format *.cub
	// 1st function = parsing & checking
	game.window = mlx_init(320, 320, "see_no_evil", false);
	game.minimap = mlx_new_image(game.window, 320, 320);
	game.view = mlx_new_image(game.window, 320, 320);
	// rendering in minimap
	start_visuals(&game);
	// set up textures
	// render final map & movements in loop
	mlx_close_hook(game.window, disappear, &game);
	mlx_loop(game.window);
	disappear(&game);
	return(0);
}
