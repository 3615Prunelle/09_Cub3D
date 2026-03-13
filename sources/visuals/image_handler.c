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
	map[10] = NULL;
	while (i < 10)
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
	map[5][3] = '1';
	map[4][7] = '1';
	map[7][7] = '1';
//	map[5][5] = 'S';
	return map;
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
	if (game->input->map)
		breakdown(game->input->map);
	exit(0);
}

void	set_game(t_cube	*game)
{
	mlx_t		*mlx;
	mlx_image_t	*map;
	mlx_image_t	*field_of_vision;
	mlx = mlx_init(320, 320, "see_no_evil", false);
	map = mlx_new_image(mlx, 320, 320);
	field_of_vision = mlx_new_image(mlx, 320, 320);
	game->window = mlx;
	game->minimap = map;
	game->view = field_of_vision;
}

void	set_input(t_input *input, char **map)
{
	input->NO = NULL;
	input->SO = NULL;
	input->WE = NULL;
	input->EA = NULL;
	input->floor[0] = 0;
	input->floor[1] = 0;
	input->floor[2] = 0;
	input->ceiling[0] = 0;
	input->ceiling[1] = 0;
	input->ceiling[2] = 0;
	input->map = map;
}
