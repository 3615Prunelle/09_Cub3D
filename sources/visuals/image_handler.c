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
	int		i;

	i = 0;
	game = param;
	if (game->minimap)
		mlx_delete_image(game->window, game->minimap);
	if (game->view)
		mlx_delete_image(game->window, game->view);
	if (game->window)
		mlx_terminate(game->window);
	if (game->input->map_info->map)
		breakdown(game->input->map_info->map);
	while (i < VIEW_WIDTH)
	{
		if (game->rays[i])
		{
			free(game->rays[i]->wall);
			free(game->rays[i]);
		}
		game->rays[i] = NULL;
		i++;
	}
	exit(0);
}

bool	ray_allocation(t_ray **rays)
{
	t_ray	*ray;
	int		i;
	char	*c;

	i = 0;
	while (i < VIEW_WIDTH)
	{
		ray = malloc(sizeof(t_ray));
		if (!ray)
			return (false);
		c = malloc(2 * sizeof(char));
		if (!c)
			return (false);
		ray->length = 0.0;
		ray->step_x = 0;
		ray->step_y = 0;
		c[0] = '0';
		c[1] = '\0';
		ray->wall = c;
		rays[i] = ray;
		i++;
	}
	return (true);
}

void	set_game(t_cube	*game)
{
	mlx_t		*mlx;
	mlx_image_t	*map;
	mlx_image_t	*field_of_vision;

	game->rays = malloc(VIEW_WIDTH * sizeof(t_ray *));
	if (!ray_allocation(game->rays))
		disappear(game);
	game->viewdistance = VIEW_WIDTH / (2 * tanf((FOW / 2) * DEG_TO_RAD));
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
	mlx = mlx_init(VIEW_WIDTH, VIEW_HEIGHT, "see_no_evil", false);
	map = mlx_new_image(mlx, MINI_WIDTH, MINI_HEIGHT);
	field_of_vision = mlx_new_image(mlx, VIEW_WIDTH, VIEW_HEIGHT);
	game->window = mlx;
	game->minimap = map;
	game->view = field_of_vision;
}
