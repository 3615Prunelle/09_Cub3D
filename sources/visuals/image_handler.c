/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlehmann <mlehmann@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 12:40:06 by mlehmann          #+#    #+#             */
/*   Updated: 2026/05/21 13:05:28 by mlehmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

mlx_texture_t	**load_textures(t_input *input)
{
	mlx_texture_t	**textures;

	textures = malloc(4 * sizeof(mlx_texture_t *));
	if (!textures)
		return (NULL);
	textures[0] = mlx_load_png(input->north);
	if (!textures[0])
		return (NULL);
	textures[1] = mlx_load_png(input->south);
	if (!textures[1])
		return (NULL);
	textures[2] = mlx_load_png(input->west);
	if (!textures[2])
		return (NULL);
	textures[3] = mlx_load_png(input->east);
	if (!textures[3])
		return (NULL);
	return (textures);
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

void	setup_player(t_cube *game)
{
	game->player->position[0] = game->player->int_cords[0] * MAP_SCALE
		+ MAP_SCALE / 2;
	game->player->position[1] = game->player->int_cords[1] * MAP_SCALE
		+ MAP_SCALE / 2;
	if (game->player->initial_direction == 'N')
		game->player->direction = 0;
	else if (game->player->initial_direction == 'S')
		game->player->direction = 180;
	else if (game->player->initial_direction == 'E')
		game->player->direction = 90;
	else if (game->player->initial_direction == 'W')
		game->player->direction = 270;
}

void	set_game(t_cube	*game)
{
	mlx_t		*mlx;
	mlx_image_t	*map;
	mlx_image_t	*field_of_vision;

	game->rays = malloc(VIEW_WIDTH * sizeof(t_ray *));
	if (!ray_allocation(game->rays))
		disappear(game);
	game->textures = load_textures(game->input);
	if (!game->textures)
		disappear(game);
	game->viewplane = VIEW_DISTANCE * (2 * tanf((FOV / 2) * DEG_TO_RAD));
	setup_player(game);
	mlx = mlx_init(VIEW_WIDTH, VIEW_HEIGHT, "see_no_evil", false);
	map = mlx_new_image(mlx, MINI_WIDTH, MINI_HEIGHT);
	field_of_vision = mlx_new_image(mlx, VIEW_WIDTH, VIEW_HEIGHT);
	game->window = mlx;
	game->minimap = map;
	game->view = field_of_vision;
}
