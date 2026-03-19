#include "cub3d.h"

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

void	disappear(void *param)
{
	t_cube	*game;
	game = param;
	if (game->minimap)
		mlx_delete_image(game->window, game->minimap);
	if (game->view)
		mlx_delete_image(game->window, game->view);
	if (game->window)
		mlx_terminate(game->window);
	if (game->input->map_info->map)
		breakdown(game->input->map_info->map);
	exit(0);
}

void	set_game(t_cube	*game)
{
	mlx_t		*mlx;
	mlx_image_t	*map;
	mlx_image_t	*field_of_vision;

	game->player->position[0] = game->player->int_cords[0] * 32 + 16;
	game->player->position[1] = game->player->int_cords[1] * 32 + 16;
	if (game->player->initial_direction == 'N')
		game->player->direction = 0;
	else if (game->player->initial_direction == 'S')
		game->player->direction = 180;
	else if (game->player->initial_direction == 'E')
		game->player->direction = 90;
	else if (game->player->initial_direction == 'W')
		game->player->direction = 270;
	mlx = mlx_init(game->input->map_info->max_columns * 32, game->input->map_info->max_lines * 32, "see_no_evil", false);
	map = mlx_new_image(mlx, game->input->map_info->max_columns * 32, game->input->map_info->max_lines * 32);
	field_of_vision = mlx_new_image(mlx, 320, 320);
	game->window = mlx;
	game->minimap = map;
	game->view = field_of_vision;
}
